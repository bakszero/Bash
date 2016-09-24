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


//Declaring the builtin functions and pointer to function
char *builtin_str[]= { "cd", "pwd", "echo", "exit"};
int (*builtin_func[]) (char **) = { &lsh_cd, &lsh_pwd, &lsh_echo, &lsh_exit};

//Return the no. of builtin
int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}




/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
  pid_t pid;
  int status;
  char ampersand[2]="&";


  int i=0;
  char * last = NULL;

  if(args[1]==NULL)
    goto LABEL;
  char * ka = args[1];
  while (1)
  {
    last = args[i];
      i++;
    ka = args[i];
    if (ka==NULL)
      break;
  }

if (last!=NULL && i!=0 && strncmp(last,ampersand, 1) ==0)
  args[i-1]=NULL;

LABEL:


 pid = fork();

  if (pid!=0 && last!=NULL && strncmp(last,ampersand, 1) ==0){
    signal(SIGCHLD, sigh);

    // Parent process
    return 1;
  }
  else if (pid == 0) {
    // Child process
//char ** argv;
    args = redirect(args);
  //  int gg;
  //  for(gg=0;gg<3;gg++)
//printf("%s\n",argv[gg] );
  /*  int fd1, fd2, fd3;
    char in[100];
    char out[100];
    char outdir[100];

    int flag1=0;
    int flag2=0;
    int flag3=0;

    //Find whether there is a string for input and output

    char * q = args[0];
    int c=0;

    while(q!=NULL){

      if (strncmp(q,"<",1)==0){
        args[c]=NULL;
        flag1=1;
        strcpy(in,args[c+1]);
      }

      if((strncmp(q,">",1)==0)){
        args[c]=NULL;
        flag2=1;
        strcpy(out,args[c+1]);
      }

      if(strncmp(q,">>",2)==0){
        args[c]=NULL;
        flag3=1;
        strcpy(outdir,args[c+1]);
      }
      c++;
      q = args[c];
    }

    //If < was found in string inputted by user

    if(flag1==1){

      fd1 = open(in, O_RDONLY,0);

      //if error
      if(fd1 < 0){
        perror("Could not open the input file");
        exit(0);
      }

      dup2(fd1,0);
      close(fd1);
    }

    if(flag2==1){
      fd2 = open (out, O_WRONLY | O_CREAT, 0666);
      if(fd2<0){
        perror("Could not open the output file");
        exit(0);
      }

      dup2(fd2,1);
      close(fd2);
    }

    if(flag3==1){
      fd3 = open (outdir, O_WRONLY | O_CREAT | O_APPEND , 0666);
      if(fd3<0){
        perror("Could not open the output file");
        exit(0);
      }

      dup2(fd3,1);
      close(fd3);
    }*/



    int ret=execvp(args[0], args);
     if (ret== -1) {
      perror("SHELL:");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("SHELL:");
  }
    else {
      // Parent process
      do {
        waitpid(pid, &status, WUNTRACED);
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}




/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }
  int count = lsh_num_builtins();
  int len = strlen(args[0]);
  for (i = 0; i < count; i++) {
    if (strncmp(args[0], builtin_str[i], len) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}
