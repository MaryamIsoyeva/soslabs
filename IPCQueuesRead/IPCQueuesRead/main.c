#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    clock_t begin = clock();
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent is %f seconds\n", time_spent);
    printf("Received: %s \n",
           message.mesg_text);
    
    //знищуємо чергу
    msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}