#include <stdio.h>
#include <stdlib.h>
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
    //дескриптор
    int shm_fd;
    void* ptr;
    clock_t begin = clock();
    //відкриваємо
    shm_fd = shm_open(name, O_RDONLY, 0666);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for opening is %f seconds\n", time_spent);
    
    begin = clock();
    //мапимо пам'ять
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for mmap is %f seconds\n", time_spent);
    
    begin = clock();
    //читання з пам'яті
    printf("%s", (char*)ptr);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime spent for reading is %f seconds\n", time_spent);
    //видалення об'єкта
    shm_unlink(name);
    return 0;
}
