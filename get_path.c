/* implementing a function to find the [PATH] */
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