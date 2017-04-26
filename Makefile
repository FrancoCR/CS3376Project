#Makefile for "SecondDel"
#Created by Katherine hartman 4/11/2017

PROG = echo_c
PROG2 = echo_s
PROG3 = log_s
OBJS = echo_c.o echo_c_functions.o
OBJS2 = echo_s.o echo_s_functions.o
OBJS3 = log_s.o log_s_functions.o
CPP = echo_c.c echo_c_functions.c
CPP2 = echo_s.c echo_s_functions.c
CPP3 = log_s.c log_s_functions.c

$(PROG) $(PROG2) $(PROG3):$(OBJS) $(OBJS2) $(OBJS3)
	g++ -o $(PROG) $(OBJS)
	g++ -o $(PROG2) $(OBJS2)
	g++ -o $(PROG3) $(OBJS3)
$(OBJS) $(OBJS2) $(OBJS3):$(CPP) $(CPP2) $(CPP3)
	g++ -c $(CPP)
	g++ -c $(CPP2)
	g++ -c $(CPP3)
clean:
	rm -rf $(PROG) $(PROG2) $(PROG3) $(OBJS) $(OBJS2) $(OBJS3)
