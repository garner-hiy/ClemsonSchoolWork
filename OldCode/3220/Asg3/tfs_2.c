// Member Names: AJ Garner, Mitchell Pohar
// Date: 15 April 2024
// Class: CPSC 3220
// Assignment: Homework 3


#include "tfs.h"

/* Helper functions for status */

/* tfs_get_status(unsigned int fd)
    return the status bit of the status field
*/
unsigned int get_status(unsigned int fd) {
    // mask the status field with the status mask
    unsigned int status = directory[fd].status & STATUS_MASK;

    return status;
}

/* tfs_set_status(unsigned int fd, unsigned int stat)
*   set the status bit of the status field
*/
void set_status(unsigned int fd, unsigned int stat) {
    unsigned char temp_status = directory[fd].status;
    //Zeroes out the status bits
    temp_status = (temp_status & RW_MASK) + stat;
    directory[fd].status = temp_status;
}

/* implementation of assigned functions */


/* file_is_readable()
*  (true if read, false otherwise)
*
*/
unsigned int file_is_readable(char *name) {
    unsigned int fd = tfs_map_name_to_fd(name);
    
    // mask the status field with the read mask
    unsigned int read_status = directory[fd].status & R_MASK;
    
    // if the masked status for read permission is set (1), return true, else return false
    if (read_status == R_MASK) { return TRUE; }
    return FALSE;
}

/* file_is_writable()
*  (true if writable, false otherwise)
*
*/
unsigned int file_is_writable(char *name) {
    unsigned int fd = tfs_map_name_to_fd(name);
    
    // mask the status field with the write mask
    unsigned int write_status = directory[fd].status & W_MASK;
    
    // if the masked status for the write permission is set (1), return true, else return false
    if (write_status == W_MASK) { return TRUE; }
    return FALSE;
}

/* make_readable()
*  Swap the read permission bit of the status field
*
*/
void make_readable(char *name) {
    unsigned int fd = tfs_map_name_to_fd(name);
    directory[fd].status = directory[fd].status ^ R_MASK;
}

/* make_writable()
*  Swap the read permission bit of the status field
*
*/
void make_writable(char *name) {
    unsigned int fd = tfs_map_name_to_fd(name);
    directory[fd].status = directory[fd].status ^ W_MASK;
}


