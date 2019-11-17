//inode_sanity_test.c
//Checks that the i-node array of a disk image is sane, specifically that each inode entry is either free (in the free list, and has nlink value 0) or in use (not in the free list, and has nlink value >=1).
//Expected behavior: prints the number of inodes, the inodes in the free list, the bitmap of inodes in the free list (really an intmap), and runs to completion after successfully asserting the condition above for each inode. 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "defrag.h"
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

  // Cast the appropriate memory region to a list of i-nodes 
  struct inode (*inode_array)[num_inodes] = ((struct inode (*)[num_inodes]) (disk_image + inode_region_start)); 

  // Iterate through free list, and mark those i-nodes as free
  // Make bitmap and initialize to all false
  int free_bitmap[num_inodes];
  for(int i=0; i<num_inodes; i++){
    free_bitmap[i] = FALSE; 
  }

  // Iterate through free list, printing indices and marking bitmap entries
  printf("Indices of i-nodes in free list:\n"); 
  int curr_free_node_index = free_inode;
  while(curr_free_node_index != -1){
    printf("%d\n", curr_free_node_index); 
    struct inode* curr_free_inode = &((*inode_array)[curr_free_node_index]);
    free_bitmap[curr_free_node_index] = TRUE;
    curr_free_node_index = curr_free_inode->next_inode; 
  }

  // Print bitmap values
  printf("Bitmap (intmap) of i-nodes, free i-nodes marked with 1:\n"); 
  for(int i=0; i<num_inodes; i++){
    printf("%d ", free_bitmap[i]);
  }
  printf("\n");

  // Check that each node is either free or in use (has nlink >= 1)
  for(int i=0; i<num_inodes; i++){
    struct inode* curr_inode = &((*inode_array)[i]);
    // this works as exclusive or
    assert(free_bitmap[i]? (curr_inode->nlink == 0) : (curr_inode->nlink >= 0)); 
  }

  printf("Successfully asserted that each i-node is either free or in use; exiting\n"); 
  
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

void print_inode(struct inode* inode_addr){
  printf("Next inode: %d\n", inode_addr->next_inode);
  printf("Protect: %d\n", inode_addr->protect);
  printf("Nlink: %d\n", inode_addr->nlink);
  printf("Size: %d\n", inode_addr->size);
  printf("Uid: %d\n", inode_addr->uid);
  printf("Gid: %d\n", inode_addr->gid);
  printf("Ctime: %d\n", inode_addr->ctime);
  printf("Mtime: %d\n", inode_addr->mtime);
  printf("Atime: %d\n", inode_addr->atime);
  for(int i=0; i<N_DBLOCKS; i++){
    printf("Dblock %d: %d\n", i, inode_addr->dblocks[i]); 
  }
  for(int i=0; i<N_IBLOCKS; i++){
    printf("Iblock %d: %d\n", i, inode_addr->iblocks[i]);
  }
  printf("i2block: %d\n", inode_addr->i2block);
  printf("i3block: %d\n", inode_addr->i3block); 
}

/*
// Given the address of an i-node on the fragmented disk image,
// this function copies its non-data block attributes into the appropriate i-node in the new disk image,
// then iterates through its data blocks, copying them in a condensed manner into the new data block
// and writing their new addresses into the new i-node 
void condense_inode(struct inode* old_inode, struct inode* new_inode){
  // Copy basic attributes into new i-node
  new_inode->next_inode = old_inode->next_inode;
  new_inode->protect = old_inode->protect;
  new_inode->nlink = old_inode->nlink;
  new_inode->size = old_inode->size;
  new_inode->uid = old_inode->uid;
  new_inode->gid = old_inode->gid;
  new_inode->ctime = old_inode->ctime;
  new_inode->mtime = old_inode->mtime;
  new_inode->atime = old_inode->atime;
  new_inode->i2block = 0;
  new_inode->i3block = 0; 
  
  // Zero out dblocks and iblocks arrays in new i-node
  for(int i=0; i<N_DBLOCKS; i++){
    new_inode->dblocks[i] = 0;
  }
  for(int i=0; i<N_IBLOCKS; i++){
    new_inode->iblocks[i] = 0; 
  }
			     
  // Calculate number of file blocks used by old i-node
  long inode_num_blocks; 
  if(old_inode->size % block_size == 0){
    inode_num_blocks = old_inode->size/block_size; 
  } else {
    inode_num_blocks = old_inode->size/block_size + 1; 
  }
  printf("Inode num blocks: %ld\n", inode_num_blocks);

  int blocks_copied = 0;
  // Copy and condense each direct block 
  for(int i=0; blocks_copied<inode_num_blocks && i<N_DBLOCKS; i++){
    // Copy block 
    int copied_block_addr = copy_block(old_inode->dblocks[i]);
    
    // Add new ptr in new i-node
    new_inode->dblocks[i] = copied_block_addr;
    blocks_copied++; 
  }

  // Handle single indirect blocks
  for(int i=0; blocks_copied<inode_num_blocks && i<N_IBLOCKS; i++){
    if(inode_num_blocks - blocks_copied > (block_size/sizeof(int))){
      new_inode->iblocks[i] = condense_single_indirect_block(old_inode->iblocks[i], block_size/sizeof(int));
      blocks_copied += block_size/sizeof(int); 
    } else {
      new_inode->iblocks[i] = condense_single_indirect_block(old_inode->iblocks[i], inode_num_blocks-blocks_copied);
      blocks_copied = inode_num_blocks; 
    }
  }

  // TODO: handle double and triple indirect blocks
} 

// Takes: the block index of a single indirect block, and the number of pointers to copy from that block 
int condense_single_indirect_block(int source_block, int num_to_copy){
  // Condense the contents of a single indirect block,
  // writing the indirect block first, followed by the blocks it points to,
  // into the next free blocks in the new disk image
  // return the block number of the indirect block itself

  // Get address of single indirect block in original disk image 
  void* block_addr = disk_image + data_region_start + (source_block * block_size);
  int* i_src = (int*) block_addr; 
  // Get address of the block we will write the new single indirect block to 
  int* indirect_block_new = (int*) (new_data + (block_size * next_new_free_block));
  int to_return = next_new_free_block;
  next_new_free_block++;
  
  for(int i=0; i<num_to_copy; i++){
    indirect_block_new[i] = copy_block(i_src[i]);   
  }
  for(int i=num_to_copy; i<block_size/sizeof(int); i++){
    indirect_block_new[i] = 0; 
  }

  return to_return; 
}

// Copies block_size bytes of data from block source_block to the next free block in the new data segment
// Returns the block number to which it was written 
int copy_block(int source_block){

  // Get actual pointer to correct address in disk_image from data block #
  void* block_addr = disk_image + data_region_start + (source_block * block_size); 
  
  char* c_src = (char*) block_addr; 
  char* dest = (char*) (new_data + (block_size * next_new_free_block)); 
  for(int i=0; i<block_size; i++){
    dest[i] = c_src[i]; 
  }
  next_new_free_block++;
  return next_new_free_block - 1; 
}
*/
