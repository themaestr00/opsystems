#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

struct
{
    long mtype;
    char data[256];
} message;

int
main(void)
{
    key_t key = ftok("/home/maestro/source/const", 'h');
    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    if (msgid == -1) {
        printf("%s\n", strerror(errno));
    }
    while (1) {
        fgets(message.data, sizeof(message.data), stdin);
        if (message.data[strlen(message.data) - 1] == '\n') {
            message.data[strlen(message.data) - 1] = 0;
        }
        switch (message.data[0]) {
        case 'a':
        case 'A':
            message.mtype = 1;
            msgsnd(msgid, &message, strlen(message.data) + 1, 0);
            break;
        case 'b':
        case 'B':
            message.mtype = 2;
            msgsnd(msgid, &message, strlen(message.data) + 1, 0);
            break;
        case 'q':
        case 'Q':
            message.mtype = 1;
            msgsnd(msgid, &message, strlen(message.data) + 1, 0);
            message.mtype = 2;
            msgsnd(msgid, &message, strlen(message.data) + 1, 0);
            sleep(10);
            msgctl(msgid, IPC_RMID, NULL);
            exit(0);
        }
    }
}
