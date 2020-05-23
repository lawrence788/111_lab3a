// NAME: Guanqun Ma
// EMAIL: maguanqun0212@gmail.com
// ID: 305331164

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ext2_fs.h"

int image_fd;
struct ext2_super_block superBLK;
unsigned int block_size;

void SuperblockSummary()
{
    off_t offset = 1024; //for ext2: "primary copy of superblock is stored at offset of 1024 bytes from the start of the device"
    pread(image_fd, &superBLK, sizeof(superBLK), offset);
    dprintf(STDOUT_FILENO, "SUPERBLOCK,%d,%d,%d,%d,%d,%d,%d\n", superBLK.s_blocks_count, superBLK.s_inodes_count, block_size, 
        superBLK.s_inode_size, superBLK.s_blocks_per_group, superBLK.s_inodes_per_group, superBLK.s_first_ino);
}

void GroupSummary()
{
    struct ext2_group_desc groupBLK;
    //we are only working on single group
    off_t offset = 1024 + block_size; //offset for superblock + superblock's size to get the offset for groups
    pread(image_fd, &groupBLK, 32, offset); //size of the block group descriptor structure is 32 bytes
    {
        fprintf(stderr, "Error, could not find super block\n");
        exit(1);
    }
    dprintf(STDOUT_FILENO, "GROUP,0,%d,%d,%d,%d,%d,%d,%d\n", superBLK.s_blocks_count, superBLK.s_inodes_per_group, groupBLK.bg_free_blocks_count,
        groupBLK.bg_free_inodes_count, groupBLK.bg_block_bitmap, groupBLK.bg_inode_bitmap, groupBLK.bg_inode_table);
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Error, incorrect number of commands\n");
        exit(1);
    }
    image_fd = open(argv[1], O_RDONLY);
    if(image_fd < 0)
    {
        fprintf(stderr, "Error, unable to open the image file\n");
        exit(1);
    }

    block_size = EXT2_MIN_BLOCK_SIZE << superBLK.s_log_block_size; //get the size of block

    SuperblockSummary();
    GroupSummary();

    return 0;
}
