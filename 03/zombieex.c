#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid, zompid;
    int status;

    pid = fork();

    if (pid > 0) { // 부모 프로세스 코드
        sleep(10); // 10초 동안 잠자기
        zompid = wait(&status); // 자식프로세스 종료 대기
        printf("부모프로세스: 자식 PID=%d, 종료 코드=%d\n", zompid, WEXITSTATUS(status));
        return 0;
    }
    else if (pid == 0) { // 자식프로세스 코드
        printf("자식프로세스: %d 종료합니다.\n", getpid());
        exit(100); // 자식이 종료하여 좀비 프로세스가 됨. 종료 코드 100 전달
    }
    else { // fork() 오류
        printf("fork 오류");
        return -1;
    }
}
