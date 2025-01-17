#include "main.h"
#include "main.h"

char *path_check(char *command) /* this command takes the tokenize string from {char *token} */
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);/* not to modify the original PATH */
    char *dir = strtok(path_copy, ":");
    /* create a loop to iterate */
    while (dir != NULL)
    {
        char *full_path = malloc(strlen(dir) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0){
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        dir = strtok(NULL, ":");/* proceed to the next directory */
    }
    free(path_copy);
    return (NULL);
    
}

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
    else
    {
        /* process the input using tokenization */
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            /* this is where to fork */
            pid_t pid = fork();
            if (pid == -1)
            {
                perror("fork failed");
                return (-1);
            }
            else if (pid == 0)
            {
                /* child process */
                char *cmdPath = path_check(token);/* to find comand path */
                if (cmdPath == NULL){
                    perror("command not found:");
                    exit(1);/* exit with an error */
                }
                /* execution of program with execve */
                execve(cmdPath, &token, __environ);
                /* check if execve fails */
                if(execve(cmdPath, &token, __environ) == -1)
                {
                  perror("failed to execute the program");
                  exit(EXIT_FAILURE);
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
            token = strtok(NULL, " ");
        }
        return 0;}


}