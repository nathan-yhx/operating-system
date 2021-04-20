

#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>

#define NUM_CHILD 10

int main()
{
    // Create the child process
    
    printf(" Create %d child process \n", NUM_CHILD);
    
    int status = 0;
    int counter = 0;
    
    for(int i = 0; i < NUM_CHILD; i++)
    {
        pid_t pid = fork();
        
        if(pid == 0)
        {
          
            printf(" pid : [%d]\n ", pid);
            printf(" This is a child process parent [%d] , the pid id [%d]\n ", getppid(), getpid());
            printf(" Child [%d] start \n", getpid());
            sleep(10);
            printf(" Child [%d] excution has completed \n", getpid());
            exit(0);
            
        }else
        {
            if(pid > 0)
            {
                
                printf(" pid : [%d]\n ", pid);
                printf(" This is a parent process, the pid id [%d]\n ", getppid());
                
            }else
            {
                printf(" fork() failed \n");
                kill(-1, SIGTERM);
                exit(1);
            }
        }
        sleep(1);
        printf(" One second delays \n\n");
    }
    
    printf(" %d childs process have been created \n", NUM_CHILD);
    
    while(1)
    {
        pid_t child_pid = wait(&status);
        if(child_pid == -1)
        {
            break;
        }else
        {
            counter++;
        }
    }
    
    printf("\n");
    printf(" No more child process\n");
    printf(" %d process terminated ccorrectly\n ", counter);
    
    return 0;
}
