#include "block.h"

block* genesisBlock;
block* latestBlock;

int main(int argc, char **argv)
{
	genesisBlock = latestBlock = getGenesisBlock();	

	// TEST BLOCK	
	block *test = generateBlock("dyl");
	printf("index -> %d\n", test->index);
	printf("timestamp -> %s", ctime(&(test->timestamp)));
	printf("data -> %s\n", test->data);
	printf("hash -> %s\n", test->hash);
	printf("prevHash -> %s\n", test->prevHash);

	return 0;
}

unsigned char *calculateHash(block *b)
{
	// generate SHA256 hash of block 
	unsigned char *digest = malloc(SHA256_DIGEST_LENGTH);
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, &(b->index), sizeof(int));
	SHA256_Update(&ctx, ctime(&(b->timestamp)), strlen(ctime(&(b->timestamp))));
	SHA256_Update(&ctx, b->data, strlen(b->data));
	SHA256_Update(&ctx, latestBlock->hash, strlen(latestBlock->hash));
	SHA256_Final(digest, &ctx);

	return digest;
}	

block* getGenesisBlock()
{
	// create hard-coded genesis block
	block *b = malloc(sizeof(block));
	b-> index = 0;
	b->timestamp = 1505659170;
	b->data = "Genesis Block.";
	b->hash = "d8a005a48ea046d008272e3a68e16b406dcd4b8fc40dfc06c2fcb6f46508d04d";
	b->prevHash  = "0";
	
	return b;
}

block *generateBlock(char *data)
{
	// get block attributes
	unsigned int index = latestBlock->index + 1;
	time_t timestamp = time(NULL);
	
	
	// allocate new block
	block* newBlock = (block*) malloc(sizeof(block));
	newBlock->index = index;
	newBlock->timestamp = timestamp;
	newBlock->data = malloc(strlen(data) + 1);
	strncpy(newBlock->data, data, strlen(data) + 1); // TODO: possible buffer overflow
	newBlock->hash = calculateHash(newBlock);
	newBlock->prevHash = latestBlock->hash;

	latestBlock = newBlock;
	return newBlock;
}

int isValidNewBlock(block* newBlock, block *latestBlock)
{
	if(newBlock->index != latestBlock->index + 1) return 0;
	else if(newBlock->prevHash != latestBlock->hash) return 0;
	else if(!strcmp(calculateHash(newBlock), newBlock->hash)) return 0;
	return 1;
}

void insert(block *genesis, block *b)
{
	if(!(genesis->next)) genesis->next = b;
	else insert(genesis->next, b);
}

int len(block *chain, int n)
{
	if(!chain) return n;
	else len(chain->next, n + 1);
}

int equals(block *a, block *b)
{
	if(a->index != b->index) return 0;
	else if(a->timestamp != b->timestamp) return 0;
	else if(strcmp(a->data, b->data)) return 0;
	else if(strcmp(a->hash, b->hash)) return 0;
	else if(strcmp(a->hash, b->hash)) return 0;
	else if(a->next != b->next) return 0;
	return 1;
}
