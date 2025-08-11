#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <sys/stat.h>
char *get_path(char *command) /* this command takes the tokenize string from {char *token} */
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);/* not to modify the original PATH */ 
    char command_path[1024];
    char *dir = strtok(path_copy, ":");
    printf("This is the command %s\n",command);
    /* create a loop to iterate */
    while (dir != NULL)
    {
        
        strcpy(command_path, dir);
        if (command_path[strlen(command_path)-1]!= '/')
        {
            strcat(command_path, "/");
        }
        strcat(command_path, command);
        
        if (access(command_path, X_OK) == 0 && access(command_path, F_OK)==0){
            free(path_copy);
            printf("This command pathin the function%s\n", command_path);
            return (strdup(command_path));
        }
        
        dir = strtok(NULL, ":");/* proceed to the next directory */
    }
    printf("File is not found in any directory\n");
    free(path_copy);
    return (NULL);
    
}
void builtin_cd(char *args)
{
    if (args == NULL)
    {
        char *home = getenv("HOME");
        if (home == NULL)
        {
            perror("cd : HOME environment variable is not set\n");
        }
    else
        {
            if (chdir(home) != 0)
            {
                perror("could not change directory");
            }
        }
    }
else 
{
    if (chdir(args) != 0)
    {
        perror("could not change directory");
    }
}
}

void builtin_exit(void)
{
    printf("exiting shell . . . .\n");
    sleep(1);
    exit (0);
}
int main(void){
    /* declare variables */
    extern char **environ;
    int characters_read;
    char *delimiter = " \n";
    char *line = NULL ;
    size_t len = 0;
    char *line_argument[1024];
    int pid;
    char **arg;

    while(1){/* prompt */
     write(1, "command- ",9);

    /* getting user input */
    characters_read= getline(&line, &len, stdin);/* stored in a variable cuz a fx always returns a value  */
    if (characters_read==-1){
        perror("error reading input");
        return (-1); 
    }
    else if (characters_read == 1)
    {
       continue ;
    }
    else
    {
        int idx=0;
        /* process the input using tokenization */
        char *token = strtok(line, delimiter);
        while (token != NULL)
        {     line_argument[idx] = token;
              token=strtok(NULL,delimiter);
              idx++;
        }
              line_argument[idx]  = NULL;
        if (strcmp(line_argument[0], "cd") == 0)
			{
				/* Call for our function*/
				builtin_cd(line_argument[1]);
			}
		else if(strcmp(line_argument[0], "exit")== 0)
			{
				/* We want to exit*/
				builtin_exit();
            }      
              
        else{
                
                int pid = fork();

        if (pid == -1)
            {
                perror("fork failed");
                free(line);
                return (-1);
            }
        else if (pid == 0)
            {    
                /* child process */
                char *cmdPath = get_path(line_argument[0]);
            if (cmdPath != NULL){
                    execve(cmdPath, line_argument, environ);
                    
                    free(line);
                    exit(1);
                
                }
                }
        else 
            {
                /* we are in parent process */
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)&& WEXITSTATUS(status) != 0)
                {
                    printf("child process %d exited with status %d\n", pid, WEXITSTATUS(status));
                }
            }
            
        }
        
    
    }

    }
        free(line);
        return (0);

    }