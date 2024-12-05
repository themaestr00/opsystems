#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/msg.h>

struct
{
    long mtype;
    char data[256];
} message;

int
main(void)
{
    key_t key = ftok("/home/maestro/source/const", 'h');
    int msgid = msgget(key, 0666);
    while (1) {
        msgrcv(msgid, &message, 256, 1, 0);
        printf("Process A received message: '%s'\n", message.data);
        if (message.data[0] == 'q' || message.data[0] == 'Q') {
            exit(0);
        }
    }
}
