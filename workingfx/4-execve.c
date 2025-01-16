#include <stdio.h>
#include <unistd.h>
int main (void ){
const char pathname[] ="/usr/bin/ls";
char *const argv[]= {"ls","-l",NULL};
/* char *const envp[] = NULL */
execve(pathname, argv, NULL);

}