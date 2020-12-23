#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#define MAX 100

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;
    
    //генеруємо ключ
    key = ftok("progfile", 65);
    //створюємо чергу
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
//    printf("Enter Data : ");
//    fgets(message.mesg_text,MAX,stdin);
    strcpy(message.mesg_text, "Hello from write");
    clock_t begin = clock();
    //надсилаємо повідомлення
    msgsnd(msgid, &message, sizeof(message), 0);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent is %f seconds\n", time_spent);
    printf("Data send is : %s \n", message.mesg_text);
    return 0;
}