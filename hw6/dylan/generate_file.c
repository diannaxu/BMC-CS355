#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DATA_REGION_SIZE 1073741824
#define BOOTBLOCK 512
#define SUPERBLOCK 512
#define BLOCKSIZE 512
#define BLOCKSIZE_PADDING 20000
#define N_DBLOCKS 10
#define N_IBLOCKS 4

#define INTSINBB 128

struct superblock {
	int size; /* size of blocks in bytes */
	int inode_offset; /* offset of inode region in blocks */
	int data_offset; /* data region offset in blocks */
	int swap_offset; /* swap region offset in blocks */
	int free_inode; /* head of free inode list, index */
	int free_block; /* head of free block list, index */
} superblock;

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
} inode;

struct bootblock {
	int bootstuff[INTSINBB];
} bootblock;

FILE *fp; 

int data_pointer = 0;
int int_num = 1;

int main()
{
	fp = fopen("large-file", "w+");

	printf(" * Proceeding to generate file with datasize %d\n", DATA_REGION_SIZE);
	printf(" * Data is ordered with lower level regions at end of the data section.  Data consists of a unique integer for each datablock \n");

	void *file = malloc(DATA_REGION_SIZE + sizeof(inode) + sizeof(superblock) + (BLOCKSIZE_PADDING * BLOCKSIZE));

	struct bootblock *bb = (struct bootblock *) (file);

	for (int i = 0; i < INTSINBB; ++i)
		bb->bootstuff[i] = -1;

	struct superblock *sb = (struct superblock *) (file + BOOTBLOCK);

	struct inode *in = (struct inode *) (file + BOOTBLOCK + SUPERBLOCK);

	sb->size = BLOCKSIZE;
	sb->inode_offset = 0;
	sb->data_offset = 1;

	// set swap offset to be larger than file length because it is not used
	// NOTE: this may cause failure for defraggers that expect swap offset within filelength
	sb->swap_offset = DATA_REGION_SIZE;

	in->next_inode = -1;
	in->protect = 1;
	in->nlink = 1;
	in->size = DATA_REGION_SIZE;
	in->uid = 10;
	in->gid = 10;
	in->ctime = 11;
	in->mtime = 15;
	in->atime = 10;

	// get the last block in the data region 
	data_pointer = (in->size / sb->size) + BLOCKSIZE_PADDING;

	// hold onto how much data we've managed to write
	int written_so_far = DATA_REGION_SIZE;

	for (int i = 1; i < ((sb->data_offset - sb->inode_offset) * sb->size) / sizeof(struct inode); ++i)
	{
		struct inode *t_in = (struct inode *) (file + BOOTBLOCK + SUPERBLOCK + (i * sizeof(struct inode)));
		t_in->next_inode = 0;
		t_in->protect = 0;
		t_in->nlink = 0; 
		t_in->size = 0;
		t_in->uid = 0; 
		t_in->gid = 0; 
		t_in->ctime =0 ; 
		t_in->mtime = 0; 
		t_in->atime = 0; 
		t_in->i2block = 0; 
		t_in->i3block = 0; 
	}

	// write direct block
	for (int i = 0; i < N_DBLOCKS; ++i)
	{
		if (written_so_far <= 0) 
			break;
		
		int this_rounds_ints[sb->size / sizeof(int)];

		for (int j = 0; j < sb->size / sizeof(int); ++j)
		{
			this_rounds_ints[j] = int_num;
		}

		void *data_location = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);

		in->dblocks[i] = data_pointer;
		memcpy(data_location, &this_rounds_ints, sb->size);

		written_so_far-=sb->size;
		data_pointer--;
		int_num++;
	}

	// write indirect block
	for (int i = 0; i < N_IBLOCKS; ++i)
	{
		if (written_so_far <= 0)
			break;

		in->iblocks[i] = data_pointer;

		void *data_location = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);
		data_pointer--;

		for (int j = 0; j < sb->size / sizeof(int); ++j)
		{
			if (written_so_far <= 0)
				break;

			void *write_location = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset * sb->size) + (sb->size * data_pointer);
			
			int this_rounds_ints[sb->size / sizeof(int)];
			for (int k = 0; k < sb->size / sizeof(int); ++k)
				this_rounds_ints[k] = int_num;
		
			memcpy(write_location, &this_rounds_ints, sb->size);
			memcpy(data_location, &data_pointer, sizeof(int));

			written_so_far-=sb->size;
			data_location += sizeof(int);
			int_num++;
			data_pointer--;
		}
	}

	//write double block
	if (data_pointer > 0) {

		void *initial_double_block = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);
		
		in->i2block = data_pointer;

		data_pointer--;

		for (int i = 0; i < sb->size / sizeof(int); ++i)
		{
			if (written_so_far <= 0)
				break;

			void *data_location = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);
			memcpy(initial_double_block, &data_pointer, sizeof(int));
			data_pointer--;

			for (int j = 0; j < sb->size / sizeof(int); ++j)
			{
				if (written_so_far <= 0)
					break;

				void *write_location = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset * sb->size) + (sb->size * data_pointer);
				
				int this_rounds_ints[sb->size / sizeof(int)];
				for (int k = 0; k < sb->size / sizeof(int); ++k)
					this_rounds_ints[k] = int_num;

				memcpy(write_location, &this_rounds_ints, sb->size);
				memcpy(data_location, &data_pointer, sizeof(int));

				written_so_far-=sb->size;
				int_num++;
				data_location += sizeof(int);
				data_pointer--;
			}
			initial_double_block += sizeof(int);
		}
	}

	// write triple block
	if (data_pointer > 0) {
		void *triple_block = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);
	
		in->i3block = data_pointer;
		data_pointer--;

		for (int i = 0; i < sb->size / sizeof(int); ++i)
		{
			if (written_so_far <= 0)
				break;

			void *middle = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset *sb->size) + (sb->size * data_pointer);
			memcpy(triple_block, &data_pointer, sizeof(int));
			data_pointer--;

			for (int j = 0; j < sb->size / sizeof(int); ++j)
			{
				if (written_so_far <= 0)
					break;

				void *data_block = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset * sb->size) + (sb->size * data_pointer);

				memcpy(middle, &data_pointer, sizeof(int));
				data_pointer--;

				for (int k = 0; k < sb->size / sizeof(int); ++k)
				{
					if (written_so_far <= 0) {
						break;
					}

					void *data = file + BOOTBLOCK + SUPERBLOCK + (sb->data_offset * sb->size) + (sb->size * data_pointer);

					int this_rounds_ints[sb->size / sizeof(int)];
					for (int z = 0; z < sb->size / sizeof(int); ++z)
						this_rounds_ints[z] = int_num;

					memcpy(data_block, &data_pointer, sb->size);
					memcpy(data, &this_rounds_ints, sb->size);

					written_so_far-=sb->size;
					int_num++;
					data_pointer--;
					data_block += sizeof(int);
				}
				middle += sizeof(int);
			}
			triple_block += sizeof(int);
		}			

	}

	fwrite(file, DATA_REGION_SIZE + sizeof(inode) + sizeof(superblock) + (BLOCKSIZE_PADDING * BLOCKSIZE), 1, fp);

	free(file);
}
