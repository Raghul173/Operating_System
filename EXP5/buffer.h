#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

// Shared Constants
#define SIZE 5           // Buffer size
#define PROJ_ID 42       // Project ID for ftok
#define FILE_PATH "producer.c" // File path for ftok

// Shared Buffer Structure
struct buffer {
    char data[SIZE];
    int in;
};

// Semaphore Union (needed for semctl)
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// Readable names for Semaphore indexes
#define SEM_EMPTY 0
#define SEM_FULL  1
#define SEM_MUTEX 2

#endif
