// all of the libraries required for the server to function are included here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>
#include <ctime>
#include <string>
#include <arpa/inet.h>
// all of the functions required by the server to work are declared here
void error(const char *msg);
int createSocket(int domain, int type, int protocol);
int getPort(char * arg);
void setupAddr(struct sockaddr_in & serv_addr, int portno);
void setupBind(int sockfd, struct sockaddr_in & serv_addr);
void startListen(int sockfd, int count);
int awaitRequest(int sockfd, struct sockaddr_in & cli_addr, socklen_t & clilen);
void setupRequest(char buffer[], int size);
void handleRequest(int sockfd, int newsockfd, char buffer[], int size);
void handleUDPRequest(int sockfd, char buffer[], int size, struct sockaddr_in & from, socklen_t & fromlen);
void cleanup(int sock);
void sendUDPRequest(char buffer[], int sockfd, struct sockaddr_in & server, unsigned int length);
void setupConnection(int sockfd, struct sockaddr_in & serv_addr);
void setupUDPAddr(struct sockaddr_in & serv_addr, struct hostent * server, int portno);
struct hostent * getServer(char * arg);
void logRequest(int log_sockfd, struct sockaddr_in & log_server, unsigned int log_length, struct sockaddr_in & from, time_t & time, char msg[]);