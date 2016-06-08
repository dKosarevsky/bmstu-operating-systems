int main (int args, char **argv) {
	int i, nthreads, count[MAXNTHREADS];
	pthread_t tid_produce[MAXNTHREADS], tid_consumer;
	if (argc != 3) qrr_quit(..)
	nitems = min(atoi(argv[1]), MAXNINTEMS);
	nthreads = min(atoi(argv[2]),  MAXNITEMS);
//создание производителей
	for(i = 0; i < nthreads; ++i) {
		count[i] = 0;
		pthreads_create(&tid_produce[i], NULL, produce, &count[i]);
	}
//потребител
	pthread_create(&tid_consumerm NULL, consume, NULL);

	return
}

-------------
//файл производители и потребитель
#include <pthread.h>
#define MAXNITEMS 1000
#define MAXNTHREADS 10
//глобальные переменные для всех потоков
int nitems;
int buff[MAXNITEMS];
struct { 
	pthread_mutex_t mutex;
	int nput;// след сохран эл-т
	int nval;// след значение
} put = {PTHREAD_MUTEX_INITIALIZER};

struct { 
	pthread_mutex_t mutex;
	pthread_cond_t cond;

	//кол-во элементов и используется совместно потребителями и производителями, поэтому доступ должен осуществляться в режиме взаимоисключения
	int nready;
} nready = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};

void *produce(void *arg) {
	for (;;;) {
		pthread_mutex_lock(&put.mutex);
		if (put.put >= nitems) {
			pthread_mutex_unlock(&put.mutex);
			return NULL;
		}
		buff[put.put] = put.nval;
		put.nput++;
		put.nval++;
		pthread_mutex_lock(nready_mutex);
		if (nready.nready == 0) {
			//сигнализирует потребителю, что он может начать работать
			pthread_cond_signal(&nready.cond);
		}
		nready.nreadt++;
		pthread_mutex_unlock(&nready.mutex);
		*((int *) arg) + 1;
	}
}

void *consumer(void *arg) {
	int i;
	for (i = 0; i < nitems; ++i) {
		pthread_mutex_lock(&nready.mutex);
		while (nreade.nready == 0) {
			pthread_cond_wait(&nready.cond, &nready.mutex);
		}
		nready.nready--;
		pthread_mutex_unlock(&nready.mutex);
		if (buff[i] != i) {
			printf("buf[%d]=%d\n", i, buff[i])
		}
	}
	return(NULL);
}
