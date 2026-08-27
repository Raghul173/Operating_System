#include "buffer.h"

int main() {
    // Generate unique key
    key_t key = ftok(FILE_PATH, PROJ_ID);
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create/Access Shared Memory
    int shmid = shmget(key, sizeof(struct buffer), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach Shared Memory
    struct buffer *buf = (struct buffer *)shmat(shmid, NULL, 0);
    if (buf == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Create Semaphore Set
    int semid = semget(key, 3, IPC_CREAT | 0666);
    if (semid < 0) {
        perror("semget failed");
        exit(1);
    }

    // Initialize Semaphores
    union semun arg;
    arg.val = SIZE;
    semctl(semid, SEM_EMPTY, SETVAL, arg); // Empty slots = 5
    arg.val = 0;
    semctl(semid, SEM_FULL, SETVAL, arg);  // Full slots = 0
    arg.val = 1;
    semctl(semid, SEM_MUTEX, SETVAL, arg); // Mutex = 1

    buf->in = 0;
    char ch;

    printf("Producer Initialized. Enter characters (q to stop):\n");

    while (1) {
        printf("Enter character: ");
        scanf(" %c", &ch);

        if (ch == 'q') break;

        // Semaphores operations
        struct sembuf wait_empty   = {SEM_EMPTY, -1, 0};
        struct sembuf wait_mutex   = {SEM_MUTEX, -1, 0};
        struct sembuf signal_mutex = {SEM_MUTEX, 1, 0};
        struct sembuf signal_full  = {SEM_FULL, 1, 0};

        semop(semid, &wait_empty, 1);   // wait(empty)
        semop(semid, &wait_mutex, 1);   // wait(mutex)

        // Critical Section
        buf->data[buf->in] = ch;
        printf("Produced: %c at index %d\n", ch, buf->in);
        buf->in = (buf->in + 1) % SIZE;

        semop(semid, &signal_mutex, 1); // signal(mutex)
        semop(semid, &signal_full, 1);  // signal(full)
    }

    shmdt(buf);
    return 0;
}
