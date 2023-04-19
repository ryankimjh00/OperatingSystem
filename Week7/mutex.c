#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int sum = 0;	// 두 스레드가 공유하는 변수
pthread_mutex_t lock;	// 뮤텍스락
// compile 할때 gcc -o mutex mutex.c -lpthread
void* worker(void *);

int main(void)
{
	char* name[] = { "황기태", "이찬수"};
	pthread_t tid[2];
	pthread_attr_t attr[2]; // 스레드 정보를 담을 구조체

	pthread_attr_init(&attr[0]); // 디폴트 속성으로 초기화
	pthread_attr_init(&attr[1]); // 디폴트 속성으로 초기화

	pthread_mutex_init(&lock, NULL); // 뮤텍스락 변수 lock 초기화

	pthread_create(&tid[0], &attr[0], worker, name[0]);  // 스레드 생성
	pthread_create(&tid[1], &attr[1], worker, name[1]); // 스레드 생성

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("total sum = %d\n", sum);

	pthread_mutex_destroy(&lock); // 뮤텍스락 lock 사용 끝

	return 0;
}

void* worker(void* arg)	// 스레드 코드
{
	printf("%s 시작 %d\n", (char *)arg, sum);

	for (int i = 0; i < 10000000; i++) {
		pthread_mutex_lock(&lock);/* entry 코드. 뮤텍스 락 잠그기 */
		sum += 10;	// 임계구역 코드
		pthread_mutex_unlock(&lock);/* exit 코드. 뮤텍스 락 열기 */
	}
	printf("%s 끝 %d \n", (char *)arg, sum);
}
