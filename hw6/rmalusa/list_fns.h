// list_fns.h
// functions used for testing to list all the blocks used by an i-node 

#ifndef __LIST_FNS_H__
#define __LIST_FNS_H__

// This function, given an inode, returns a malloc'd array of ints containing its data blocks
// If "include_indirect" is true, it also includes the single, double, and triple indirect blocks 
// It also stores the size of the malloc'd array in block_index_array_size 
int* list_of_blocks(struct inode* node, int include_indirect, int* block_index_array_size); 

// Given a malloc'd array and a next free index, copies the indices of all the blocks in a single-indrect block into that array
// If include_indirect is true, it also copies the index of the single indirect block itself 
void list_single_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int* block_indices_next_free, int include_indirect);

void list_double_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int* block_indices_next_free, int include_indirect);

void list_triple_indirect_block(int source_block, int num_blocks, int* blocks_copied, int** block_indices, int* block_indices_next_free, int include_indirect);

#endif 