all: a.out 

a.out: main.o sqlite3.o bdr.o bds.o sorts.o
	g++ main.o sqlite3.o bdr.o bds.o sorts.o -o a.out -ldl -lpthread
	
nmain.o: main.cpp
	g++ -c main.cpp
	
sqlite3.o: sqlite3.c
	gcc -c sqlite3.c -ldl -lpthread
	
bdr.o: bdr.cpp
	g++ -c bdr.cpp

bds.o: bds.cpp
	g++ -c bds.cpp

sorts.o: sorts.cpp
	g++ -c sorts.cpp

clean:
	rm -rf *.o *.exe  
