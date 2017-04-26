#include "log_s_functions.h"

void writeToFile(char* towrite)
{
	FILE *file;

	file = fopen("echo.log", "a");
	fputs((const char *)towrite, file);
	fclose(file);
}

// returns an error to the user and exits the program
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

// creates a socket ofthe specified type, and returns the file descriptor of the created socket
int createSocket(int domain, int type, int protocol)
{
	int sockfd = socket(domain, type, protocol);
	if (sockfd < 0)
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

// assigns the port numer to the server object
void setupAddr(struct sockaddr_in & serv_addr, int portno)
{
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
}

// binds the socket and the server together
void setupBind(int sockfd, struct sockaddr_in & serv_addr)
{
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
	{
		error("ERROR on binding");
	}
}

// listens for a tcp request on the specified socket
void startListen(int sockfd, int count)
{
	listen(sockfd, count);
}

// accepts a connection from the client that requests one, and returns the socket file descriptor
int awaitRequest(int sockfd, struct sockaddr_in & cli_addr, socklen_t & clilen)
{
	int newsockfd = accept(sockfd,
		(struct sockaddr *) &cli_addr,
		&clilen);

	if (newsockfd < 0)
		error("ERROR on accept");

	return newsockfd;
}

//clears the contents of the buffer
void setupRequest(char buffer[], int size)
{
	bzero(buffer, size);
}

// whenever a UDP message is recieved prints that message and responds to the sender
void handleUDPRequest(int sockfd, char buffer[], int size, struct sockaddr_in from, socklen_t fromlen)
{
	write(1, "Received a UDP message: ", 24);
	write(1, buffer, size);
}

//closes the specified socket
void cleanup(int sock)
{
	close(sock);
}