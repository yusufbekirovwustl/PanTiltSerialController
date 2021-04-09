# Makefile for test main program
 
# *****************************************************
# Variables to control Makefile operation
 
#DEBUG	= -g -O0
DEBUG	= -O3
CC	= g++
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685
 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o InputParser.o PanCommand.o SaveCommand.o ViewCommand.o DeleteCommand.o LoadCommand.o SetCommand.o CoordinateCommander.o State.o StateSnapshot.o pwmController.o
	$(CC) $(CFLAGS) -o main main.o InputParser.o PanCommand.o SaveCommand.o ViewCommand.o DeleteCommand.o LoadCommand.o SetCommand.o CoordinateCommander.o State.o StateSnapshot.o pwmController.o $(LDFLAGS) $(LDLIBS)
 
main.o: main.cpp InputParser.h
	$(CC) $(CFLAGS) -c main.cpp $(LDFLAGS) $(LDLIBS)
 
InputParser.o: InputParser.cpp AbstractCommand.h
	$(CC) $(CFLAGS) -c InputParser.cpp $(LDFLAGS) $(LDLIBS)

State.o: State.cpp pwmController.h 
	$(CC) $(CFLAGS) -c State.cpp $(LDFLAGS) $(LDLIBS)

PanCommand.o: PanCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c PanCommand.cpp $(LDFLAGS) $(LDLIBS)

SaveCommand.o: SaveCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c SaveCommand.cpp $(LDFLAGS) $(LDLIBS)

ViewCommand.o: ViewCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c ViewCommand.cpp $(LDFLAGS) $(LDLIBS)

DeleteCommand.o: DeleteCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c DeleteCommand.cpp $(LDFLAGS) $(LDLIBS)

LoadCommand.o: LoadCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c LoadCommand.cpp $(LDFLAGS) $(LDLIBS)

SetCommand.o: SetCommand.cpp AbstractCommand.h CoordinateCommander.h
	$(CC) $(CFLAGS) -c SetCommand.cpp $(LDFLAGS) $(LDLIBS)

CoordinateCommander.o: CoordinateCommander.cpp State.h StateSnapshot.h
	$(CC) $(CFLAGS) -c CoordinateCommander.cpp $(LDFLAGS) $(LDLIBS)

StateSnapshot.o: StateSnapshot.cpp 
	$(CC) $(CFLAGS) -c StateSnapshot.cpp $(LDFLAGS) $(LDLIBS)

pwmController.o: pwmController.cpp
	$(CC) $(CFLAGS) -c pwmController.cpp $(LDFLAGS) $(LDLIBS)


 