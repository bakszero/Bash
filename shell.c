//Author : Bakhtiyar Syed
//Institution : IIIT Hyderabad

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include "shell.h"






/**
   @brief Main entry point.
   @param argc Argument count.
   @param argv Argument vector.
   @return status code
 */
int main(int argc, char **argv)
{


  //struct utsname unameData;

  //Returns passwd struct
  struct passwd * myname=NULL;
  myname = getpwuid(getuid());

  //Get the hostname
  char hostname[30];
  gethostname(hostname, 29);

  //passwd = getpwuid ( getuid());
  int status;
  char **args;
  char *line;

  //Getting the current working dir
  char * home;
  char * homenext;
  char prespath[1000];
  home = getcwd(curpath, sizeof(curpath));
  int len = strlen(curpath);
//printf("len is %d\n",len );
//printf("curpat is %s\n",curpath );
  do {

    //Print type
    printf("<");
    printf("%s", myname->pw_name);
    printf("@");
    printf("%s", hostname);
    printf(":");
    homenext= getcwd(prespath, sizeof(prespath));
    //printf("prespath is %s\n", prespath);
    if(strlen(prespath)<len)
        printf("%s",prespath );

    else if (strncmp(curpath,prespath,strlen(prespath))!=0)
      {
        if(strlen(prespath)>len)
        {
          printf("~");
          printf ("%s", prespath+ len);
        }
        else
        {
          printf("%s",prespath );
        }
      }
    else
      printf("~");
    printf(">");

    lsh_read_line(); //Calling th function to read the line

    int j=0;
    while(sentences[j]!=NULL)
    {
      args = lsh_split_line(sentences[j]); // Split line
      status = lsh_execute(args); //Execute the commands
      j++;
    }

    //free(line);
    free(args);
  } while (status);







  return EXIT_SUCCESS;
}
