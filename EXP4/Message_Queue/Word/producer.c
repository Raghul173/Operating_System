#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
        perror("ftok failed");
        exit(1);
    }

    // Create the message queue
    int msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid < 0)
    {
        perror("msgget failed");
        exit(1);
    }

    struct message msg;
    msg.msg_type = 1;

    // Producer sends the message
    printf("Enter a message (Producer): ");
    fgets(msg.text, MSG_SIZE, stdin);

    if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1)
    {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Producer sent: %s", msg.text);

    return 0;
}
