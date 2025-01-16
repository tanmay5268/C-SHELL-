#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(void)
{
    char *new_directory ="/usr/bin";//example of any directory
    if (chdir(new_directory)==0)
    {
        printf("Changed to /usr/bin");
    }
    else {
        perror("chdir");
        printf("failed to change the directory");
    }
    return 0;
}