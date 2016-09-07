
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






//  Builtin function implementations.
/**
   @brief Builtin command: pwd. Returns the present working directory.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_pwd(char ** args)
{
    if (args[0]== NULL)
      return 1;

    else
    {
      char * tem;
      char array[1000];
      if ((tem = getcwd(array, sizeof(array)))!=NULL)
        printf("%s\n",array );
      else
        fprintf(stderr, "Error: Unable to access directory.\n" );
    }
    return 1;
}


/**
   @brief Builtin command: echo
   @param args List of args.  Given by user
   @return Always returns 1, to continue executing.
 */
int lsh_echo(char ** args)
{
  //Empty argument prints new line
  if(args[1]==NULL)
    printf("\n" );

  else
  {
    int i;
    i=1;
    while (args[i]!=NULL){
      printf("%s\n", args[i]);
      i++;
    }
  }
  return 1;
}


/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    chdir(curpath);
  } else {

  if (strncmp(args[1],"~", 1)==0)
  {     //printf("yo found!\n" );
        strcpy(args[1],curpath);
        //printf("args[1] is %s\n",args[1] );
      }

     int dir = chdir(args[1]);
      if (dir!=0) {
      perror("lsh");
    }
  }
  return 1;
}



  //char * i;
/*  if (strncmp(args[1],"\"",1)==0 && args[2]!=NULL)
    {
      printf("%s ", args[1]+1 );
      /*char * i = args[2];
      int j =3;

      while(1){
        i = args[j];
        printf(" %s",i );

        if(i==NULL)
          break;

      }
   }*/


/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
  if (strcmp(args[0],"exit")==0)
    return 0;
}
