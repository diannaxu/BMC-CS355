#include "../mem.h"
int main(){
    Mem_Init(4096);
    int * ptr;
    ptr = Mem_Alloc(16);
		if(ptr) *ptr = 255; // writing 0xff to byte
    Mem_Dump(); // should see 0xff
}