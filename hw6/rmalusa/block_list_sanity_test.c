
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "defrag.h"
#include "list_fns.h"
#include <assert.h>

#define SUCCESS 0 
#define ERROR -1
#define BOOTBLOCK_SIZE 512
#define SUPERBLOCK_SIZE 512
#define TRUE 1
#define FALSE 0

int block_size; 
void* disk_image; 

long file_size;            // The total size of the fragmented file 
int inode_offset;          // The offset in blocks between byte 1024 and the start of the inode region
int data_offset;           // The offset in blocks between byte 1024 and the start of the data region
int swap_offset;           // The offset in blocks between byte 1024 and the start of the swap region 
int free_inode;            // The index of the i-node that is the head of the free i-node list in the fragmented file 
int free_block;            // The index of the block that is the head of the free block list in the fragmented file 
long inode_region_size;    // The size of the inode region in bytes 
long data_region_size;     // The size of the data region in bytes 
long swap_region_size;     // The size of the swap region in bytes 
int num_inodes;            // The number of entries in the i-node array 
int num_datablocks;        // The number of data blocks in the data region 
long inode_region_start;   // The difference, in bytes, between the start of the inode region and the start of the file
long swap_region_start;    // The difference, in bytes, between the start of the swap region and the start of the file
long data_region_start;    // The difference, in bytes, between the start of the data region and the start of the file 


// Given an i-node, marks each data block it uses by adding 1 to its entry in the data map
//void mark_inode_block_indices(struct inode* node, int* data_map);

int main(int argc, char* argv[]){
  
  // Expected structure of arguments:
  // executable name + file name 
  if(argc != 2){
    printf("Please enter the file name of the disk image to check as an argument\n");
    exit(EXIT_FAILURE); 
  }

  // Copy disk image contents into a malloc'd region
  disk_image = get_file_contents(argv[1], &file_size); 

  // Cast the appropriate section of memory to a struct superblock* to get access to the superblock 
  struct superblock* superblock_ptr = (struct superblock*) ((char*)disk_image + BOOTBLOCK_SIZE); 
  
  block_size = superblock_ptr->size;
  inode_offset = superblock_ptr->inode_offset;
  data_offset = superblock_ptr->data_offset;
  swap_offset = superblock_ptr->swap_offset;
  free_inode = superblock_ptr->free_inode;
  free_block = superblock_ptr->free_block;
  
  // Calculate the size of each region (except superblock and boot block, which are fixed) 
  inode_region_size = (data_offset - inode_offset) * block_size;
  inode_region_start = (inode_offset * block_size) + BOOTBLOCK_SIZE + SUPERBLOCK_SIZE; 
  data_region_size = (swap_offset - data_offset) * block_size;
  data_region_start = (data_offset * block_size) + BOOTBLOCK_SIZE + SUPERBLOCK_SIZE; 
  swap_region_size = file_size - ((swap_offset * block_size) + BOOTBLOCK_SIZE + SUPERBLOCK_SIZE);
  swap_region_start = ((swap_offset * block_size) + BOOTBLOCK_SIZE + SUPERBLOCK_SIZE); 

  // Calculate number of i-nodes and data blocks
  num_inodes = inode_region_size / sizeof(struct inode); 
  num_datablocks = swap_offset - data_offset; 
  printf("Inode region size %d\n", inode_region_size);
  printf("Size of inode %d\n", sizeof(struct inode)); 
  printf("Num inodes %d\n", num_inodes); 

  // Make map that will track status of every data block
  // and initialize it to 0 
  int data_map[num_datablocks];
  for(int i=0; i<num_datablocks;i++){
    data_map[i] = 0; 
  }
  
  // Cast the appropriate memory region to a list of i-nodes 
  struct inode (*inode_array)[num_inodes] = ((struct inode (*)[num_inodes]) (disk_image + inode_region_start)); 

  // Iterate through the array of i-nodes
  // For each one, we will mark each block it uses
  for(int i=0; i<num_inodes; i++){
    struct inode* curr_inode = &((*inode_array)[i]);
    if(curr_inode->nlink >= 1){
        
      int num_data_blocks_in_list = 0; 
      int* list_of_data_blocks = list_of_blocks(curr_inode, TRUE, &num_data_blocks_in_list);
      for(int k=0; k<num_data_blocks_in_list; k++){
        data_map[list_of_data_blocks[k]] += 1; 
      } 
      free(list_of_data_blocks); 

      //mark_inode_block_indices(curr_inode, data_map); 
    }
  }

  // Now we iterate through the free block list and mark each of those blocks
  printf("%d\n", free_block); 
  int curr_free_block_index = free_block;
  data_map[curr_free_block_index] += 1; 
  void* curr_free_block_addr = disk_image + data_region_start + (curr_free_block_index * block_size); 
  int* i_src = (int*) curr_free_block_addr;
  printf("%d\n", *i_src); 
  while(*i_src != -1){
    printf("%d\n", *i_src); 
    data_map[*i_src] += 1;
    curr_free_block_index = *i_src;
    curr_free_block_addr = disk_image + data_region_start + (curr_free_block_index * block_size);
    i_src = (int*) curr_free_block_addr; 
  }

  /*
  for(int i=0; i<num_datablocks; i++){
    if(data_map[i] != 1){
      printf("%d, %d\n", i, data_map[i]); 
    }
    //assert(data_map[i] == 1); 
  }
  */ 
  
  printf("Successfully asserted block list sanity; exiting\n"); 
  
  //free(superblock_raw); 
  // Free the array that was used to store the disk image 
  free(disk_image);
  exit(EXIT_SUCCESS); 
}

