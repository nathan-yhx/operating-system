#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
 
 int a[5];

 
union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};
 
 
#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)
     
 
//request a resource
#define DELAY (rand() % 5 + 1)
 

void grab_forks(int no,int semid)
{  
    
           
      
    //philosopher's index is same as the left fork index.
    int left = no;
    //right fork
    int right = (no + 1) % 5;
 
   a[no]++;
    struct sembuf buf[2] = {
        {left,-1,0},
        {right,-1,0}
    };

    semop(semid,buf,2);
}
 
void put_away_forks(int no,int semid)
{
    int left = no;
    int right = (no + 1) % 5;
    struct sembuf buf[2] = {
        {left,1,0},
        {right,1,0}
    };
    semop(semid,buf,2);
}
 
 
//the things philosopher will do.
void philosophere(int no,int semid)
{
    srand(getpid());
    //srand(time(NULL));
   
    for(int i=0 ; i < 5; i++) 
    {
     
        //satisfy two conditions
        //the non-adjcent philosopher can eat
        printf("%d is thinking\n",no);  // thinking 
        sleep(DELAY);
        printf("%d is hungry\n",no);  // feel hungry
        grab_forks(no,semid);//only take two forks can eat
      
        printf("Philosopher %d takes fork %d and %d\n",
                      no, no, (no + 1)%5 );
        printf("%d is eating, eating time[ %d ] \n",no,a[no]);  // eating
        sleep(DELAY);
        put_away_forks(no,semid);// free two forks
        printf("Philosopher %d putting fork %d and %d down\n",
           no, no, (no + 1)%5 );
   
    }
}
 
 /*void *table_lifecycle(void *i)      //philosopher action
{
    int meals_left = FOOD_LIMIT;
    //number of the philosopher
    int mm = *(int*) i;
    //check if meal has finish or not
    while(meals_left != 0)
    {
        printf("%s is thinking\n", philosopher_names[mm]);
        //sleep time for thinking
        sleep(THINKING_TIME);
        grab_forks(mm);
        printf("%s is eating the  [ %dth ] meal.\n", philosopher_names[mm], (FOOD_LIMIT-(--meals_left)));
        //sleep time for eating
        sleep(EATING_TIME);
        printf("%s have eaten [%d] meals \n", philosopher_names[mm], (FOOD_LIMIT-meals_left));
        put_away_forks(mm);
    }
}
 */
int main(int argc,char *argv[])
{
    int semid;
    //creat 5 signals in total. 
     
    semid = semget(IPC_PRIVATE,5,IPC_CREAT | 0666); 
    if(semid < 0) {
        ERR_EXIT("semid");
    }
    union semun su;
    su.val = 1;
    int i;
    for(i = 0;i < 5;++i) {
        
        semctl(semid,i,SETVAL,su);
    }
    //creat 4 son processes. 
    int num = 0;
    pid_t pid;
    for(i = 1;i < 5;++i) 
    {
       pid = fork(); 
       if(pid < 0) 
        {
           ERR_EXIT("fork");
        }
        if(0 == pid)  // son process
        {
            num = i;
            break;
        }
    }

   philosophere(num,semid);
    return 0;
}
