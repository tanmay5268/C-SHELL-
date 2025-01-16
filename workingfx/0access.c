#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    char *file_path = "new.doc";
    int permissions = R_OK; // check for read permissions

    if (access(file_path, permissions) == 0) {
        printf("The file %s exists and is readable.\n", file_path);
    }
     else {
        printf("The file %s does not exist.\n", file_path);
    }

    return 0;
}