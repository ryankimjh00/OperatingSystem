#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid, returnid;
    int i, sum = 0;
    int start= 0;
    int end = 0;
    int status;
    scanf("%d, %d", &start, &end);
    pid = fork();/* 자식프로세스 생성 */
    switch(pid){
        case -1:
            printf("fork 오류");
            return -1;
        case 0:
            for (i = start; i <= end; i++){
                sum += i;
            }
            if(sum < 1000){
                printf("자식 프로세스: sum = %d\n", sum);
                exit(0);
            }
            else if(sum == 1000){
                printf("자식 프로세스: sum = %d\n", sum);
                exit(1);
            }
            else if(sum > 1000){
                printf("자식 프로세스: sum = %d\n", sum);
                exit(2);
            }            
        default:
            wait(&status); // 자식프로세스 종료 대기

            // printf("status: %d\n", WEXITSTATUS(status));
            if(status == 0){
                printf("부모 프로세스: 1000보다 작다\n");
            }else if(status == 1){
                printf("부모 프로세스: 1000과 같다\n");
            }else{
                printf("부모 프로세스: 1000보다 크다\n");
            }

    }
    return 0;
}
