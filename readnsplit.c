
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
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
void lsh_read_line(void)
{
  char *line = NULL;
  const char s[2] = ";";
 ssize_t bufsize = 1024; // have getline allocate a buffer for us
 getline(&line, &bufsize, stdin);


 sentences[0] = strtok(line,s);
 int k=0;
 int l =1;
 while (sentences[k]!=NULL)
 {
   k++;
   sentences[l] =strtok(NULL,s);
   l++;

 }


}








/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE;
  int position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char **tokens_backup;
  char *token;

  if (!tokens) {
    fprintf(stderr, "SHELL: allocation error\n");
    exit(3);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}