/* tfs_delete()
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

unsigned int tfs_delete( unsigned int file_descriptor ){

    // case where delete would fail (already deleted)?
    if (get_status(file_descriptor) == UNUSED) return FALSE;

    // set status to unused
    set_status(file_descriptor, UNUSED);
    unsigned int current_block = directory[file_descriptor].first_block;

    //clears out all blocks
    while(current_block != LAST_BLOCK && current_block != 0) {
        unsigned int next_block = file_allocation_table[current_block];
        file_allocation_table[current_block] = FREE;
        current_block = next_block;
    }

    return TRUE;
}


/* tfs_read()
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

unsigned int tfs_read( unsigned int file_descriptor,
                       char *buffer,
                       unsigned int byte_count ){
    // Check read permission first
    if (file_is_readable(directory[file_descriptor].name) == FALSE) {
        printf("Not permitted to read from %s.\n", directory[file_descriptor].name);
        return 0;
    }

    // Variable to track the number of bytes read so far
    unsigned int bytes_read = 0;

    // Get the current block and byte offset within that block
    unsigned char current_block = directory[file_descriptor].first_block;
    unsigned short byte_offset = directory[file_descriptor].byte_offset;

    int blockctr = 0;
    while(file_allocation_table[current_block] != LAST_BLOCK && blockctr + BLOCK_SIZE < byte_offset){
        current_block = file_allocation_table[current_block];
        blockctr += BLOCK_SIZE;
    }
    unsigned int starting_pos = byte_offset - blockctr;
    
    // while we have not read all the bytes intended AND the current block is not the last
    while (bytes_read < byte_count && current_block != LAST_BLOCK) {
        
        // Calculate the remaining bytes to read within the current block
        unsigned int bytes_to_read = byte_count - bytes_read;

        if(bytes_to_read > BLOCK_SIZE)
            bytes_to_read = BLOCK_SIZE - starting_pos;

        // Read data from the current block into the buffer
        memcpy(buffer + bytes_read, &blocks[current_block].bytes[starting_pos], bytes_to_read);
        starting_pos = 0;

        // Update the byte offset, bytes read, and total bytes read
        byte_offset = byte_offset + bytes_to_read;
        bytes_read += bytes_to_read;

        directory[file_descriptor].byte_offset = byte_offset;

        current_block = file_allocation_table[current_block];
    }

    // Return the number of bytes read
    return bytes_read;

}

/* tfs_write()
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

unsigned int tfs_write( unsigned int file_descriptor,
                        char *buffer,
                        unsigned int byte_count ){
    // if first write, we need to set write permission to TRUE
    if (directory[file_descriptor].size == 0) { 
        make_writable(directory[file_descriptor].name); 
        make_readable(directory[file_descriptor].name); 
    }
    // Check write permission first
    if (file_is_writable(directory[file_descriptor].name) == FALSE) {
        printf("Not permitted to write to %s.\n", directory[file_descriptor].name);
        return 0;
    }

    unsigned int bytes_written = 0;

    unsigned int current_block = directory[file_descriptor].first_block;
    // if this is the first write that is being made, we need to create a new block
    if(current_block < FIRST_VALID_BLOCK) {
        unsigned char new_first = tfs_new_block();
        directory[file_descriptor].first_block = new_first;
        current_block = directory[file_descriptor].first_block;
        file_allocation_table[new_first] = LAST_BLOCK;
    }
    
    // set local current block to the current block of FAT
    while(file_allocation_table[current_block] != LAST_BLOCK)
        current_block = file_allocation_table[current_block];
        
    // set local current offset to the actual offset from directory entry
    unsigned int current_offset = directory[file_descriptor].byte_offset;

    // Loops until we reach the max size of a file OR all the bytes in the offset are written
    while (bytes_written < byte_count && current_offset < MAX_FILE_SIZE) {

        // find how many bytes we have left to write to block
        unsigned int remaining_in_block = BLOCK_SIZE - (current_offset % BLOCK_SIZE);

        // find how many bytes we have left that we can write to this block
        unsigned int remaining_bytes = byte_count - bytes_written;
        unsigned int bytes_to_write = byte_count - bytes_written;

        if(remaining_bytes > remaining_in_block)
            bytes_to_write = remaining_in_block;

        
        // If we have written all we can to this block, move to next 
        if (remaining_bytes != 0 && current_offset >= BLOCK_SIZE && remaining_in_block == BLOCK_SIZE) {

            // check if we already have a new block in the FAT to write to
            unsigned int next_block = file_allocation_table[current_block];
            if (next_block == LAST_BLOCK) {
                
                // If not, create a new block 
                next_block = tfs_new_block();
                if (next_block == 0) {
                    // No free blocks available, return the number of bytes written so far
                    directory[file_descriptor].size = current_offset;
                    directory[file_descriptor].byte_offset = current_offset;
                    return bytes_written;
                }
                file_allocation_table[current_block] = next_block;
                file_allocation_table[next_block] = LAST_BLOCK;
            }
            current_block = next_block;
        }

        // Write the bytes from the buffer into the file block
        memcpy(&blocks[current_block].bytes[current_offset % BLOCK_SIZE], &buffer[bytes_written], bytes_to_write);
        bytes_written += bytes_to_write;
        current_offset += bytes_to_write;

        remaining_bytes = byte_count - bytes_written;
    }

    // Update the file's size and byte offset in the directory entry
    directory[file_descriptor].size = current_offset;
    directory[file_descriptor].byte_offset = current_offset;
    return bytes_written;

}