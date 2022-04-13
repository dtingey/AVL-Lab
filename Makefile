TARGETS = AVLlab

CC = g++
CCFLAGS = -g -std=c++11

AVLlab:	main.cpp AVL.h AVL.cpp AVLInterface.h NodeInterface.h Node.h Node.cpp 
	$(CC) $(CCFLAGS)  -o AVLlab main.cpp AVL.cpp Node.cpp

