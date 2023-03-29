#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
        pid_t pid, ppid;

        pid = /* 현재 프로세스의 id */getpid();
        ppid = /* 현재 프로세스의 부모 프로세스 id */getpid();

        printf("process ID = %d, parent PID = %d\n", pid, ppid);

        return 0;
}
