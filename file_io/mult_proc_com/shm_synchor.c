/*******************************************************************
 *
 *     File Name    :      shared_mem.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Fri 23 Oct 2020 04:22:12 PM CST
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
#include <sys/shm.h>


typedef void (*signalhandler)(int);

void signalhandle_read(int para);
void signalhandle_write(int para);


char * shm_addr = NULL; 
char ptr_str[22] = {"test sentence"};
char ptr_c[21] = {"helloworld"}; 


int main(int argc , const char * argv[])
{
    //    extern void signalhandle_read(int para);
    //    extern void signalhandle_write(int para);

    //signalhandler psignalhandle_read = signalhandle_read;
    //signalhandler psignalhandle_write = signalhandle_write;
    //signal(SIGUSR1,psignalhandle_read);
    //signal(SIGUSR2,psignalhandle_write);

    signal(SIGUSR1,signalhandle_read);
    signal(SIGUSR2,signalhandle_write);


    //***************create shared_mem*******************// 

    key_t key = ftok(".",123);
    if( key == -1)
    {
        perror("ftok()");
        return -1;
    }

    int shmid = shmget(key,1024,IPC_CREAT|O_EXCL|0666);
    if(shmid == -1)
    {
        perror("shmid()");
        return -1;
    }
    printf("shmid = %d\n",shmid);

    shm_addr = shmat(shmid, NULL, 0);
    if(shm_addr == (void *) -1)
    {
        perror("shmat()");
        return -1;
    }

    system("ipcs -m");
    /*
       shmdt(shm_addr);
       if(shmctl(shmid,IPC_RMID,NULL) == -1)
       {
       perror("shmctl(IPC_RMID)");
       return -1;
       }

       system("ipcs -m");
    */

    //****************create child progress******************// 

    int ret = 0;
    if((ret = fork()) < 0)
    {
        perror("fork()");
        return -1;
    }

    /****************************************************
     *
     *    child write   waitting parent to read
     *
     *    parent write   waitting child to read
     *
     * **************************************************/
    
    if( ret == 0 )
    {
        //****************in child progress******************// 


        strncpy(shm_addr,ptr_c,strlen(ptr_c));
        printf("child write completed,waitting for parent pro to read \n");
        kill(getppid(),SIGUSR1);   //write complete call parent to read

        pause();                   //waitting parent pro to complete the reading 

        printf("child read completed, now is writing\n");
        raise(SIGUSR2);

        kill(getppid(),SIGUSR1);   //call parent to read


    }
    else
    {
        //****************in parent progress******************// 

        pause();                    // waitting to read

        printf("parent read completed, now is writing\n");
        strncpy(shm_addr,ptr_str,strlen(ptr_str));

        kill(ret,SIGUSR1);          //after parent pro writing, call child progress to read 
        printf("parent write completed, readSIG sent, waitting for child pro to read \n");

        //kill(ret,SIGUSR2);        //after reading  call child progress to write

        pause();                    // waitting for child pro to complete the reading/writting

        kill(ret,SIGKILL);  



        //*******************relase shared_mem***********************// 
        shmdt(shm_addr);
        if(shmctl(shmid,IPC_RMID,NULL) == -1)
        {
            perror("shmctl(IPC_RMID)");
            return -1;
        }

        system("ipcs -m");
        printf("parent pro ended,shared_mem released\n");
    }
    return 0;
}


void signalhandle_read(int para)
{
    putchar('\n');

    printf("in shm :%s\n",shm_addr);

    putchar('\n');

}

void signalhandle_write(int para)
{
    strncpy(shm_addr,ptr_c,strlen(ptr_c)+1);
    printf("child write completed,read SIG sent\n");

    putchar('\n');

}
