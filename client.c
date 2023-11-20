// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    // Get the key used by the server
    key_t key = ftok("server-client", 'R');

    // Get the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666);

    // Attach the shared memory segment
    char *shmaddr = (char *)shmat(shmid, NULL, 0);

    // Read and display the message from shared memory
    printf("Client: Message received from server: %s\n", shmaddr);

    // Detach the shared memory segment
    shmdt(shmaddr);

    // Remove the shared memory segment (optional)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

