Semester Project: cs 3376.501

Group 01: Brobdingnagian

GitHub Repository: https://github.com/FrancoCR/CS3376Project

Members:
	Franco Alejandro Covarrubias-Reyes-Lucio-Sanchez-Adame-Carrera-Chavez
	Ryan Glaser
	Kat Hartman
	Timothy Shiveley
	Carla Vazquez
	Maxwell Weinzierl

How To Use This Project:
	1. Enter the command "make" into the command line in the directory where all the files are located.
		a. This will compile all of the executables.
	2. Create a server
		a. type "./echo_s portno1 [portno2 portno3] [-logip ipaddr] [-logport portno]" into the command line
		b. Where portno# are the ports you would like the server to run on
		c. type "./log_s [-port portno]" into the command line to run the logging server on a specific port
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

Third Deliverable:
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
		g. The server will send information to the log server on a specified port, 
		   using 9999 by default using UDP
		h. The log server will store information in the file echo.log
		i. The log server can specify the port to listen on using command line parameters
		j. The server can specify the ip address for the log server with command line parameters
		k. The server can specify the port for the log server with command line parameters
		l. The log server will terminate when the echo server exits using an UDP message
		m. The log server will log when it exits from the echo server sending an exit message
	2. Comment the code to describe what the functions are doing.

Tasks Completed By:
	Franco Covarrubias: User 1 Task
		Task 1: Create Git repository with previous second deliverable files.
		Task 2: Add the "-logip ipaddr" feature to the echo_s so that a log server ip can be specified.
		Task 3: Document their changes to command line parameter parsing.

	Ryan Glaser: User 2 Task
		Task 1: Add the "-logport portno" feature to the echo_s so that a log server port can be specified.
		Task 2: Document their changes to command line parameter parsing.
		Task 3:

	Kat Hartman: User 3 Task
		Task 1: Add the "-port portno" feature to the log_s so that the log server can specify the port to listen on.
		Task 2: Document their changes to the command line parameter parsing.
		Task 3:

	Timothy Shiveley: User 4 Task
		Task 1: Add the feature to both the echo_s and log_s which causes the log_s to exit when the echo_s exits.
		Task 2: Rearrange the log variables to be extern in the .h files so that they can be used in the signal handler.
		Task 3: Document their changes to the variable locations and usages.

	Carla Vazquez: User 5 Task
		Task 1: Add the feature to the log_s which logs when it exits due to the echo_s exit message.
		Task 2: Test to make sure the log file is working with the new messages.
		Task 3: Document their changes to the logging structure.

	Maxwell Weinzierl: User 6 Task
		Task 1: Documented the project in the readme and made sure the git repository was being utilized correctly.
		Task 2: Debugging for various small issues throughout the project.
		Task 3: Testing the executables with each other with all the new features.
