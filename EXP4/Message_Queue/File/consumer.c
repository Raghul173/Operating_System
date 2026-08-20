#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 1024

struct message
{
    long msg_type;
    char text[MSG_SIZE];
    int last;
};

int main()
{
    const char *filename = ".";
    char destination[100];

    printf("Enter destination file name: ");
    scanf("%s", destination);

    // Check destination file
    FILE *fp = fopen(destination, "w");

    if (fp == NULL)
    {
        perror("Destination file cannot be created");
        exit(1);
    }

    fclose(fp);

    // Generate key
    key_t key = ftok(filename, 42);

    if (key == -1)
    {
        perror("ftok failed");
        exit(1);
    }

    // Access the message queue
    int msgid = msgget(key, 0666);

    if (msgid < 0)
    {
        perror("msgget failed. Ensure producer is running first");
        exit(1);
    }

    // Open destination file for writing
    fp = fopen(destination, "w");

    if (fp == NULL)
    {
        perror("Destination file open failed");
        exit(1);
    }

    struct message msg;

    // Consumer receives the file data
    while (1)
    {
        if (msgrcv(msgid, &msg,
                   sizeof(msg.text) + sizeof(msg.last),
                   1, 0) == -1)
        {
            perror("msgrcv failed");
            fclose(fp);
            exit(1);
        }

        if (msg.last == 1)
        {
            break;
        }

        fputs(msg.text, fp);
    }

    printf("Consumer received file data successfully.\n");
    printf("Data saved to: %s\n", destination);

    fclose(fp);

    // Remove message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl failed");
        exit(1);
    }

    return 0;
}
