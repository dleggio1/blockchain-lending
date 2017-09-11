#include "block.h"

block* genesisBlock;
block* latestBlock;

int main(int argc, char **argv)
{
	// create hard-coded genesis block
	genesisBlock = malloc(sizeof(block));
	genesisBlock->index = 0;
	genesisBlock->timestamp = time(NULL);
	genesisBlock->data = "Genesis Block.";
	genesisBlock->hash = "d8a005a48ea046d008272e3a68e16b406dcd4b8fc40dfc06c2fcb6f46508d04d";
	genesisBlock->prevHash  = "0";
	latestBlock = genesisBlock;
	
	block* test = generateBlock("dyl");
	printf("index -> %d\n", test->index);
	printf("timestamp -> %s", ctime(&(test->timestamp)));
	printf("data -> %s\n", test->data);
	printf("hash -> %s\n", test->hash);
	printf("prevHash -> %s\n", test->prevHash);


	return 0;
}

block* generateBlock(char *data)
{
	// get block attributes
	unsigned int index = latestBlock->index + 1;
	time_t timestamp = time(NULL);
	
	// generate SHA256 hash of block 
	unsigned char digest[SHA256_DIGEST_LENGTH];
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, &index, 1);
	SHA256_Update(&ctx, ctime(&timestamp), strlen(ctime(&timestamp)));
	SHA256_Update(&ctx, data, strlen(data));
	SHA256_Update(&ctx, latestBlock->hash, strlen(latestBlock->hash));
	SHA256_Final(digest, &ctx);

	// allocate new block
	block* newBlock = (block*) malloc(sizeof(block));
	newBlock->index = index;
	newBlock->timestamp = timestamp;
	newBlock->data = malloc(strlen(data) + 1);
	newBlock->data = data;
	newBlock->hash = malloc(strlen(digest) + 1);
	newBlock->hash = digest;
	newBlock->prevHash = malloc(strlen(latestBlock->hash) + 1);
	newBlock->prevHash = latestBlock->hash;

	latestBlock = newBlock;
	return newBlock;
}
