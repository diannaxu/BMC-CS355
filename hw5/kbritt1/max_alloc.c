#include <unistd.h>
#include <stdio.h>
#include"../mem.h"	
#define HSB 32 //header size in bytes
int main(){
	printf("%d\n",Mem_Init(0));
	unsigned int * ptr;
	for (int i =0; i < 104; i++){
		printf("%d",i);
		ptr = Mem_Alloc(4);
		if(ptr)*ptr = 2882400171; // 0xabcdefab
		else printf("NO MORE ROOOMM!");
		
	}
	Mem_Dump();
    printf("expecting: %d 0xabcdefab in memdump", (getpagesize())/((HSB+8)));
}