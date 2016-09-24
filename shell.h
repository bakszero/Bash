#ifndef HEADER
#define HEADER


#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_RL_BUFSIZE 1024

char curpath[1000]; //Home directory, globally declared
char *sentences[25]; //Storing strings delimited by ;


/*
  List of builtin commands, followed by their corresponding functions.
 */
/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_pwd(char **args);
int lsh_echo(char ** args);
int lsh_exit(char **args);

void lsh_read_line();
int piping (char **args);
char ** redirect(char** args);
int lsh_launch(char **args);
char **lsh_split_line(char *line);
int lsh_execute(char **args);
int lsh_num_builtins();
void sigh(int signum);


#endif
