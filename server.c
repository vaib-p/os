// server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    // Generate a key
    key_t key = ftok("server-client", 'R');

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    // Attach the shared memory segment
    char *shmaddr = (char *)shmat(shmid, NULL, 0);

    // Write a message to the shared memory
    strcpy(shmaddr, "Hello from the server!");
    printf("Server: Message written to shared memory\n");

    // Detach the shared memory segment
    shmdt(shmaddr);

    return 0;
}