// Copies the contents of the fragmented file to
// a malloc'd region and returns the pointer to it,
// as well as putting the file size in the variable file_size 
void* get_file_contents(char* filename, long* file_size){
  
  // Open the fragmented disk image file
  FILE* disk_image_file = fopen(filename, "r");
  if(!disk_image_file){
    printf("Invalid file name\n");
    exit(EXIT_FAILURE); 
  }
  
  // Calculate the file size and allocate space for it in memory 
  if(fseek(disk_image_file, 0L, SEEK_END) == ERROR){
    printf("Fseek error\n");
    exit(EXIT_SUCCESS); 
  }
  *file_size = ftell(disk_image_file);
  if(*file_size == ERROR){
    printf("Ftell error\n");
    exit(EXIT_SUCCESS); 
  }
  
  void* disk_image = malloc(*file_size); 

  // Rewind the pointer to the beginning of the file
  rewind(disk_image_file); 
  
  // Read disk image into memory
  size_t disk_read = fread(disk_image, 1, *file_size, disk_image_file);
  if(disk_read != *file_size || ferror(disk_image_file)){
    perror("Huh?"); 
    printf("Error reading disk image\n");
    exit(EXIT_FAILURE); 
  }
  
  // Close disk file handle
  fclose(disk_image_file);

  return disk_image; 
}

// Given the size of a file, returns the number of blocks needed to store it 
int size_to_num_blocks(int size){
  int inode_num_blocks; 
  if(size % block_size == 0){
    inode_num_blocks = size/block_size; 
  } else {
    inode_num_blocks = size/block_size + 1; 
  }
  return inode_num_blocks; 
}

