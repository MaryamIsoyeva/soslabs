#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
int main()
{
    const int SIZE = 4096;
    
    //спільний об'єкт в пам'яті
    const char* name = "mfile";
    const char* message = "Hello from writer mmap";
    //дескриптор
    int shm_fd;
    void* ptr;
    
    //створення спільного об'єкта
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    //задаємо розмір
    ftruncate(shm_fd, SIZE);
    
    //мапимо пам'ять
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
    clock_t begin = clock();
    //запис в об'єкт
    sprintf(ptr, "%s", message);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for writing is %f seconds\n", time_spent);
    ptr += strlen(message);
//    sprintf(ptr, "%s", message_1);
//    ptr += strlen(message_1);
    return 0;
}
