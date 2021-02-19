/*******************************************************************
 *
 *     File Name    :      msgquene.c
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Mon 26 Oct 2020 09:21:10 AM CST
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
#include <sys/msg.h>


struct msgbuf {
    long mtype;
    char mtext[15];
};


int main(int argc , const char * argv[])
{
    key_t  key= ftok(".",123);
    printf("%d\n",key);
    key= ftok(".",123);
    printf("%d\n",key);
    int msgid = -1;

    if( (msgid = msgget(key,IPC_CREAT|IPC_EXCL)) == -1 )
    {
        perror("msgget()");
        return -1;
    }

     struct msgbuf msgbuffer = {
        .mtype = 12345,
        .mtext  = "fafasdfkk", 
    };

    void * msgp = (void *) &msgbuffer;
    //in struct msgbuf  long mtype is used to 
    //indecate the one who is senaingd or will receive the msg


    if (msgsnd(msgid, msgp, sizeof msgbuffer.mtext ,0)  != 0)
    {
        printf("msgsnd error\n");
        perror("msgsnd()");
        return -1;
    }

    struct msgbuf msgrcvbuffer; 
    void * msgpr = (void *) &msgrcvbuffer;

    if (msgrcv(msgid, msgpr, sizeof msgrcvbuffer.mtext ,12345,IPC_NOWAIT )  == 0)
    {
        printf("msgrcv error\n");
        perror("msgrcv()");
        return -1;
    }

    system("ipcs -q");


    if (msgctl(msgid,IPC_RMID,NULL) != 0)
    {
        perror("msgctl()");
        return -1;
    }

    system("ipcs -q");

    return 0;
}