// This function, given an i-node, returns a pointer to a malloc'd array of all its data block indices 
// If "include_indirect" is true, it also includes the single, double, and triple indirect blocks 
// It also stores the size of the malloc'd array in block_index_array_size 
int* list_of_blocks(struct inode* node, int include_indirect, int* block_index_array_size){
  
  int blocks = size_to_num_blocks(node->size); 
  *block_index_array_size = size_to_num_blocks(node->size);
  
  if(include_indirect){
    // How many indirect block indices must we add? 
    int blocks_stored_single_indirect = 0; 
    if(blocks>N_DBLOCKS){
      // For each chunk of block_size/sizeof(int) (128, usually) blocks after 10 but before we've used up all 4 single indirect blocks, we add one
      // First we calculate how many blocks are stored indirectly, between 0 and 4*capacity 
      blocks_stored_single_indirect = blocks - N_DBLOCKS; 
      if(blocks_stored_single_indirect > (block_size/sizeof(int)) * N_IBLOCKS){
        blocks_stored_single_indirect = (block_size/sizeof(int)) * N_IBLOCKS; 
      }
      // Then we calculate how many single indirect blocks are required for that 
      int single_indirect_blocks; 
      if(blocks_stored_single_indirect % block_size/sizeof(int) == 0){
        single_indirect_blocks = blocks_stored_single_indirect / (block_size/sizeof(int)); 
      } else {
        single_indirect_blocks = blocks_stored_single_indirect / (block_size/sizeof(int)) + 1; 
      }
      // We increase *block_index_array_size by that much
      *block_index_array_size += single_indirect_blocks; 
    }

    int blocks_stored_double_indirect = 0; 
    if(blocks > N_DBLOCKS + blocks_stored_single_indirect && node->i2block){
      // Calculate how many blocks can actually be stored double-indirect 
      blocks_stored_double_indirect = blocks - N_DBLOCKS - blocks_stored_single_indirect; 
      if(blocks_stored_double_indirect > (block_size/sizeof(int) * block_size/sizeof(int))){
        blocks_stored_double_indirect = (block_size/sizeof(int) * block_size/sizeof(int)); 
      }
      // Then we calculate how many single indirect blocks are required for that 
      int single_indirect_blocks; 
      if(blocks_stored_double_indirect % block_size/sizeof(int) == 0){
        single_indirect_blocks = blocks_stored_double_indirect / (block_size/sizeof(int)); 
      } else {
        single_indirect_blocks = blocks_stored_double_indirect / (block_size/sizeof(int)) + 1; 
      }

      // We increase *block_index_array_size by that much + 1 for the double indirect block 
      *block_index_array_size += single_indirect_blocks + 1; 
    }

    int blocks_stored_triple_indirect = 0; 
    if(blocks > N_DBLOCKS + blocks_stored_single_indirect + blocks_stored_double_indirect && node->i3block){
      // Calculate how many blocks can actually be stored triple-indirect 
      blocks_stored_triple_indirect = blocks - N_DBLOCKS - blocks_stored_single_indirect - blocks_stored_double_indirect; 
      if(blocks_stored_triple_indirect > (block_size/sizeof(int) * block_size/sizeof(int) * (block_size/sizeof(int)))){
        blocks_stored_triple_indirect = (block_size/(sizeof(int) * block_size/sizeof(int) * (block_size/sizeof(int)))); 
      }
      // Then we calculate how many single indirect blocks are required for that 
      int single_indirect_blocks; 
      if(blocks_stored_triple_indirect % block_size/sizeof(int) == 0){
        single_indirect_blocks = blocks_stored_triple_indirect / (block_size/sizeof(int)); 
      } else {
        single_indirect_blocks = blocks_stored_triple_indirect / (block_size/sizeof(int)) + 1; 
      }

      // And also how many double indirect blocks are required for that 
      int double_indirect_blocks; 
      if(blocks_stored_triple_indirect % (block_size/sizeof(int) * block_size/sizeof(int)) == 0){
        double_indirect_blocks = blocks_stored_triple_indirect / (block_size/sizeof(int) * block_size/sizeof(int)); 
      } else {
        double_indirect_blocks = blocks_stored_triple_indirect / (block_size/sizeof(int) * block_size/sizeof(int)) + 1; 
      }

      // Increase *block_index_array_size by that much + 1 for the triple indirect block 
      *block_index_array_size += single_indirect_blocks + double_indirect_blocks + 1; 
    }
  } 

  int* block_indices = malloc((*block_index_array_size) * sizeof(int)); 
  int block_indices_next_free = 0; 
  int blocks_copied = 0; 

  // Copy indices from direct blocks 
  for(int i=0; i<N_DBLOCKS && blocks_copied < blocks; i++){
    block_indices[block_indices_next_free] = node->dblocks[i]; 
    block_indices_next_free++; 
    blocks_copied++; 
  }

  // Copy indices from as many single indirect blocks as necessary 
  for(int i=0; i<N_IBLOCKS && blocks_copied < blocks; i++){
    list_single_indirect_block(node->iblocks[i], blocks, &blocks_copied, &block_indices, &block_indices_next_free, include_indirect); 
  }

  // Copy indices from double indirect block 
  if(blocks_copied<blocks && node->i2block){
    list_double_indirect_block(node->i2block, blocks, &blocks_copied, &block_indices, &block_indices_next_free, include_indirect);   
  }

  // Copy/condense triple indirect block if there are STILL blocks left
  // condense_triple_indirect_block will update blocks_copied 
  if(blocks_copied<blocks && node->i3block){
    list_triple_indirect_block(node->i3block, blocks, &blocks_copied, &block_indices, &block_indices_next_free, include_indirect);
  }

  return block_indices; 

}

