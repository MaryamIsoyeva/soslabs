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
    const char* name = "OS";
    const char* message = "Hello from writer mmap";
    //дескриптор
    int shm_fd;
    void* ptr;
    
    //створення спільного об'єкта
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    //змінюємо розмір
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
/*#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define STORAGE_ID "/SHM_TEST"
#define STORAGE_SIZE 32
#define DATA "Hello, World! From PID %d"

int main(int argc, char *argv[])
{
	int res;
	int fd;
	int len;
	pid_t pid;
	void *addr;
	char data[STORAGE_SIZE];
    
	pid = getpid();
	sprintf(data, DATA, pid);
    
	// get shared memory file descriptor (NOT a file)
	fd = shm_open(STORAGE_ID, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
		return 10;
	}
    
	// extend shared memory object as by default it's initialized with size 0
	res = ftruncate(fd, STORAGE_SIZE);
	if (res == -1)
	{
		perror("ftruncate");
		return 20;
	}
    
	// map shared memory to process address space
	addr = mmap(NULL, STORAGE_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
	{
		perror("mmap");
		return 30;
	}
    
	// place data into memory
	len = strlen(data) + 1;
	memcpy(addr, data, len);
    
	// wait for someone to read it
	sleep(2);
    
	// mmap cleanup
	res = munmap(addr, STORAGE_SIZE);
	if (res == -1)
	{
		perror("munmap");
		return 40;
	}
    
	// shm_open cleanup
	fd = shm_unlink(STORAGE_ID);
	if (fd == -1)
	{
		perror("unlink");
		return 100;
	}
    
	return 0;
}*/