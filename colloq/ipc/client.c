#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct
{
    long mtype;
    char data[100];
} msgfrom;

struct
{
    long mtype;
    pid_t data;
} msgto;

int
main(void)
{
    key_t key = ftok("/home/maestro/source/opsystems/colloq/ipc/server", 's');
    int msgid = msgget(key, 0);
    msgto.mtype = 1;
    msgto.data = getpid();
    msgsnd(msgid, &msgto, sizeof(msgto.data), 0);
    msgrcv(msgid, &msgfrom, sizeof(msgfrom.data), getpid(), 0);
    printf("Got message from server: '%s'\n", msgfrom.data);
    return 0;
}
