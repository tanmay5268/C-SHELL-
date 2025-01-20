#include "main.h"
void builtin_cd(char *args)
{
    if (args == NULL)
    {
        char *home = getenv("HOME")
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
    sleep(2);
    exit(0);
}