CXX=g++
CPPFLAGS=
LDFLAGS=
RM=rm -f

all: huffmunch

huffmunch: main.o huffmunch.o
	$(CXX) $(LDFLAGS) -o huffmunch main.o huffmunch.o

main.o: main.cpp huffmunch.h
	$(CXX) $(CPPFLAGS) -o main.o -c main.cpp

huffmunch.o: huffmunch.cpp huffmunch.h
	$(CXX) $(CPPFLAGS) -o huffmunch.o -c huffmunch.cpp

clean:
	$(RM) main.o
	$(RM) huffmunch.o
	$(RM) huffmunch
