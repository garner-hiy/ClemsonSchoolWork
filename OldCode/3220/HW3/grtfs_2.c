// Member Names: AJ Garner, Mitchell Pohar
// Date: 17 April 2024
// Class: CPSC 3220
// Assignment: Homework 3

#include "grtfs.h"


/* grtfs_delete()
 *
 * deletes a closed directory entry having the given file descriptor
 *   (changes the status of the entry to unused) and releases all
 *   allocated file blocks
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is closed
 *
 * postconditions:
 *   (1) the status of the directory entry is set to unused
 *   (2) all file blocks have been set to free
 *
 * input parameter is a file descriptor
 *
 * return value is TRUE when successful or FALSE when failure
 */

unsigned int grtfs_delete( unsigned int file_descriptor ){
    
    // if unused, return false
    if (grtfs_get_status(file_descriptor) == UNUSED) return FALSE;
    
    // set status to unused
    grtfs_set_status(file_descriptor, UNUSED);
    unsigned int currentBlock = directory[file_descriptor].first_block;
    
    // clears all blocks of data
    while(currentBlock != LAST_BLOCK && currentBlock != 0) {
        unsigned int nextBlock = file_allocation_table[currentBlock];
        file_allocation_table[currentBlock] = FREE;
        currentBlock = nextBlock;
    }
    return TRUE;
}


/* grtfs_read()
 *
 * reads a specified number of bytes from a file starting
 *   at the byte offset in the directory into the specified
 *   buffer; the byte offset in the directory entry is
 *   incremented by the number of bytes transferred
 *
 * depending on the starting byte offset and the specified
 *   number of bytes to transfer, the transfer may cross two
 *   or more file blocks
 *
 * the function will read fewer bytes than specified if the
 *   end of the file is encountered before the specified number
 *   of bytes have been transferred
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *   (3) the file has allocated file blocks
 *
 * postconditions:
 *   (1) the buffer contains bytes transferred from file blocks
 *   (2) the specified number of bytes has been transferred
 *         except in the case that end of file was encountered
 *         before the transfer was complete
 *
 * input parameters are a file descriptor, the address of a
 *   buffer of bytes to transfer, and the count of bytes to
 *   transfer
 *
 * return value is the number of bytes transferred
 */

unsigned int grtfs_read( unsigned int file_descriptor, char *buffer, unsigned int byte_count ){
    
    // if read permission is false, then prints not able to read to user
    if (file_is_readable(directory[file_descriptor].name) == FALSE) {
        printf("NO READABLE PERMISSIONS for...%s.\n", directory[file_descriptor].name);
        return 0;
    }

    unsigned int bytesRead = 0;

    // current block and byte offset for current block
    unsigned char currentBlock = directory[file_descriptor].first_block;
    unsigned short byteOffset = directory[file_descriptor].byte_offset;

    int blockCounter = 0;
    while((file_allocation_table[currentBlock] != LAST_BLOCK) && (blockCounter + BLOCK_SIZE < byteOffset)){
        currentBlock = file_allocation_table[currentBlock];
        blockCounter += BLOCK_SIZE;
    }
    unsigned int startingPosition = byteOffset - blockCounter;
    
    // while bytes read is not finished and not the last block
    while (bytesRead < byte_count && currentBlock != LAST_BLOCK) {
        
        // remaining bytes to read 
        unsigned int bytesToRead = byte_count - bytesRead;

        if(bytesToRead > BLOCK_SIZE) bytesToRead = BLOCK_SIZE - startingPosition;

        // copy data from current block into buffer
        memcpy(buffer + bytesRead, &blocks[currentBlock].bytes[startingPosition], bytesToRead);
        startingPosition = 0;

        // updating the byte offset and bytes read
        byteOffset = byteOffset + bytesToRead;
        bytesRead += bytesToRead;

        directory[file_descriptor].byte_offset = byteOffset;

        currentBlock = file_allocation_table[currentBlock];
    }

    // return bytes read
    return bytesRead;

}

/* grtfs_write()
 *
 * writes a specified number of bytes from a specified buffer
 *   into a file starting at the byte offset in the directory;
 *   the byte offset in the directory entry is incremented by
 *   the number of bytes transferred
 *
 * depending on the starting byte offset and the specified
 *   number of bytes to transfer, the transfer may cross two
 *   or more file blocks
 *
 * furthermore, depending on the starting byte offset and the
 *   specified number of bytes to transfer, additional file
 *   blocks, if available, will be added to the file as needed;
 *   in this case, the size of the file will be adjusted
 *   based on the number of bytes transferred beyond the
 *   original size of the file
 *
 * the function will read fewer bytes than specified if file
 *   blocks are not available
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *
 * postconditions:
 *   (1) the file contains bytes transferred from the buffer
 *   (2) the specified number of bytes has been transferred
 *         except in the case that file blocks needed to
 *         complete the transfer were not available
 *   (3) the size of the file is increased as appropriate
 *         when transferred bytes extend beyond the previous
 *         end of the file
 *
 * input parameters are a file descriptor, the address of a
 *   buffer of bytes to transfer, and the count of bytes to
 *   transfer
 *
 * return value is the number of bytes transferred
 */

