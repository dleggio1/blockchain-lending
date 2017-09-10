#include "block.h"

block* latestBlock;

int main(int argc, char **argv)
{
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
	SHA256_Update(&ctx, (unsigned char*) index, strlen((unsigned char*) index));
	SHA256_Update(&ctx, (unsigned char*) timestamp, strlen((unsigned char*) timestamp));
	SHA256_Update(&ctx, data, strlen(data));
	SHA256_Update(&ctx, latestBlock->hash, strlen(latestBlock->hash));
	SHA256_Final(digest, &ctx);

	// allocate new block
	block* newBlock = (block*) malloc(sizeof(block));
	newBlock->index = index;
	newBlock->timestamp = timestamp;
	newBlock->data = data;
	newBlock-> hash = digest;
	newBlock-> prevHash = latestBlock->hash;

	return newBlock;
}
