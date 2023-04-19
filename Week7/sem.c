#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t toiletsem; // POSIX 세마포 구조체로 모든 스레드에 의해 공유

#define NO 0          // 자식 프로세스와 세마포 공유하지 않음
#define MAX_COUNTER 3 // 자원의 개수, 동시에 들어갈 수 있는 스레드의 개수

void* guestThread(void* arg);

int main(void)
{
	int counter = -1;
	char* name[] = { "1", "2", "3", "4", "5" };
	pthread_t t[5]; // 스레드 구조체

	// 세마포 초기화 : MAX_COUNTER 명이 동시에 사용
	sem_init(&toiletsem, NO, MAX_COUNTER);
	sem_getvalue(&toiletsem, &counter); // 세마포의 현재 counter 값 읽기
	printf("세마포 counter = %d\n", counter);

	for (int i = 0; i < 5; i++) // 5명의 고객(스레드) 생성
		pthread_create(&t[i], NULL, guestThread, (void*)name[i]);

	for (int i = 0; i < 5; i++) // 모든 고객이 소멸할 때까지 대기
		pthread_join(t[i],NULL);

	sem_getvalue(&toiletsem, &counter); //  세마포의 현재 counter 값 읽기
	printf("세마포 counter = %d\n", counter);
	sem_destroy(&toiletsem); // 세마포 기능 소멸

	return 0;
}

void* guestThread(void* arg)	// 고객의 행동을 묘사하는 스레드 코드
{
	int cnt = -1;

	sem_wait(&toiletsem); // P 연산. 자원 사용 요청. 세마포의 counter 값 1 감소
	sem_getvalue(&toiletsem, &cnt); //  세마포의 counter 을 cnt 변수로 읽어오기

	printf("고객%s 화장실에 들어간다... 세마포 counter = %d\n", (char*)arg, cnt);
	sleep(1); // 1초 동안 화장실을 사용한다.

	sem_post(&toiletsem); // V 연산. 화장실 사용을 끝냈음을 알림

	sem_getvalue(&toiletsem, &cnt); //  세마포의 counter 값을 cnt 변수로 읽어오기
	printf("고객%s 화장실에서 나온다.세마포 counter = %d\n", (char*)arg, cnt);
}
