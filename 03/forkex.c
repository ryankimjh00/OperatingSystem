#include <stdio.h>
#include <sys/types.h>  // pid_t 타입
#include <sys/wait.h>   // wait() 시스템 호출
#include <unistd.h>     // POSIX OS API

int main(void)
{
    pid_t pid;
    int i, sum = 0;
    int start, end = 0;

    pid = /* 자식프로세스 생성 */fork();

    if ( /* 부모 프로세스이면 */pid > 0 ) {
        printf("부모프로세스: fork()의 리턴 값 = 자식프로세스 pid = %d\n", pid);
        printf("부모프로세스: pid = %d\n", getpid());
        printf("부모 프로세스: 시작값 =%d, 끝값=%d 을 자식 프로세스에 전달\n", start, end);
        /* 자식 프로세스가 종료할 때까지 대기 */wait(NULL);
        printf("부모프로세스종료\n");
    }
    else if ( /* 자식 프로세스이면 */ pid == 0) {
        printf("자식프로세스: fork()의 리턴 값 pid = %d\n", pid);
        printf("자식프로세스: pid = %d, 부모프로세스 pid = %d\n", getpid(), getppid());

        for (i = start; i <= end; i++)
            sum += i;
        printf("자식프로세스: sum = %d\n", sum);
    }
    else { // fork() 오류
        printf("fork 오류");
        return -1;
    }

    return 0;
}
