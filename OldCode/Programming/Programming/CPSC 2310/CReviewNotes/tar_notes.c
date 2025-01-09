//Tar <flags><name of tar.gz><list or path to the files> 
//order matters - if not, this will cause a corrupt file
//c: Create an archive
//z: Compress the archive with gzip
//v: Display progress in the terminal, also know as verbose mode- optional but helpful
//f: allows you to specify the filname of the archive

// command ex: tar -czvf test.tar.gz tarTest1.txt tarTest2.txt tarTest3.txt

//opening is -xzvf
// x is for extract while c is for create
//to have them untar us -C and the filename to untar to

//command ex: tar -xzvf test.tar.gz -C untar

//commands: mkdir <name>- makes a folder in the location
//          rm <name>- will remove whatever is named / delete
//          ls - shows what is in the directory/folder


// cd to snapshot on SoC server to go to the archive of all backups