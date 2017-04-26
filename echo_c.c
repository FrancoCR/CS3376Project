#include "echo_c_functions.h"

int main(int argc, char *argv[])
{
	if (argc < 4) //if the user does not enter the correct number of arguments
	{
		// using an extra command line arguments to differentiate between UDP and TCP
		error("usage ./echo_c -t/-T/-u/-U hostname port\n");
		exit(0);
	}
	if ((strcmp(argv[1], "-t") == 0) || (strcmp(argv[1], "-T") == 0)) //will execute if the message is TCP
	{
		int sockfd, portno;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		char buffer[256];
		portno = getPort(argv[3]);

		//createSocket creates a TCP socket and returns the socket's file descriptor
		sockfd = createSocket(AF_INET, SOCK_STREAM, 0);

		// getServer verifies the user specified server is reachable
		server = getServer(argv[2]);

		//setupAddr connects the host and the specified port
		setupAddr(serv_addr, server, portno);

		//setupConnection connects the socket file descriptor to the specified server
		setupConnection(sockfd, serv_addr);

		//prompts the user to input the message they want to send to the server
		getRequest(buffer, 256);

		//sends the message entered by the user to the server
		sendRequest(buffer, sockfd);

		//clears the buffer prior to recieving a response from the server
		setupResponse(buffer, 256);

		//waits for the server to send a response
		awaitResponse(buffer, 256, sockfd);

		//orints the server's response to the stdout
		handleResponse(buffer);

		//closes the socket that was used for this communication
		cleanup(sockfd);
	}
	else if ((strcmp(argv[1], "-u") == 0) || (strcmp(argv[1], "-U") == 0)) //will execute if the message is UDP
	{
		int sockfd, msglen;
		unsigned int length;
		struct sockaddr_in serv_addr, from;
		struct hostent *server;
		char buffer[1024];

		// createSocket creates a UDP socket and returns that sockets file descriptor
		sockfd = createSocket(AF_INET, SOCK_DGRAM, 0);

		// getServer verifies the user specified server is reachable
		server = getServer(argv[2]);

		// setupUDPAddr connects the host and the specified port
		setupUDPAddr(serv_addr, server, getPort(argv[3]));

		//setupConnection connects the socket file descriptor to the specified server
		setupConnection(sockfd, serv_addr);

		// the size of the sockaddr_in structure is used for both sendto and recvfrom commands
		length = sizeof(struct sockaddr_in);

		// promts the user to input the message tehy want to send to the server
		getRequest(buffer, 1024);

		// sends the message entered by the user to the server
		sendUDPRequest(buffer, sockfd, serv_addr, length);

		// clears the buffer prior to receiving a response from the server
		setupResponse(buffer, 1024);

		// waits for the server to send a response
		awaitUDPResponse(buffer, 1024, sockfd, from, length);

		// orints the servers response the stdout
		handleResponse(buffer);

		// closes the socket that was used for this communication
		cleanup(sockfd);
	}
	return 0;
}
