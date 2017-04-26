#include "echo_c_functions.h"

//error is called when a system call fails
void error(const char *msg)
{
	perror(msg);
	exit(0);
}

//createSocket creates the socket that will be used to communicate with the server
int createSocket(int domain, int type, int protocol)
{
	int sockfd = socket(domain, type, protocol); //socket() creates a new socket and returns a file descriptor
	if (sockfd < 0)//if -1 is returned an error has occured
		error("ERROR opening socket");
	return sockfd;
}

// parses the port number supplied by the user
int getPort(char * arg)
{
	int port = -1;
	try
	{
		port = atoi(arg);
	}
	catch(...)
	{
		error("ERROR invalid port number");
	}
	if (port == 0)
	{
		error("ERROR invalid port number");
	}
	return port;
}

//sets up the server and returns a hostnet struct pointer
struct hostent * getServer(char * arg)
{
	struct hostent * server = gethostbyname(arg);
	if (server == NULL) {
		error("ERROR, no such host\n");
		exit(1);
	}
	return server;
}

// setupAddr is used to create the sockaddr_in structure that is needed to communicate with the server
void setupAddr(struct sockaddr_in & serv_addr, struct hostent * server, int portno)
{
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
}

//setupConnection establishes the connection between the client and the server
void setupConnection(int sockfd, struct sockaddr_in & serv_addr)
{
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
}

//getRequest allows the client to create a message to send to the server
void getRequest(char buffer[], int size)
{
	printf("Please enter the message: ");
	bzero(buffer, size);
	fgets(buffer, size - 1, stdin);
}

//sends the TCP message to the specifed server over the socket that has been created
void sendRequest(char buffer[], int sockfd)
{
	int n = write(sockfd, buffer, strlen(buffer));
	if (n < 0)
		error("ERROR writing to socket");
}

// sets all the characters in the buffer to null
void setupResponse(char buffer[], int size)
{
	bzero(buffer, size);
}

//handles the reseption of information from the server
void awaitResponse(char buffer[], int size, int sockfd)
{
	int n = read(sockfd, buffer, size - 1);
	if (n < 0)
		error("ERROR reading from socket");
}

// prints the contents of the buffer to the stdout
void handleResponse(char buffer[])
{
	printf("%s\n", buffer);
}

// setupUDPAddr is used to create the sockaddr_in structure that is needed to communicate with the server
void setupUDPAddr(struct sockaddr_in & serv_addr, struct hostent * server, int portno)
{
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
}

// sends the UDP message to the specified server over the socket that has been created
void sendUDPRequest(char buffer[], int sockfd, struct sockaddr_in server, unsigned int length)
{
	int n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, length);
	if (n < 0)
		error("ERROR writing to socket");
}

// handles the reception of information from the server
void awaitUDPResponse(char buffer[], int size, int sockfd, struct sockaddr_in from, unsigned int length)
{
	int n = recvfrom(sockfd, buffer, size - 1, 0, (struct sockaddr *) &from, &length);
	if (n < 0)
		error("ERROR reading from socket");
}

//closes the sockfd file descriptor
void cleanup(int sockfd)
{
	close(sockfd);
}
