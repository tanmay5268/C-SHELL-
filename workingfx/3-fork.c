#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    pid_t pid;
    pid_t my_pid;
    my_pid=getpid();
    printf("parent's id %u\n",my_pid);
    printf("before fork\n");
    printf("1\n");
    printf("2\n");
    printf("3\n");
    my_pid = getpid();
    printf("this is programs id:%u\n",my_pid);
    printf("after fork!\n");
    pid = fork();
    if(pid==-1){
        printf("fork error\n");
    }
      printf("4\n");
      printf("5\n");
      printf("6\n");
      if(pid==0){
        printf("this is parent's pid:%u\n",getppid());
        printf("this is child's pid:%u\n", my_pid);}
        else if(pid>0)
        {
            printf("this is parent's pid:%u\n",my_pid);
        }
        return 0;
}