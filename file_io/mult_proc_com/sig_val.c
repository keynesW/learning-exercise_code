/*******************************************************************
 *
 *     File Name    :      sigval.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º       :      http://www.    .com/ 
 *     Created Time :      Mon 26 Oct 2020 01:55:38 PM CST
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


#include <sys/ipc.h>
#include <sys/sem.h>


union semun {
    int		val;	        /* Value for SETVAL */
    struct semid_ds *buf;	/* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;	/* Array for GETALL, SETALL */
    struct seminfo  *__buf;	/* Buffer for IPC_INFO
                               (Linux-specific) */
};


int semphor_get(key_t key);
int init_sem(int semid,int init_val);
int sem_P(int sem_id);
int sem_V(int sem_id);
void sem_del(int sem_id);


int main(int argc , const char * argv[])
{

    key_t key = ftok(".",123);

    int sem_id = semphor_get( key );

    init_sem(sem_id,0);

    sem_V(sem_id);
    sem_P(sem_id);
    //sem_P(sem_id);
    //sem_V(sem_id);
    
    system("ipcs -s");
    sem_del(sem_id);

    system("ipcs -s");

    return 0;

}

int semphor_get(key_t key)
{
    int sem_id = semget(key,1,IPC_CREAT | IPC_EXCL | 0666);
    return sem_id;
}

int init_sem(int sem_id,int init_val)
{
    union semun semunion; 
    semunion.val = init_val ;//default to 1

    if (semctl(sem_id, 0,SETVAL,semunion) == -1)
    {
        perror("semctl()");
        return -1;
    }
}

int sem_P(int sem_id)
{
    struct sembuf sem_ops = {
                .sem_num = 0,
                .sem_op = -1,
                .sem_flg = SEM_UNDO, 
            };

   if (semop(sem_id,&sem_ops,1) == -1)
   {
        perror("semop()");
        return -1;
   }
}


int sem_V(int sem_id)
{
    struct sembuf sem_ops = {
                .sem_num = 0,
                .sem_op = 1,
                .sem_flg = SEM_UNDO, 
            };

   if (semop(sem_id,&sem_ops,1) == -1)
   {
        perror("semop()");
        return -1;
   }
}

void sem_del(int sem_id)
{
    if (semctl(sem_id,0,IPC_RMID) == -1)
    {
        perror("semctl(IPC_RMID)");
        return ;
    }
}
