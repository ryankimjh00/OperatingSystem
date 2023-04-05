#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// 연습문제 4장

/*
T0: [    1] ~ 10000 -> s[0] => += sum
T1: [10001] ~ 20000 -> s[1] => += sum
T2: [20001] ~ 30000 -> s[2] => += sum
T3: [30001] ~ 40000 -> s[3] => += sum
s의 인덱스는 받은 값(시작값)의 몫을 사용하면됨 tip
*/
static __thread int tsum = 5;
int total = 0;
int total_sum =0;

void* runner(void* param){
    printf("runner 스레드가 실행을 시작합니다.\n");
    int to = atoi(param);
    int i, sum = 0;
    for(i = 1; i< to; i++){
        sum += i;
    }
    tsum = sum;
    total += tsum;
}

// void printsum(void){
//     printf("tsum = %d\n", tsum);
// }
int main(void){
    char *p[4] = {"1", "10001", "20001", "30001"};
    pthread_t tid[4];
    pthread_attr_t attr[4];
    for(int i =0; i< 4; i++){
        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i], &attr[i], runner, p[i]);
        printf("runner 스레드 생성 완료\n");
    }

    for(int i=0; i< 4; i++){
        pthread_join(tid[i], NULL);
        printf("runner 스레드 종료\n");        
    }
    printf("total = %d\n", total);
    return 0;
}
