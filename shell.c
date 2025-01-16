#include "main.h"

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
            printf("%s\n",token);
            token = strtok(NULL, " ");
            }
    }
    
    
   
}