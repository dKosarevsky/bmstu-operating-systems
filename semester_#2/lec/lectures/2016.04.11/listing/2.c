struct semaphore {
	atomic_t count;
	int sleepers;
	wait_queue_head wait;
}

//инициализирует счетчик семафора sem->count заданной величиной val.
void sem_init(struct semaphore *sem, int val);

//пытвается захватить семафор
inline void down(struct semaphore *sem);

inline void up(struct semaphore *sem);

int down_interruptible(&sem);

int down_trylock(&sem);