#to run this file run in command line make
# example: ....$ make

# use here any compiler you want, for example g++
CC=g++
# specify the compiler flags here
# I added the c++14 standard
CFLAGS =--std=c++14 -Wall -Wextra -Wconversion
#specify ALL of your header files
DEPS = *.h catch.hpp
#specify ALL of your source files here with a .o ending
OBJ = *.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#specify your executable's name, here it is "TVS"
TVS: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	#cleans directory -> removes all .o files
	rm -f *.o
 
#congrats!! now you should be able to run your executable as follows on the command line
# ....$ ./$(name)

#If you don't use the makefile do this:
# ...$ g++ name.cpp --std=c++14
#...$ ./a.out
#
