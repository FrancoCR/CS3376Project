#include "echo_s_functions.h"

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

// whenever a TCP message is received, prints that message and responds to the sender
void handleRequest(int sockfd, int newsockfd, char buffer[], int size)
{
	int n = read(newsockfd, buffer, size - 1);
	if (n < 0)
		error("ERROR reading from socket");
	printf("Received a TCP message: %s", buffer);
	n = write(newsockfd, buffer, size -1);
	if (n < 0)
		error("ERROR writing to socket");
}

// whenever a UDP message is recieved prints that message and responds to the sender
void handleUDPRequest(int sockfd, char buffer[], int size, struct sockaddr_in & from, socklen_t & fromlen)
{
	write(1, "Received a UDP message: ", 24);
	write(1, buffer, size);
	int n = sendto(sockfd, buffer, size, 0, (struct sockaddr *) &from, fromlen);
	if (n < 0)
		error("ERROR writing to socket");
}

//closes the specified socket
void cleanup(int sock)
{
	close(sock);
}
//logs the message info to the log server
void logRequest(int log_sockfd, struct sockaddr_in & log_server, unsigned int log_length, struct sockaddr_in & from, time_t & time, char msg_buffer[])
{
	//set up a buffer to store the formatted date/time string
	char dt_buffer[20];
	//format the date/time string
	strftime(dt_buffer, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
	//convert to a c++ string for easier concatenation
	std::string txt(dt_buffer);
	//start concatenation with the rest of the log line
	txt = txt + "	\"";
	//set up a buffer to store the formatted ip addresss string
	char addr_buffer[INET_ADDRSTRLEN];
	//format the ip address to a string
	inet_ntop(AF_INET, &(from.sin_addr), addr_buffer, INET_ADDRSTRLEN);
	//convert to a c++ string for easier concatenation
	std::string addr(addr_buffer);
	//convert to a c++ string for easier concatenation
	std::string msg(msg_buffer);
	//strip off the \n from the end of the user's message because we don't want it
	msg = msg.substr(0, msg.size() - 1);

	//concatenate all the strings together in the required format.
	txt = txt + msg + "\" was received from " + addr + "\n";

	//set up a buffer to store the string in for the rest of the sending process
	char final_buffer[txt.length() + 1];

	//copy the constant contents of the c++ string to a modifiable copy buffer
	strcpy(final_buffer, txt.c_str());

	//send the text buffer to the logging server over UDP
	sendUDPRequest(final_buffer, log_sockfd, log_server, log_length);
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

//setupConnection establishes the connection between the client and the server
void setupConnection(int sockfd, struct sockaddr_in & serv_addr)
{
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
}

// sends the UDP message to the specified server over the socket that has been created
void sendUDPRequest(char buffer[], int sockfd, struct sockaddr_in & server, unsigned int length)
{
	int n = sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &server, length);
	if (n < 0)
		error("ERROR writing to socket");
}