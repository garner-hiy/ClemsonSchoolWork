// Member Names: AJ Garner, Mitchell Pohar
// Date: 17 April 2024
// Class: CPSC 3220
// Assignment: Homework 3

#include "grtfs.h"


/* implementation of helper functions */

unsigned int grtfs_check_fd_in_range( unsigned int fd ){
  if( ( fd < FIRST_VALID_FD ) || ( fd >= N_DIRECTORY_ENTRIES ) ){
    printf( "*** file_descriptor out of range: %d\n", fd );
    return( FALSE );
  }
  return( TRUE );
}

unsigned int grtfs_check_block_in_range( unsigned int b ){
  if( ( b < 2 ) || ( b >= N_BLOCKS ) ){
    printf( "*** block number out of range: %d\n", b );
    return( FALSE );
  }
  return( TRUE );
}

unsigned int grtfs_check_file_is_open( unsigned int fd ){
  if(grtfs_get_status(fd) != OPEN) {
    printf( "*** attempt to access invalid or closed file: %d\n", fd );
    return( FALSE );
  }
  return( TRUE );
}

unsigned int grtfs_check_valid_name( char *name ){
  int i, len = strlen( name );
  if( len > FILENAME_LENGTH ){
    printf( "*** file name too long\n" );
    return( FALSE );
  }
  for( i = 0; i < len; i++ ){
    if( !isalnum( name[i] ) && ( name[i] != '_' ) && ( name[i] != '.' ) ){
      printf( "*** file name has non-alphanumeric," );
      printf( " non-underscore character\n" );
      return( FALSE );
    }
  }
  return( TRUE );
}

unsigned int grtfs_new_directory_entry(){
  unsigned int fd;
  for( fd = FIRST_VALID_FD; fd < N_DIRECTORY_ENTRIES; fd++ ){
    if(grtfs_get_status(fd) == UNUSED) {
      return( fd );
    }
  }
  return( 0 );
}

unsigned int grtfs_map_name_to_fd( char *name ){
  unsigned int fd;
  if( !grtfs_check_valid_name( name ) ) return( 0 );
  for( fd = 1; fd < N_DIRECTORY_ENTRIES; fd++ ){
    if( strcmp( name, directory[fd].name ) == 0 ){
      return( fd );
    }
  }
  return( 0 );
}

unsigned int grtfs_new_block(){
  unsigned int b;
  for( b = FIRST_VALID_BLOCK; b < N_BLOCKS; b++ ){
    if( file_allocation_table[b] == FREE ) return( b );
  }
  return( 0 );
}


/* implementation of public functions */

/* grtfs_init()
 *
 * initializes the directory as empty and the file allocation table
 *   to have all blocks free
 *
 * no parameters
 *
 * no return value
 */
void grtfs_init(){
  unsigned int i;
  directory = (struct directory_entry *) storage;
  blocks = (struct file_block *) storage;
  file_allocation_table = (unsigned char *) &storage[N_BLOCKS];
  for( i = 0; i < N_BYTES; i++ ){
    storage[i] = 0;
  }
}

/* grtfs_list_blocks()
 *
 * list file blocks that are being used and next block values
 *   from the file allocation table
 *
 * no parameters
 *
 * no return value
 */
void grtfs_list_blocks(){
  unsigned int b;
  printf( "-- file alllocation table listing of used blocks --\n" );
  for( b = FIRST_VALID_BLOCK; b < N_BLOCKS; b++ ){
    if( file_allocation_table[b] != FREE ){
      printf( "  block %3d is used and points to %3d\n",
        b, file_allocation_table[b] );
    }
  }
  printf( "-- end --\n" );
}

/* grtfs_list_directory()
 *
 * list all directory entries
 *
 * no parameters
 *
 * no return value
 */
void grtfs_list_directory(){
  unsigned int fd;
  unsigned char b;
  printf( "-- directory listing --\n" );
  for( fd = FIRST_VALID_FD; fd < N_DIRECTORY_ENTRIES; fd++ ){
    printf( "  fd = %2d: ", fd );
    if(grtfs_get_status(fd) == UNUSED) {
      printf( "unused\n" );
    }else if (grtfs_get_status(fd) == CLOSED) {
      printf( "%s, currently closed, %d bytes in size\n",
        directory[fd].name, directory[fd].size );
    }else if(grtfs_get_status(fd) == OPEN) {
      printf( "%s, currently open, %d bytes in size\n",
        directory[fd].name, directory[fd].size );
    }else{
      printf( "*** status error\n" );
    }
    if (  ((grtfs_get_status(fd) == CLOSED) ||
          (grtfs_get_status(fd) == OPEN))) {
      printf( "           FAT:" );
      if( directory[fd].first_block == 0 ){
        printf( " no blocks in use\n" );
      }else{
        b = directory[fd].first_block;
        while( b != LAST_BLOCK ){
          printf( " %d", b );
          b = file_allocation_table[b];
        }
        printf( "\n" );
      }
    }
  }
  printf( "-- end --\n" );
}

