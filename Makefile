all: test

test: nmain.o sqlite3.o bdr.o bds.o sorts.o
	g++ nmain.o sqlite3.o bdr.o bds.o sorts.o -o test -ldl -lpthread
	
nmain.o: nmain.cpp
	g++ -c nmain.cpp
	
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
