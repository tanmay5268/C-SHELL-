#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
    /* declare variables */
    int characters_read;
    char *line = NULL ;
    size_t len = 0;

    /* prompt */
     write(1, "command- ",9);

    /* getting user input */
    characters_read= getline(&line, &len, stdin);/* stored in a variable cuz a fx always returns a value  */
    if (characters_read==-1){
        perror("error reading input");
        return (-1); 
    }
    else{
        /* process the input using tokenization */
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            /* this is where to fork */
            pid_t pid = fork();
            if (pid == -1){
                perror("fork failed");
                return (-1);
            }
            else if (pid == 0){
                /* child process */
                char *cmdPath = path_check(token);/* to find comand path */
                if (cmdPath == NULL){
                    write(2, "command not found\n", 18);
                    exit(1);/* exit with an error */
                }
                /* execution of program with execve */
                execve(cmdPath, &token, __environ);
                /* check if execve fails */
                if(execve(cmdPath, &token, __environ) == -1){
                perror("failed to execute the program");
                return EXIT_FAILURE;
                }
            }
        }
    }


}