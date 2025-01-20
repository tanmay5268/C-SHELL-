#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <sys/stat.h>   
char *get_path(char *command);
extern char **environ;
/*for builtins*/
void builtin_cd(char *args);
void builtin_exit(void); 

#endif
