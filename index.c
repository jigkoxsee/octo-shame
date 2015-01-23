#include "stdio.h"
#include "string.h"
#include <glib.h>
#include "hash.c"


int fastHash(const char * data,int max){
	int hash=SuperFastHash(data,strlen(data));
	return hash%max;
}

int main(int argc, char const *argv[])
{
	printf("Hello param: %s\n",argv[1]);
	int newK=fastHash(argv[1],20);//SuperFastHash(argv[1],strlen(argv[1]));
	printf("newK %d\n",newK);
	return 0;
}