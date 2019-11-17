#ifndef __DEFRAG_H__
#define __DEFRAG_H__

#define N_DBLOCKS 10
#define N_IBLOCKS 4

struct superblock {
  int size; /* size of blocks in bytes */
  int inode_offset; /* offset of inode region in blocks */
  int data_offset; /* data region offset in blocks */
  int swap_offset; /* swap region offset in blocks */
  int free_inode; /* head of free inode list, index */
  int free_block; /* head of free block list, index */
};

struct inode {
  int next_inode; /* index of next free inode */
  int protect; /* protection field */
  int nlink; /* number of links to this file */
  int size; /* numer of bytes in file */
  int uid; /* owner’s user ID */
  int gid; /* owner’s group ID */
  int ctime; /* change time */
  int mtime; /* modification time */
  int atime; /* access time */
  int dblocks[N_DBLOCKS]; /* pointers to data blocks */
  int iblocks[N_IBLOCKS]; /* pointers to indirect blocks */
  int i2block; /* pointer to doubly indirect block */
  int i3block; /* pointer to triply indirect block */
};

// Copies the contents of the fragmented file to
// a malloc'd region and returns the pointer to it
// as well as putting the file size in the variable file_size 
void* get_file_contents(char* filename, long* file_size);

void print_inode(struct inode* inode_addr);

// Given the address of an i-node on the fragmented disk image, and the address of a new i-node,
// this function copies its non-data block attributes into the appropriate i-node in the new disk image,
// then iterates through its data blocks, copying them in a condensed manner into the new data block
// and writing their new addresses into the new i-node 
void condense_inode(struct inode* old_inode, struct inode* new_inode);

int condense_single_indirect_block(int source_block, int num_to_copy);

// Copies block_size bytes of data from block source_block to the next free block in the new data segment
// Returns the block number to which it was written 
int copy_block(int source_block);


#endif 
