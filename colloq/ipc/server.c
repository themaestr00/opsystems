#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int msgid_glob = 0;

struct
{
    long mtype;
    pid_t data;
} msgfrom;

struct
{
    long mtype;
    char data[100];
} msgto;

void
sighandler(int s)
{
    msgctl(msgid_glob, IPC_RMID, NULL);
    _exit(0);
}

int
main(void)
{
    key_t key = ftok("/home/maestro/source/opsystems/colloq/ipc/server", 's');
    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
    msgid_glob = msgid;
    sigaction(SIGINT, &(struct sigaction){.sa_handler = sighandler, .sa_flags = SA_RESTART}, NULL);
    while (1) {
        printf("Waiting for message...\n");
        msgrcv(msgid, &msgfrom, sizeof(msgfrom.data), 1, 0);
        printf("Message received, forming answer...\n");
        msgto.mtype = msgfrom.data;
        snprintf(msgto.data, sizeof(msgto.data), "Hello, process №%d!", msgfrom.data);
        msgsnd(msgid, &msgto, strlen(msgto.data) + 1, 0);
        printf("Answer sent!\n");
    }
}