/* grtfs_exists()
 *
 * return TRUE if a file name is associated with an active
 *   directory entry
 *
 * preconditions:
 *   (1) the name is valid
 *   (2) the name is associated with an active directory entry
 *
 * postconditions:
 *   there are no changes to the file data structures
 *
 * input parameter is file name
 *
 * return value is TRUE or FALSE
 */
unsigned int grtfs_exists( char *name ){
  if( !grtfs_check_valid_name( name ) ) return( FALSE );
  if( grtfs_map_name_to_fd( name ) == 0 ) return( FALSE );
  return( TRUE );
}

/* grtfs_create()
 *
 * create a new directory entry with the given file name and
 *   set the status to open, the first_block to invalid, the
 *   size to 0 and the byte offset to 0
 *
 * preconditions:
 *   (1) the name is valid
 *   (2) the name is not already associated with any active
 *         directory entry
 *   (3) an unused directory entry is available
 *
 * postconditions:
 *   (1) a new directory entry overwrites an unused entry
 *   (2) the new entry is appropriately initialized
 *
 * input parameter is file name
 *
 * return value is the file descriptor of a directory entry
 *   when successful or 0 when failure
 */
unsigned int grtfs_create( char *name ){
  unsigned int file_descriptor;
  if( !grtfs_check_valid_name( name ) ) return( 0 );
  if( grtfs_map_name_to_fd( name ) != 0 ) return( 0 );
  file_descriptor = grtfs_new_directory_entry();
  if( file_descriptor == 0 ) return( 0 );
  grtfs_set_status(file_descriptor, OPEN);
  directory[file_descriptor].first_block = 0;
  directory[file_descriptor].size = 0;
  directory[file_descriptor].byte_offset = 0;
  strcpy( directory[file_descriptor].name, name );
  return( file_descriptor );
}

/* grtfs_open()
 *
 * opens the directory entry having the given file name and
 *   sets the status to open and the byte offset to 0
 *
 * preconditions:
 *   (1) the name is valid
 *   (2) the name is associated with an active directory entry
 *   (3) the directory entry is not already open
 *
 * postconditions:
 *   (1) the status of the directory entry is set to open
 *   (2) the byte offset of the directory entry is set to 0
 *
 * input parameter is file name
 *
 * return value is the file descriptor of a directory entry
 *   when successful or 0 when failure
 */
unsigned int grtfs_open( char *name ){
  unsigned int file_descriptor;
  if( !grtfs_check_valid_name( name ) ) return( 0 );
  file_descriptor = grtfs_map_name_to_fd( name );
  if( file_descriptor == 0 ) return( 0 );
  if( grtfs_check_file_is_open( file_descriptor ) ) return( 0 );
  grtfs_set_status(file_descriptor, OPEN);
  directory[file_descriptor].byte_offset = 0;
  return( file_descriptor );
}

/* grtfs_close()
 *
 * closes the directory entry having the given file descriptor
 *   (sets the status to closed and the byte offset to 0); the
 *   function fails if (1) the file descriptor is out of range,
 *   (2) the file descriptor is within range but the directory
 *   entry is not open
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *
 * postconditions:
 *   (1) the status of the directory entry is set to closed
 *   (2) the byte offset of the directory entry is set to 0
 *
 * input parameter is a file descriptor
 *
 * return value is TRUE when successful or FALSE when failure
 */
unsigned int grtfs_close( unsigned int file_descriptor ){
  if( !grtfs_check_fd_in_range( file_descriptor ) ) return( FALSE );
  if( !grtfs_check_file_is_open( file_descriptor ) ) return( FALSE );
  grtfs_set_status(file_descriptor, CLOSED);
  directory[file_descriptor].byte_offset = 0;
  return( TRUE );
}

/* grtfs_size()
 *
 * returns the file size for an active directory entry
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is active
 *
 * postconditions:
 *   there are no changes to the file data structures
 *
 * input parameter is a file descriptor
 *
 * return value is the file size when successful or MAX_FILE_SIZE+1
 *   when failure
 */
unsigned int grtfs_size( unsigned int file_descriptor ){
  if( !grtfs_check_fd_in_range( file_descriptor ) ) return( MAX_FILE_SIZE + 1 );
  if ( grtfs_get_status(file_descriptor) == UNUSED) return( MAX_FILE_SIZE + 1 );
  return( directory[file_descriptor].size );
}

/* grtfs_seek()
 *
 * sets the byte offset in a directory entry
 *
 * preconditions:
 *   (1) the file descriptor is in range
 *   (2) the directory entry is open
 *   (3) the specified offset is less than the file size
 *
 * postconditions:
 *   the byte offset of the directory entry is set to the
 *     specified offset
 *
 * input parameters are a file descriptor and a byte offset
 *
 * return value is TRUE when successful or FALSE when failure
 */
unsigned int grtfs_seek( unsigned int file_descriptor, unsigned int offset ){
  if( !grtfs_check_fd_in_range( file_descriptor ) ) return( FALSE );
  if( !grtfs_check_file_is_open( file_descriptor ) ) return( FALSE );
  if( offset >= directory[file_descriptor].size ) return( FALSE );
  directory[file_descriptor].byte_offset = offset;
  return( TRUE );
}
