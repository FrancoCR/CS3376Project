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
#include <string>
// all of hthe functions required by the server to work are declared here
void writeToFile(char* towrite);
void error(const char *msg);
int createSocket(int domain, int type, int protocol);
int getPort(char * arg);
void setupAddr(struct sockaddr_in & serv_addr, int portno);
void setupBind(int sockfd, struct sockaddr_in & serv_addr);
void startListen(int sockfd, int count);
int awaitRequest(int sockfd, struct sockaddr_in & cli_addr, socklen_t & clilen);
void setupRequest(char buffer[], int size);
void handleUDPRequest(int sockfd, char buffer[], int size, struct sockaddr_in from, socklen_t fromlen);
void cleanup(int sock);
