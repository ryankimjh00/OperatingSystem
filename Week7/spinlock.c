#include <stdio.h>
#include <pthread.h>

int sum = 0; // 두 스레드가 공유하는 변수
pthread_spinlock_t lock; // 스핀락 변수

void* worker(void*);

int main(void)
{
	char* name[] = { "황기태", "이찬수" };
	pthread_t tid[2]; // 두 스레드의 ID를 저장할 배열
	pthread_attr_t attr[2]; // 스레드 정보를 담을 구조체

	pthread_attr_init(&attr[0]); // 디폴트 속성으로 초기화
	pthread_attr_init(&attr[1]); // 디폴트 속성으로 초기화

	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE); // lock을 한 프로세스에 속한 스레드만이 공유하는 변수로 선언

	pthread_create(&tid[0], &attr[0], worker, name[0]);  // 스레드 생성
	pthread_create(&tid[1], &attr[1], worker, name[1]); // 스레드 생성

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("total sum = %d\n", sum); // 최종 합 출력

	pthread_spin_destroy(&lock);

	return 0;
}

void* worker(void* arg) // 스레드 코드
{
	printf("%s 시작 %d\n", (char *)arg, sum);
	for (int i = 0; i < 10000000; i++) {
		pthread_spin_lock(&lock);/* entry 코드 */
		sum += 10; // 임계구역 코드
		pthread_spin_unlock(&lock);/* exit 코드 */
	// mutex는 대기큐에 넣고 빼야하기 때문에 작업 규모에 따라 다르긴 하지만 이 경우 spinlock이 더 빠르다
	}
	printf("%s 끝 %d\n", (char *)arg, sum);
}
