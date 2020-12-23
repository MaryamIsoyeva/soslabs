#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
int main()
{
    // ftok to generate unique key
    key_t key = ftok("fileshared",65);
    
    //ідентифікатор
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    
    clock_t begin = clock();
    // атач
    char *str = (char*) shmat(shmid,(void*)0,0);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for attaching and reading is %f seconds\n", time_spent);
    printf("Data read: %s\n",str);
    
    //детач
    shmdt(str);
    
    //знищення спільної пам'яті
    shmctl(shmid,IPC_RMID,NULL);
    
    return 0;
}