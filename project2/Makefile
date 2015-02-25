#		Makefile
#Author: Sietschie from Stack Overflow
#Source:
#http://stackoverflow.com/questions/9870297/makefile-to-compile-opencv-code-in-c-on-ubuntu-linux

#OpenCV flags and libraries
#FLAGS = `pkg-config --cflags opencv`
#LIBS = `pkg-config --libs opencv`

#Generic compilation
#% : %.cpp
#	g++ $(CFLAGS) $(LIBS) -o $@ $<

CC = gcc
CFLAGS = -g 

dash:	 dash.c cmdArgs.c
	$(CC) -o dash dash.c cmdArgs.c 

test:	test.c cmdArgs.c
	$(CC) -o $@ $< 


clean:	
	rm -f *.o core

cleanall:
	rm -f *.o dash core
