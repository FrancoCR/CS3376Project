Semester Project: cs 3376.501

Group 01: Brobdingnagian

Members:
	Franco Alejandro Covarrubias-Reyes-Lucio-Sanchez-Adame-Carrera-Chavez
	Ryan Glaser
	Kat Hartman
	Timothy Shiveley
	Carla Vazquez
	Max Winezerl

How To Use This Project:
	1. Enter the command "make" into the command line in the directory where all the files are located.
		a. This will compile all of the executables.
	2. Create a server
		a. type "./echo_s portno1 [portno2 portno3]" into the command line
		b. Where portno# are the ports you would like the server to run on
	3. Send requests to the server
		a. type "./echo_c -t/-u host portno" into the command line
		b. -t or -T mark the message as TCP
		c. -u or -U mark the message as UDP
		d. host is the name of the server and it's address ex: cs2.utdallas.edu
		e. portno is the port that the mesage needs to be sent on

Files Included:
	Filename 		- Dependencies
	echo.log		- none
	echo_c_functions.c	- echo_c_functions.h
	echo_c_functions.h	- arpa/inet.h, netdb.h, netinet/in.h, stdio.h, stdlib.h, string.h, sys/socket.h, sys/types.h, unistd.h
	echo_c.c		- echo_c_functions.h
	echo_s_functions.c	- echo_s_functions.h
	echo_s_functions.h	- netdb.h, netinet/in.h, signal.h, stdio.h, stdlib.h, string.h, sys/socket.h, sys/types.h, unistd.h
	echo_s.c		- echo_s_functions.h
	log_s_functions.c	- log_s_functions.h
	log_s_functions.h	- netdb.h, netinet/in.h, signal.h, stdio.h, stdlib.h, string.h, sys/socket.h, sys/types.h, unistd.h
	log_s.c			- echo.log, log_s_functions.h
	Makefile		- echo_c_functions.c, echo_c_functions.h, echo_c.c, echo_s_functions.c, echo_s_functions.h, echo_s.c, log_s_functions.c, log_s_functions.h, log_s.c
	readme.txt		- HUMANS

Second Deliverable:
	1. Write a network echo server, and an echo client, and a log server.
		a. The server will reply to any client on the same port that it receives a message
		b. The server will support both TCP and UDP on each port
		c. The server will run on a minumum of one port, and a maximum of three ports
		d. The server will be tested with the nc command
		e. The server will be able to handle multiple clients by creating new processes
		f. The server will send all requests it receives to the log server
			i. The IP address of the client
			ii. The timestamp the request was received
			iii. The message the server received
		g. The server will only send information to the log server on port 9999 using UDP
		h. The log server will store information in the file echo.log
	2. Comment the code to describe what the functions are doing.

Tasks Completed By:
	Franco Covarrubias:
		Task 1: Worked with max to setup up echo_s to be able to take multiple ports as arguments
		Task 2: Commented and edited the code accordingly
		Task 3: Ran necessary tests to ensure ports and arguments were being checked properly

	Ryan Glaser:
		Task 1: General Testing of clients and servers to make sure everything works the way it is required.
		Task 2: Testing using netcat as a client agaisnt echo_s, and as a a server agaisnt echo_c. 
		Task 3:

	Kat Hartman:
		Task 1: Modify copy of echo_s to produce base code for log_s by removing TCP code and setting up UDP code.
		Task 2: Comment and document project files.
		Task 3:

	Timothy Shiveley:
		Task 1: Add in -t and -u for client to determine whether to use TCP or UDP.
		Task 2: Organize and write readme and make sure project files are organized and commented.
		Task 3: 

	Carla Vazquez:
		Task 1: created the function to write messages sent to log_s.c to echo.log.
		Task 2: updated log_s_functions.c and log_s_functions.h and placed the function call in the necessary location in log_s.c
		Task 3:

	Max Winezerl:
		Task 1: Added logging transfer over UDP from the echo_s to the log_s, as well as message formatting.
		Task 2: Debugging for various small issues throughout the project.
		Task 3: Testing the executables with each other.
