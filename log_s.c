#include "log_s_functions.h"

int main(int argc, char *argv[])
{
	int childpid = 0;

	int sockfd, length, msglen;
	socklen_t fromlen;
	char buffer[1024];
	struct sockaddr_in server, from;

	// createSocket creates a new UDP socket and returns the filedescripor of the socket
	sockfd = createSocket(AF_INET, SOCK_DGRAM, 0);

	// setupAddr creates the connection between the server and the port
	setupAddr(server, 9999);

	// setupBind connects the socket and the server together
	setupBind(sockfd, server);

	//the size of the sockaddr_in structure is used to determine the size of the received message
	fromlen = sizeof(struct sockaddr_in);
	int pid;
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
				handleUDPRequest(sockfd, buffer, 1024, from, fromlen);
				writeToFile(&buffer[0]);//function that writes to echo.log
			}
			exit(0);
		}
	}
	// closes the socket when the program exits
	cleanup(sockfd);
	return 0;
}
