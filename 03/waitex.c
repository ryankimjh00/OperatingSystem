#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int status;

    pid = fork(); // 자식프로세스 생성

    if (pid > 0) { // 부모 프로세스 코드
        printf("부모프로세스: 자식의 종료를 기다림\n");

        /* 자식프로세스 종료 대기. status에 종료 코드 받음 */
	    wait(&status);   // status >> 8비트만큼 이동(응답 코드가 32비트중 끝에 있지 않을 경우땜에)

        printf("부모프로세스: child의 종료 코드=%d\n", WEXITSTATUS(status));
        return 0;
    }
    else if (pid == 0) { // 자식 프로세스 코드
        /* child를 자식프로세스로 실행 */
	execl("./child", "child", NULL);
	printf("failed");
    }
    else { // fork() 오류
        printf("fork 오류");
        return -1;
    }
}
