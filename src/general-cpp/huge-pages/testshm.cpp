#include <sys/shm.h>
#include <numaif.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <string>


int free_shm(int shm_key, void* shm_buf);
void* allocate_shm(size_t buf_size, int numa_node, int shm_key);

int main(int argc, char *argv[]) {
	assert(argc == 2);
	size_t buf_size = std::stoull(std::string(argv[1]));
	std::cout << "Allocating " << buf_size << " Bytes (" << ((double)buf_size) / (1024*1024*1024) << " GB)" << std::endl;
	size_t numa_node = 1;
	//int shm_key = IPC_PRIVATE;
	int shm_key = 13;
	
	// allocate shared memory
	void* allocBuff = allocate_shm(buf_size, numa_node, shm_key);
	
	// set, and read the value of the buffer
	char* buffer = (char*)allocBuff;
	for (size_t i = 0; i < buf_size; i++) {
		buffer[i] = (char)i;
	}
	for (size_t i = 0; i < buf_size; i++) {
		assert(buffer[i] == (char)i);
	}
	
	// free shared memory
	free_shm(shm_key, allocBuff);
	return 0;
}


int free_shm(int shm_key, void* shm_buf) {
	int ret;
	int shmid = shmget(shm_key, 0, 0);
	if(shmid == -1) {
		switch(errno) {
			case EACCES:
				printf("SHM free error: Insufficient permissions. (SHM key = %d)\n", shm_key);
				break;
			case ENOENT:
				printf("SHM free error: No such SHM key. (SHM key = %d)\n", shm_key);
				break;
			default:
				printf("SHM free error: A wild SHM error: %s\n", strerror(errno));
				break;
		}
		return -1;
	}

	ret = shmctl(shmid, IPC_RMID, NULL);
	if(ret != 0) {
		printf("SHM free error: shmctl() failed for key %d\n", shm_key);
		exit(-1);
	}

	ret = shmdt(shm_buf);
	if(ret != 0) {
		printf("SHM free error: shmdt() failed for key %d\n", shm_key);
		exit(-1);
	}
	
	std::cout << "memory is freed successfully" << std::endl;
	return 0;
}

void* allocate_shm(size_t buf_size, int numa_node, int shm_key) {
	int shmid = shmget(shm_key, buf_size, IPC_CREAT | IPC_EXCL | 0666 | SHM_HUGETLB);
	if(shmid == -1) {
		switch(errno) {
			case EACCES:
				printf("SHM malloc error: Insufficient permissions. (SHM key = %d)\n", shm_key);
				break;
			case EEXIST:
				printf("SHM malloc error: Already exists. (SHM key = %d)\n", shm_key);
				break;
			case EINVAL:
			
				printf("SHM malloc error: SHMMAX/SHMMIN mismatch. (SHM key = %d, size = %lu)\n", shm_key, buf_size);
				break;
			case ENOMEM:
				printf("SHM malloc error: Insufficient memory. (SHM key = %d, size = %lu)\n", shm_key, buf_size);
				break;
			default:
				printf("SHM malloc error: Wild SHM error: %s.\n", strerror(errno));
				break;
		}
		std::exit(EXIT_FAILURE);
	}

	void *buf = shmat(shmid, NULL, 0);
	if(buf == NULL) {
		printf("SHM malloc error: shmat() failed for key %d\n", shm_key);
		exit(-1);
	}

	/* Bind the buffer to this socket */
	// const unsigned long nodemask = (1 << numa_node);
	// int ret = mbind(buf, buf_size, MPOL_BIND, &nodemask, 32, 0);
	// if(ret != 0) {
	// 	printf("HrdAlloc: SHM malloc error. mbind() failed for key %d\n", shm_key);
	// 	switch(errno) {
	//
	// 		case EFAULT:
	// 			printf("Part/all of the memory range specified by nodemask and maxnode points outside your accessible address space. (SHM key = %d)\n", shm_key);
	// 			break;
	// 		case EINVAL:
	// 			printf("An invalid value was specified for flags or mode. (SHM key = %d, size = %lu)\n", shm_key, buf_size);
	// 			std::cout << (char*)buf << std::endl;
	// 			break;
	// 		case EIO:
	// 			printf("MPOL_MF_STRICT was specified and an existing page was already"
	//               "on a node that does not follow the policy; or MPOL_MF_MOVE or"
	//               "MPOL_MF_MOVE_ALL was specified and the kernel was unable to"
	//               "move all existing pages in the range.. (SHM key = %d, size = %lu)\n", shm_key, buf_size);
	// 			break;
	// 		case ENOMEM:
	// 			printf("Insufficient kernel memory was available.. (SHM key = %d, size = %lu)\n", shm_key, buf_size);
	// 			break;
	// 		case EPERM:
	// 			printf("The flags argument included the MPOL_MF_MOVE_ALL flag and the caller does not have the CAP_SYS_NICE privilege");
	// 			break;
	// 		default:
	// 			printf("HrdAlloc: SHM malloc error: Wild SHM error: %s.\n", strerror(errno));
	// 			break;
	// 	}
	//
	// }
	//
	//
	memset(buf, 0, buf_size);	
	std::cout << "memory is allocated successfully" << std::endl;		
	return buf;
}