// Given a malloc'd array and a next free index, copies the indices of all the blocks in a single-indrect block into that array
// If include_indirect is true, it also copies the index of the single indirect block itself 
void list_single_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int* block_indices_next_free, int include_indirect){
  
  // Get address of old single indirect block, as void* and as int array 
  void* single_indirect_block_addr = disk_image + data_region_start + (source_block * block_size);
  int* single_indirect_block_array = (int*) single_indirect_block_addr; 

  // calculate how many data blocks to copy - block size, or as many as are left 
  int blocks_to_copy = num_blocks - *blocks_copied; 
  if(blocks_to_copy > block_size/sizeof(int)){
    blocks_to_copy = block_size/sizeof(int); 
  }

  // Copy that many data blocks 
  for(int i = 0; i<blocks_to_copy; i++){
    (*block_indices)[*block_indices_next_free] = single_indirect_block_array[i];
    (*block_indices_next_free)++; 
  }

  // If include_indirect, copy the single indirect block itself 
  if(include_indirect){
    (*block_indices)[*block_indices_next_free] = source_block; 
    (*block_indices_next_free)++; 
  }

  // Update blocks_copied 
  *blocks_copied += blocks_to_copy; 
}
 
void list_double_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int*block_indices_next_free, int include_indirect){
  // Get address of old single indirect block, as void* and as int array 
  void* double_indirect_block_addr = disk_image + data_region_start + (source_block * block_size);
  int* double_indirect_block_array = (int*) double_indirect_block_addr; 

  // calculate how many data blocks to copy - block size squared, or as many as are left 
  int blocks_to_copy = num_blocks - *blocks_copied; 
  if(blocks_to_copy > (block_size/sizeof(int) * (block_size/sizeof(int)))){
    blocks_to_copy = block_size/sizeof(int) * block_size/sizeof(int); 
  }

  // Calculate how many single indirect blocks we will copy to reach that amount
  int i_blocks_to_copy; 
  if(blocks_to_copy % (block_size/sizeof(int)) == 0){
    i_blocks_to_copy = blocks_to_copy/(block_size/sizeof(int)); 
  } else {
    i_blocks_to_copy = blocks_to_copy/(block_size/sizeof(int)) + 1; 
  }

  // Copy that many single indirect blocks 
  for(int i = 0; i<i_blocks_to_copy; i++){
    // This will also increase blocks_copied 
    // so that the last one will copy correct number of blocks 
    list_single_indirect_block(double_indirect_block_array[i], num_blocks, blocks_copied, block_indices, block_indices_next_free, include_indirect); 
  }

  // If include_indirect, copy the index of the double indirect block itself also
  if(include_indirect){
    (*block_indices)[*block_indices_next_free] = source_block; 
    (*block_indices_next_free)++;     
  }

  // Blocks_copied has already been updated as we go, so no need to update it here as we do in condense_single_indirect 
}

void list_triple_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int* block_indices_next_free, int include_indirect){
  // Get address of old single indirect block, as void* and as int array 
  void* triple_indirect_block_addr = disk_image + data_region_start + (source_block * block_size);
  int* triple_indirect_block_array = (int*) triple_indirect_block_addr; 

  // calculate how many data blocks to copy - block size squared, or as many as are left 
  int blocks_to_copy = num_blocks - *blocks_copied; 

  if(blocks_to_copy > (block_size/sizeof(int) * (block_size/sizeof(int) * (block_size/sizeof(int))))){
    blocks_to_copy = block_size/sizeof(int) * block_size/sizeof(int) * block_size/sizeof(int); 
  }

  // Calculate how many double indirect blocks we will copy to reach that amount
  int di_blocks_to_copy; 

  if(blocks_to_copy % (block_size/sizeof(int) * block_size/sizeof(int)) == 0){
    di_blocks_to_copy = blocks_to_copy/(block_size/sizeof(int) * block_size/sizeof(int)); 
  } else {
    di_blocks_to_copy = blocks_to_copy/(block_size/sizeof(int) * block_size/sizeof(int)) + 1; 
  }

  // Copy that many double indirect blocks 
  for(int i = 0; i<di_blocks_to_copy; i++){
    // This will also increase blocks_copied 
    // so that the last one will copy correct number of blocks 
    list_double_indirect_block(triple_indirect_block_array[i], num_blocks, blocks_copied, block_indices, block_indices_next_free, include_indirect);   
  }

  // If include_indirect, include the index of this triple indirect block as well
  if(include_indirect){
    (*block_indices)[*block_indices_next_free] = source_block; 
    (*block_indices_next_free)++;     
  }

  // Blocks_copied has already been updated as we go, so no need to update it here as we do in condense_single_indirect 
}
