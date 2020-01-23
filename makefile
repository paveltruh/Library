main : main.o library.o libraryview.o
	g++ main.o library.o libraryview.o -o main -std=c++14
main.o : main.cpp library.h libraryview.h
	g++ -c main.cpp -o main.o -std=c++14
library.o : library.h library.cpp
	g++ -c library.cpp -o library.o -std=c++14
libraryview.o : libraryview.h libraryview.cpp
	g++ -c libraryview.cpp -o libraryview.o -std=c++14
clean :
	del *.o main.exe
