#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>


#define BUFF_SIZE 4096 // typical OS page/block size

int main(int argc , char* argv[])
{
  char buffer[BUFF_SIZE];
  struct stat statbuf;

  if(argc == 1) {printf("%s: missing file operand \n", argv[0]); return EXIT_FAILURE;}
  if(argc == 2) {printf("%s: missing destination file operand after '%s' \n", argv[0], argv[1]); return EXIT_FAILURE;}


  // cp source destination
  if(argc == 3) 
  {
    //fd = file_descriptor
    //this check if the file exist or not
    int source_fd= open(argv[1], O_RDONLY);
    if(source_fd == -1) 
    { printf("%s: cannot stat '%s': %s \n", argv[0], argv[1], strerror(errno)); return EXIT_FAILURE;}
  
    stat(argv[1],&statbuf);
    // this check if a file exist and create it if not
    int target_fd = creat(argv[argc-1],statbuf.st_mode);
    if(target_fd == -1) 
    { printf("%s: cannot create '%s': %s \n", argv[0], argv[argc-1], strerror(errno)); return EXIT_FAILURE;}
   

   // keep reading from file and copying until there's nothing to copy 
    ssize_t bytes_read;
    while((bytes_read = read(source_fd,buffer,BUFF_SIZE)) > 0)
    {
      ssize_t bytes_written = 0;
      while(bytes_read > bytes_written)
      {
        int result = write(target_fd, buffer+bytes_written, bytes_read-bytes_written);
        if(result == -1)
        {
          close(source_fd);
          close(target_fd);
          return EXIT_FAILURE;
        }
        bytes_written += result;
      }
    }
    return EXIT_SUCCESS;
  }

  // cp source1 source2 .. destination
  if(argc > 3)
  {
    //check if the destination is a directory 
    int dir_fd = open(argv[argc-1],O_DIRECTORY,statbuf.st_mode);
    if(dir_fd == -1) 
    {
      printf("%s: target '%s': %s \n", argv[0], argv[argc-1], strerror(errno));
      close(dir_fd);
      return EXIT_FAILURE;
    }

    for(int i = 1; i < argc-1; i++)
    {
    //fd = file_descriptor
    //this check if the file exist or not
    int source_fd= open(argv[i], O_RDONLY);
    if(source_fd == -1) 
    { printf("%s: cannot stat '%s': %s \n", argv[0], argv[i], strerror(errno)); return EXIT_FAILURE;}
  
    
    stat(argv[i],&statbuf);
    // this check if a file exist and create it if not
    int target_fd = openat(dir_fd,argv[i],O_CREAT|O_WRONLY|O_TRUNC,statbuf.st_mode);
    if(target_fd == -1) 
    { printf("%s: cannot create '%s': %s \n", argv[0], argv[argc-1], strerror(errno)); return EXIT_FAILURE;}
   

   // keep reading from file and copying until there's nothing to copy 
    ssize_t bytes_read;
    while((bytes_read = read(source_fd,buffer,BUFF_SIZE)) > 0)
    {
      ssize_t bytes_written = 0;
      while(bytes_read > bytes_written)
      {
        int result = write(target_fd, buffer+bytes_written, bytes_read-bytes_written);
        if(result == -1)
        {
          close(source_fd);
          close(target_fd);
          return EXIT_FAILURE;
        }
        bytes_written += result;
      }

    }
  }
  }
  //open the source file to check if it exists or not
  return 0;
}
