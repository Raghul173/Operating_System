#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>

#define MSG_SIZE 1024

struct message
{
    long msg_type;
    char text[MSG_SIZE];
};

int main()
{
    const char *filename = "producer.c";
    key_t key = ftok(filename, 42);

    if (key == -1)
    {
        perror("ftok failed. Ensure producer.c exists");
        exit(1);
    }

    // Access the message queue
    int msgid = msgget(key, 0666);

    if (msgid < 0)
    {
        perror("msgget failed. Run producer first");
        exit(1);
    }

    struct message msg;

    // Consumer receives the message
    if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1)
    {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Consumer received: %s", msg.text);

    // Count number of words
    int count = 0;
    int in_word = 0;
    int i = 0;
    for (i = 0; msg.text[i] != '\0'; i++)
    {
        if (!isspace(msg.text[i]) && in_word == 0)
        {
            count++;
            in_word = 1;
        }
        else if (isspace(msg.text[i]))
        {
            in_word = 0;
        }
    }

    printf("Number of words: %d\n", count);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
