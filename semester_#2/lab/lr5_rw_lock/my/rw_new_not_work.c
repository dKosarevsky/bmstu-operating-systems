#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/random.h>

static const int R_COUNT =  5;
static const int W_COUNT =  3;

static const int R_ATTEMPT  = 10;
static const int W_ATTEMPT  = 10;

static int shmem = 0;

static rwlock_t lck;

static struct task_struct **r_threads, **w_threads;

struct thread_param
{
	int id;
	int attempt;
} *r_thread_params, *w_thread_params;


void reader_thread(void *data)
{
	int i;
	struct thread_param param = *((struct thread_param *)data);
	printk("Reader #%d started\n", param.id);
	for (i = 0; i < param.attempt; i++)
	{
		read_lock(&lck);
		printk ("Reader #%d: %d\n", i, shmem);
		read_unlock(&lck);
		msleep(get_random_int() % 20 * 10);
	}
	printk("Reader #%d finished\n", param.id);
}

void writer_thread(void *data)
{
	int i;
	struct thread_param param = *((struct thread_param *)data);
	printk("Writer #%d started\n", param.id);
	int old_shmem;
	for (i = 0; i < param.attempt; i++)
	{
		write_lock(&lck);
		old_shmem = shmem++;
		printk("Writer #%d: edit from %d to %d\n", param.id, old_shmem, shmem);
		write_unlock(&lck);
		msleep(get_random_int() % 20 * 10);
	}
	printk("Writer #%d finished\n", param.id);	
}

struct thread_param * my_create_params(int count, int attempt) {
	int i;
	struct thread_param * params = (struct thread_param *)kmalloc(sizeof (struct thread_param) * count, GFP_KERNEL);
	
	for (i = 0; i < count; ++i) {
		params[i].id = i;
		params[i].attempt = attempt;
	}

	return params;
}

struct task_struct ** my_create_threads(int count, int (*threadfn)(void *data), struct thread_param *params, char *name) {
	int i;

	struct task_struct **threads = (struct task_struct **)kmalloc(sizeof (struct task_struct *) * count, GFP_KERNEL);

	for (i = 0; i < count; ++i) {
		threads[i] = kthread_create(threadfn, (void *)(params+i), name, i);
	}

	return threads;
}

void my_run_threads(int count, struct task_struct **threads)
{
	int i;
	for (i = 0; i < count; ++i)	{
		wake_up_process(threads[i]);	
	}
}


int init_m(void)
{
	printk("Module init has started\n");

	rwlock_init(&lck);

	r_thread_params = my_create_params(R_COUNT, R_ATTEMPT);
	w_thread_params = my_create_params(W_COUNT, W_ATTEMPT);

	r_threads = my_create_threads(R_COUNT, reader_thread, r_thread_params, "reader_%d");
	w_threads = my_create_threads(W_COUNT, writer_thread, w_thread_params, "writer_%d");

	my_run_threads(R_COUNT, r_threads);
	my_run_threads(W_COUNT, w_threads);

	printk("Module inserted\n");
	return 0;
}

int exit_m(void)
{
	printk("Module exit has started\n");

	kfree(r_thread_params);
	kfree(w_thread_params);

	kfree(r_threads);
	kfree(w_threads);

	printk("Module removed\n");
	return 0;
}

module_init(init_m);
module_exit(exit_m);