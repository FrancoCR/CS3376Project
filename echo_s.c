#include "echo_s_functions.h"

int main(int argc, char *argv[])
{
	int childpid = 0;
	
	// implements zombie handling
	signal(SIGCHLD, SIG_IGN);

	if (argc < 2 || argc > 4)
	{
		// checks if the number of arguments passed to the server are insufficient
		error("ERROR, required usage is ./echo_s <port1> [<port2> <port3>]");
	}
	
	int log_sockfd;
	unsigned int log_length;
	struct sockaddr_in log_serv_addr, from;
	struct hostent *log_server;
	char log_buffer[1024];
	
	int portno = getPort(argv[1]);
	int port_pid;
	// if we have multiple ports, we need to fork more processes
	for (int i = 2; i < argc; i++)
	{
		port_pid = fork();
		if (port_pid < 0)
		{
			error("ERROR on fork");
			
		}
		if (port_pid == 0)
		{
			// child
			portno = getPort(argv[i]);
			// leave the loop to start executing code on port i
			break;
		}
	}
	// parent will leave loop when it finishes spawning children to start executing code on port 1
	
	
	
	// createSocket creates a UDP socket and returns that sockets file descriptor
	log_sockfd = createSocket(AF_INET, SOCK_DGRAM, 0);

	// getServer verifies the user specified server is reachable
	log_server = getServer("localhost");

	// setupUDPAddr connects the host and the specified port
	setupUDPAddr(log_serv_addr, log_server, 9999);

	//setupConnection connects the socket file descriptor to the specified server
	setupConnection(log_sockfd, log_serv_addr);

	// the size of the sockaddr_in structure is used for both sendto and recvfrom commands
	log_length = sizeof(struct sockaddr_in);

	// closes the socket that was used for this communication

	// This fork is used to create two processes, one for handling TCP, and one for handling UDP
	if ((childpid = fork()) == -1)
	{
		error("Error creating child process.");
	}

	if (childpid == 0)
	{
		int sockfd, newsockfd;
		socklen_t clilen;
		char buffer[256];
		struct sockaddr_in serv_addr, cli_addr;

		// creates a TCP socket and returns the socket file descriptor
		sockfd = createSocket(AF_INET, SOCK_STREAM, 0);

		// parses the command line arguments to get the port number from the user
		// now taken from the loop above
		//portno = getPort(argv[1]);
               
		// connects the port address to the server object
		setupAddr(serv_addr, portno);

		//binds the TCP socket to the server object
		setupBind(sockfd, serv_addr);

		// starts listening for client requests
		startListen(sockfd, 5);

		// client length will be used for the creation of the child socket
		clilen = sizeof(cli_addr);
		int pid;

		// allows for new child processes to be created in response to requests indefinitely
		while (1)
		{
			// creates a new socket that will be used by the child process
			newsockfd = awaitRequest(sockfd, cli_addr, clilen);

			// creates a child process that will be used to handle the new request
			pid = fork();
			if (pid < 0)
			{
				error("ERROR on fork");
			}
			if (pid == 0) // the child is used to handle the request
			{
				// closes the childs copy of the parent socket
				cleanup(sockfd);
				time_t t = time(0);
				// clears the buffer used by the socket
				setupRequest(buffer, 256);

				// handles the request that has been received by the server
				handleRequest(sockfd, newsockfd, buffer, 256);

				logRequest(log_sockfd, log_serv_addr, log_length, cli_addr, t, buffer);

				//closes the child process after the server has handled the request
				exit(0);
			}
			else
			{
				//closes the newly created socket
				cleanup(newsockfd);
			}
		}

		// closes the parent socket
		cleanup(sockfd);
		cleanup(log_sockfd);
		return 0;
	}
	else
	{
		int sockfd, length, msglen;
		socklen_t fromlen;
		char buffer[1024];
		struct sockaddr_in server, from;
		int pid;
		// createSocket creates a new UDP socket and returns the filedescripor of the socket
		sockfd = createSocket(AF_INET, SOCK_DGRAM, 0);

		// setupAddr creates the connection between the server and the port
		setupAddr(server, portno);

		// setupBind connects the socket and the server together
		setupBind(sockfd, server);

		//the size of the sockaddr_in structure is used to determine the size of the received message
		fromlen = sizeof(struct sockaddr_in);
		while (1)
		{
			// setupRequest clears the buffer in between messages
			setupRequest(buffer, 1024);

			// recvfrom returns the number of characters read from the buffer, returns -1 on errors
			msglen = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *) &from, &fromlen);
			
			// creates a child process that will be used to handle the new request
			pid = fork();
			if (pid < 0)
			{
				error("ERROR on fork");
			}
			if (pid == 0) // the child is used to handle the request
			{
				if (msglen < 0)
				{
					error("UDP message length less than zero");
				}
				else if (msglen > 0)
				{
					// if msglen is positive then handle the recieved message
					time_t t = time(0);
					handleUDPRequest(sockfd, buffer, 1024, from, fromlen);

					logRequest(log_sockfd, log_serv_addr, log_length, from, t, buffer);
				}
				exit(0);
			}
		}
		// closes the socket when the program exits
		cleanup(sockfd);
		cleanup(log_sockfd);
		return 0;
	}

	return 0;
}
