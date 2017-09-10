all: block

block: block.o block.h
	gcc block.o -o block -lssl -lcrypto

block.o: block.c block.h
	gcc -c block.c

clean:
	rm -rf *.o block
	
