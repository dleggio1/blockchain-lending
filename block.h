#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

typedef struct {
	unsigned int index; // index of block in blockchain
	time_t timestamp; // time of creation
	char *data; // data of block
	unsigned char *hash; // SHA256 hash of block
	unsigned char *prevHash; // SHA256 hash of previous block	
	block *next;
} block;

unsigned char *calculateHash(block *b);

block *getGenesisBlock();

block *generateBlock(char *data);

int isValidNewBlock(block* newBlock);

void insert(block *genisis, block *b);

int len(block *chain, int n);

int equals(block *a, block *b);
