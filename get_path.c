/* implementing a function to find the [PATH] */
#include "main.h"

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
        
        if (access(command_path, X_OK) == 0 && access(command_path, F_OK==0)){
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