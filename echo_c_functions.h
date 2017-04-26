// all of the libraries required for the client to function are included here
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
// all of the functins required by the client are declared here
void error(const char *msg);
int createSocket(int domain, int type, int protocol);
int getPort(char * arg);
struct hostent * getServer(char * arg);
void setupAddr(struct sockaddr_in & serv_addr, struct hostent * server, int portno);
void setupConnection(int sockfd, struct sockaddr_in & serv_addr);
void getRequest(char buffer[], int size);
void sendRequest(char buffer[], int sockfd);
void setupResponse(char buffer[], int size);
void awaitResponse(char buffer[], int size, int sockfd);
void handleResponse(char buffer[]);
void setupUDPAddr(struct sockaddr_in & serv_addr, struct hostent * server, int portno);
void sendUDPRequest(char buffer[], int sockfd, struct sockaddr_in server, unsigned int length);
void awaitUDPResponse(char buffer[], int size, int sockfd, struct sockaddr_in from, unsigned int length);
void cleanup(int sockfd);
int main(int argc, char *argv[]);
