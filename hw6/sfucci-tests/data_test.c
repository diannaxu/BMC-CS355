#include "structs.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_DONE -1
#define IGNR_BLOCKS 1
#define NO_IGNR_BLOCKS 0

FILE * extract_data(char*, char *);

int write_block(int, FILE *, void *);
void write_direct_blocks(int, int[], FILE *, void *);
void write_indirect_blocks(int, int[], FILE *, void *);
int write_indirect_block(int, FILE *, void *);
int write_second_indirect_block(int, FILE *, void *);
int write_third_indirect_block(int, FILE *, void *);

int file_size = -1;
int n_blocks_left;
int blocksize;
int inode_region_size;
int data_region_size;
int data_region_start;
int swap_region_start;

/*
Writes the data contents of both the original file
and the new file to a two files. If the defragmentation is 
successful, then there should be no difference between the two files.
*/

int main(int argc, char ** argv){
  if(argc!= 3){
    printf("Usage: ./data_test orig_image new_image\n");
    return -1;
  }
  
  FILE * orig_data_file = extract_data(argv[1], "orig-data");
  //printf("\n\nNew data file\n\n");
  FILE * new_data_file = extract_data(argv[2], "new-data");
  return 0;
}

FILE* extract_data(char * old_filename, char * new_filename){
  FILE * tmp_file = fopen(old_filename, "r");
  if(tmp_file == NULL) return NULL;

  if(file_size == -1){
    int seek = fseek(tmp_file, 0, SEEK_END);
    if(seek != 0){
      printf("Seek returned with errno: %d\n", errno);
      return NULL;
    }

    file_size = (int) ftell(tmp_file);

    //https://www.youtube.com/watch?v=2rnO3fU5Pf8
    rewind(tmp_file);
  }

  void * data_ptr = malloc(file_size);
  fread(data_ptr, 1, file_size, tmp_file);


  struct superblock * sblock = (struct superblock *)(data_ptr + 512);

  int sblock_offset = 1024;
  blocksize = sblock->size;

  int inode_region_start = sblock_offset + (blocksize * sblock->inode_offset);
  data_region_start = sblock_offset + (blocksize * sblock ->data_offset);
  swap_region_start = sblock_offset + (blocksize * sblock ->swap_offset);

  data_region_size = swap_region_start - data_region_start;
  FILE * data_region_file = fopen(new_filename, "w+");
  
  void * inode_start = data_ptr + inode_region_start;
  //  void * data_start = data_ptr+ data_region_start;

  inode_region_size = data_region_start - inode_region_start;

  for(void * current_inode = inode_start; current_inode < (inode_start + inode_region_size); current_inode += sizeof(struct inode)){
    struct inode * in = (struct inode *) current_inode;
   
    
    int used = in->nlink != 0;
    if(used){
      if(in->size % blocksize == 0){
	n_blocks_left = in->size/blocksize;
      }else{
	n_blocks_left = (in->size/blocksize)+1;
      }
      write_direct_blocks(N_DBLOCKS, in->dblocks,data_region_file, data_ptr);
      if(n_blocks_left > 0){
	write_indirect_blocks(N_IBLOCKS, in->iblocks, data_region_file,data_ptr);
	if(n_blocks_left > 0){
	  	  write_second_indirect_block(in->i2block, data_region_file, data_ptr);
	  if(n_blocks_left > 0){
	    	    write_third_indirect_block(in->i3block, data_region_file, data_ptr);
	  }
	}
      }
    }
    
  }
  
  free(data_ptr);
  return data_region_file;
}

/*
  Writes a block, at address block_addr, to the file that solely contains the data
*/
int write_block(int block_addr, FILE * data_region, void * file_ptr){
  if(n_blocks_left <= 0)return FILE_DONE;
  
  fwrite(file_ptr+data_region_start+(block_addr*blocksize), 1, blocksize,data_region);
  n_blocks_left--;

  //can uncomment debug
  //printf("wrote block#%d; %d blocks left\n", block_addr, n_blocks_left);
  return n_blocks_left;
}

/*
  Writes direct blocks of an inode to the data file
*/
void write_direct_blocks(int nblocks, int blocks[], FILE * data_region, void * file_ptr){
  for(int i = 0; i < nblocks; i++){
    if(n_blocks_left <= 0){
      break;
    }
    //assert(blocks[i] >= data_region_start && blocks[i] < swap_region_start);
    write_block(blocks[i], data_region, file_ptr);
  }
}

/*
  Writes an indirect block to the data file
*/
int write_indirect_block(int block_addr, FILE * data_region, void * file_ptr){
  if(n_blocks_left <= 0) return FILE_DONE;

  void * block_start = file_ptr + data_region_start+ (block_addr*blocksize);
  int npointers = blocksize/4;
  
  for(int i = 0; i < npointers; i++){
    int ptr = *((int *) block_start);

    if(write_block(ptr, data_region, file_ptr) == FILE_DONE){
       return FILE_DONE;
      //break;
    }
    assert(ptr < data_region_size);
    block_start+=4;
  }
  return n_blocks_left;
}

/*
  Writes indirect blocks from the inode to the data file
*/
void write_indirect_blocks(int nblocks, int blocks[], FILE * data_region, void * file_ptr){
  if(n_blocks_left <=0) return;

  for(int i = 0; i < nblocks; i++){
    assert(blocks[i] <= data_region_size);
    if(write_indirect_block(blocks[i], data_region, file_ptr) == FILE_DONE){
      break;
    }
  }
}

/*
  Writes second indirect block located at block_addr to the data file
*/
int write_second_indirect_block(int block_addr, FILE * data_region, void * file_ptr){
  if(n_blocks_left <= 0) return FILE_DONE;
  
  void * block_start = file_ptr + data_region_start + (block_addr*blocksize);
  int npointers = blocksize/4;

  for(int i = 0; i < npointers; i++){
    //void * current_ptr = block_start;
    int ptr = (*(int *)block_start);
    //assert(ptr >= data_region_start && ptr < swap_region_start);

    if(write_indirect_block(ptr, data_region, file_ptr) == FILE_DONE){
      return FILE_DONE;
    }
    block_start+=4;
  }
  return n_blocks_left;
}

/*
  Writes third indirect block located at block_addr to the data file
*/
int write_third_indirect_block(int block_addr, FILE * data_region, void * file_ptr){
  if(n_blocks_left <= 0) return FILE_DONE;

  void * block_start = file_ptr + data_region_start+ (block_addr*blocksize);
  int npointers = blocksize/4;

  for(int i = 0; i < npointers; i++){
    //    void * current_ptr = block_start;
    int ptr = (*(int *)block_start);
    //assert(ptr >= data_region_start && ptr < swap_region_start);
    if(write_second_indirect_block(ptr, data_region, file_ptr) == FILE_DONE){
      return FILE_DONE;
    }
    block_start+=4;
  }
  return n_blocks_left;
}