unsigned int grtfs_write( unsigned int file_descriptor, char *buffer, unsigned int byte_count ){
    
    // if first time writing to file, set read and write permissions to true
    if (directory[file_descriptor].size == 0) { 
        make_writable(directory[file_descriptor].name); 
        make_readable(directory[file_descriptor].name); 
    }
    
    // if not writable, then print no writing permissions to user
    if (file_is_writable(directory[file_descriptor].name) == FALSE) {
        printf("NO WRITABLE PERMISSIONS for...%s.\n", directory[file_descriptor].name);
        return 0;
    }

    unsigned int bytesWritten = 0;
    unsigned int currentBlock = directory[file_descriptor].first_block;
    
    // if first block, creat a new block
    if(currentBlock < FIRST_VALID_BLOCK) {
        unsigned char newFirstBlock = grtfs_new_block();
        directory[file_descriptor].first_block = newFirstBlock;
        currentBlock = directory[file_descriptor].first_block;
        file_allocation_table[newFirstBlock] = LAST_BLOCK;
    }
    
    // set local current block to the FAT current block
    while(file_allocation_table[currentBlock] != LAST_BLOCK) {
        currentBlock = file_allocation_table[currentBlock];
    }
    
    // set local current offset to the directory offset
    unsigned int currentOffset = directory[file_descriptor].byte_offset;

    // while bytes are not all written and while offset is not max file size
    while (bytesWritten < byte_count && currentOffset < MAX_FILE_SIZE) {

        // set remaining amount of bytes in the current block
        unsigned int remainingBytesInBlock = BLOCK_SIZE - (currentOffset % BLOCK_SIZE);

        // bytes left to write to current block
        unsigned int remainingBytes = byte_count - bytesWritten;
        unsigned int bytesToWrite = byte_count - bytesWritten;

        if(remainingBytes > remainingBytesInBlock) bytesToWrite = remainingBytesInBlock;
        
        // if remaining bytes have not been used up yet, then write to or create a new block
        if (remainingBytes != 0 && currentOffset >= BLOCK_SIZE && remainingBytesInBlock == BLOCK_SIZE) {

            // if a new block is already created, skip
            unsigned int nextBlock = file_allocation_table[currentBlock];
            if (nextBlock == LAST_BLOCK) {
                
                // if not, create a new block 
                nextBlock = grtfs_new_block();
                if (nextBlock == 0) {
                    directory[file_descriptor].size = currentOffset;
                    directory[file_descriptor].byte_offset = currentOffset;
                    return bytesWritten;
                }
                file_allocation_table[currentBlock] = nextBlock;
                file_allocation_table[nextBlock] = LAST_BLOCK;
            }
            currentBlock = nextBlock;
        }

        // copy the bytes into file block
        memcpy(&blocks[currentBlock].bytes[currentOffset % BLOCK_SIZE], &buffer[bytesWritten], bytesToWrite);
        bytesWritten += bytesToWrite;
        currentOffset += bytesToWrite;

        remainingBytes = byte_count - bytesWritten;
    }

    // file size and byte offset updated
    directory[file_descriptor].size = currentOffset;
    directory[file_descriptor].byte_offset = currentOffset;
    return bytesWritten;

}

/* Helper functions for status */

// helper function that returns the status bit
unsigned int grtfs_get_status(unsigned int fd) {
    unsigned int status = directory[fd].status & STATUS_MASK;
    return status;
}

// helper function to set the status bit
void grtfs_set_status(unsigned int fd, unsigned int stat) {
    unsigned char tempStatus = directory[fd].status;
    tempStatus = (tempStatus & RW_MASK) + stat;
    directory[fd].status = tempStatus;
}

/* implementation of assigned functions */


// function that returns true if the file is readable, otherwise returns false
unsigned int file_is_readable(char *name) {
    unsigned int fd = grtfs_map_name_to_fd(name);
    unsigned int readStatus = directory[fd].status & R_MASK;
    if (readStatus == R_MASK) return TRUE;
    return FALSE;
}

// function that returns true is the file is writable, otherwise returns false
unsigned int file_is_writable(char *name) {
    unsigned int fd = grtfs_map_name_to_fd(name);
    unsigned int writeStatus = directory[fd].status & W_MASK;
    if (writeStatus == W_MASK) return TRUE;
    return FALSE;
}

// function that swaps the readable bit to either readable or not readable, depending on the initial status
void make_readable(char *name) {
    unsigned int fd = grtfs_map_name_to_fd(name);
    directory[fd].status = directory[fd].status ^ R_MASK;
}

// function that swaps the writable bit to either writable or not writable, depending on the initial status
void make_writable(char *name) {
    unsigned int fd = grtfs_map_name_to_fd(name);
    directory[fd].status = directory[fd].status ^ W_MASK;
}