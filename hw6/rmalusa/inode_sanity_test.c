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

void print_inode(struct inode* inode_addr, int unused){
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

