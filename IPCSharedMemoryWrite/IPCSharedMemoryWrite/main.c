#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
int main()
{
    key_t key = ftok("fileshared",65);
    //ідентифікатор
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    clock_t begin = clock();
    //атач до спільної пам'яті
    char *str = (char*) shmat(shmid,(void*)0,0);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for attaching is %f seconds\n", time_spent);
    
    begin = clock();
    strcpy(str, "Hello from writer in shared memory");
//    gets(str);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for writing is %f seconds\n", time_spent);
    printf("Data written: %s\n",str);
    
    //детач
    begin = clock();
    shmdt(str);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for detaching is %f seconds\n", time_spent);
    return 0;
}