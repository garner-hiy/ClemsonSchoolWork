// Member Names: AJ Garner, Mitchell Pohar
// Date: 17 April 2024
// Class: CPSC 3220
// Assignment: Homework 3

// To Complile: gcc -g grtfs_1.c grtfs_2.c grtfs_driver3.c -o grtfs_driver3.out
//              (or use makefile)

// To Run: ./grtfs_driver3.out
//         (or use makefile)

// To create a compressed archived file:
// tar -cvzf asg3.tar.gz grtfs.h grtfs_1.c grtfs_2.c grtfs_driver3.c

// To extract a compressed archived file:
// tar -xvzf asg3.tar.gz

// To list contents of a tar.gz file:
// tar -ztvf asg3.tar.gz


#include "grtfs.h"

//This is a modified version of driver 2

int main(){
  unsigned int fd[128];
  char buffer1[1024], buffer2[1024], buffer3[1024];
  unsigned int length1, length2, count1, count2, count3;

  sprintf( buffer1, "%s", "This is to show that the GREAT File System is superior in every way compared to the trivial file system of the last project! Now Trivial File System, bow before the superior GREAT File System!!!!");

  sprintf( buffer2, "%s", "And now for something completely different." );

  length1 = strlen( buffer1 );
  length2 = strlen( buffer2 );
  printf( "length of buffer1 is %d\n", length1 );
  printf( "length of buffer2 is %d\n", length2 );

  grtfs_init();

  grtfs_list_directory();

  fd[0] = grtfs_create( "file.txt" );
  if( fd[0] == 0 ) printf( "first create failed\n" );

  fd[1] = grtfs_create( "my_file" );
  if( fd[1] == 0 ) printf( "second create failed\n" );

  grtfs_list_directory();
  

  // code to prove that the write function works as intended
  printf("Before making my_file unwritable.\n");
  count1 = grtfs_write( fd[0], buffer1, length1 );
  printf( "%d bytes written to file.txt\n", count1 );

  count2 = grtfs_write( fd[1], buffer2, length2 );
  printf( "%d bytes written to my_file\n", count2 );

  count1 = grtfs_write( fd[0], buffer1, length1 );
  printf( "%d bytes written to file.txt\n", count1 );

/////////////////////////////////////////////////
  //Now we will attempt to make fd[1] unwriteable before trying to write to it again
  make_writable( "my_file" );
  printf("After making my_file unwritable.\n");

  count2 = grtfs_write( fd[1], buffer2, length2 );
  printf( "%d bytes written to my_file\n", count2 );

/////////////////////////////////////////////////
  //Here we are showing that file_is_writeable works
  if(!file_is_writable("my_file")){
    printf("my_file had 0 bytes written to it because it is unwritable.\n" );
  }
  else{
    printf("my_file had %d written to it because it is writable.\n", count2);
  }
/////////////////////////////////////////////////

  count1 = grtfs_write( fd[0], buffer1, length1 );
  printf( "%d bytes written to file.txt\n", count1 );

  grtfs_close( fd[1] );

  grtfs_list_directory();
  grtfs_list_blocks();

  grtfs_seek( fd[0], 500 );

  // code to prove that the read function works as intended
  printf("Before making file.txt unreadable.\n");
  count3 = grtfs_read( fd[0], buffer3, 600 );
  printf( "%d bytes read from file.txt\n", count3 );
  buffer3[count3] = '\0';
  printf( "[%s]\n", buffer3 );

  grtfs_seek( fd[0], 250 );

/////////////////////////////////////////////////
  //this is the modified section
  //Now we will attempt to make fd[0] unreadable before trying to read it
  make_readable( "file.txt" );
  printf("After making file.txt unreadable.\n");
/////////////////////////////////////////////////

  count3 = grtfs_read( fd[0], buffer3, 20 );
  printf( "%d bytes read from file.txt\n", count3 );

/////////////////////////////////////////////////
  //Here we are showing that file_is_readable works
  if(!file_is_readable("file.txt")){
    printf("file.txt had 0 bytes read because it is unreadable.\n");
  }
  else{
    printf("file.txt had %d bytes read because it is readable.\n", count3);
  }
/////////////////////////////////////////////////

  buffer3[count3] = '\0';
  printf( "[%s]\n", buffer3 );

  fd[2] = grtfs_create( "file.txt" );
  printf( "fd for creating a file with identical name" );
  printf( " as existing file - %d\n", fd[2] );
  fd[2] = grtfs_create( "file3" );
  fd[3] = grtfs_create( "file4" );
  fd[4] = grtfs_create( "file5" );
  fd[5] = grtfs_create( "file6" );
  fd[6] = grtfs_create( "file7" );
  fd[7] = grtfs_create( "file8" );
  fd[8] = grtfs_create( "file9" );
  fd[9] = grtfs_create( "file10" );
  fd[10] = grtfs_create( "file11" );
  fd[11] = grtfs_create( "file12" );
  fd[12] = grtfs_create( "file13" );
  fd[13] = grtfs_create( "file14" );
  fd[14] = grtfs_create( "file15" );
  fd[15] = grtfs_create( "file16" );
  printf( "fd for creating a sixteenth file - %d\n", fd[15] );

/////////////////////////////////////////////////
  //this is the modified section
  //We are adding A LOT more files to the system to show it works fine
  for(int i = 16; i < 75; i++){
    char filename[20];
    sprintf(filename, "file%d", i + 1);
    fd[i] = grtfs_create( filename );
  }
/////////////////////////////////////////////////

  grtfs_list_directory();

  grtfs_close( fd[0] );
  grtfs_delete( fd[0] );
  printf("deleting file.txt.\n");

  grtfs_list_directory();

  grtfs_close( fd[3] );
  grtfs_close( fd[4] );
  grtfs_close( fd[5] );
  grtfs_close( fd[6] );
  grtfs_close( fd[7] );

  /////////////////////////////////////////////////
    //this is the modified section
    //We are closing a lot of those new files to show this works
  for(int i = 30; i < 45; i++){
    grtfs_close( fd[i] );
  }
  /////////////////////////////////////////////////

  grtfs_delete( fd[6] );
  grtfs_delete( fd[7] );
  printf("deleting file7 and file8.\n");

  /////////////////////////////////////////////////
    //this is the modified section
    //We are deleting a bunch of them now
  for(int i = 35; i < 43; i++){
    grtfs_delete( fd[i] );
  }
  printf("deleting file36 - file43.\n");
  /////////////////////////////////////////////////

  grtfs_list_directory();

  fd[16] = grtfs_create( "added_1" );
  fd[17] = grtfs_create( "added_2" );
  printf("creating files added_1 and added_2 to the first positions that are unused.\n");

  grtfs_list_directory();
  grtfs_list_blocks();

  return 0;
}