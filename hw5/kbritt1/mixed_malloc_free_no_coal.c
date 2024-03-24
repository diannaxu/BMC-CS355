#include "../mem.h"
#include <stdlib.h>

int main(){
	printf("%d\n",Mem_Init(4096));

	int * ptr;
	for (int i =0; i < 103; i++){
		ptr = Mem_Alloc(16);
		if(ptr) *ptr = 255;
		else printf("NO MORE ROOOMM!");
		if(i%4 == 0 && ptr){
			printf("FREE ATTEMPT");
			Mem_Free(ptr,NULL);
		}
		
	}
	printf("free Status %d\n", Mem_Free(ptr, NULL));
	printf("sizeOfInt, %d", sizeof(int));
	mem_dump(); // should see lots of 0xff, also 1 free header every 4 alloced header

}