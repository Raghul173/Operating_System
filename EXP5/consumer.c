#include "buffer.h"

int main() {
    // Generate unique key (must match producer)
    key_t key = ftok(FILE_PATH, PROJ_ID);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Access Shared Memory
    int shmid = shmget(key, sizeof(struct buffer), 0666);
    if (shmid < 0) {
        perror("shmget failed. Run producer first");
        exit(1);
    }

    // Attach Shared Memory
    struct buffer *buf = (struct buffer *)shmat(shmid, NULL, 0);
    if (buf == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Access Semaphore Set
    int semid = semget(key, 3, 0666);
    if (semid < 0) {
        perror("semget failed");
        exit(1);
    }

    int out = 0;
    char ch;

    printf("Consumer started and waiting for data...\n");

    while (1) {
        // Semaphores operations
        struct sembuf wait_full     = {SEM_FULL, -1, 0};
        struct sembuf wait_mutex    = {SEM_MUTEX, -1, 0};
        struct sembuf signal_mutex  = {SEM_MUTEX, 1, 0};
        struct sembuf signal_empty  = {SEM_EMPTY, 1, 0};

        semop(semid, &wait_full, 1);    // wait(full)
        semop(semid, &wait_mutex, 1);   // wait(mutex)

        // Critical Section
        ch = buf->data[out];
        printf("Consumed: %c (ASCII: %d) from index %d\n", ch, ch, out);
        out = (out + 1) % SIZE;

        semop(semid, &signal_mutex, 1); // signal(mutex)
        semop(semid, &signal_empty, 1); // signal(empty)

        sleep(1); // Slow down consumer to see results
    }

    shmdt(buf);
    return 0;
}
