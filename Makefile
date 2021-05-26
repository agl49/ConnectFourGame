output: Project2Main-agl49.o Project2.o
	g++ Project2Main-agl49.o Project2.o -o output

Project2Main-agl49.o: Project2Main-agl49.cpp
	g++ -c -Wall -std=c++17 -g Project2Main-agl49.cpp

Project2-agl49.o: Project2.cpp Project2.h
	g++ -c -Wall -std=c++17 -g Project2.cpp

clean: 
	rm *.o output
