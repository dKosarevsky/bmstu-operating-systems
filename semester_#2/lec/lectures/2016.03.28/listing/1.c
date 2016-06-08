#if LINUX_VERSION_CODE >= KERNEL_VERSION (3.10.0)
#include <../fs/prc/internal.h> /*PDE()*/
static inline void *PDE_DATA(const struct inode *inode) {
	return PROC_I (inode) -> pde-> data;
}
#endif

#include <...>

struct proc_dir_entry *proc;
int len, temp;
char *msg;
int read_proc(struct file *filp, char *buf, size_t count, loff_t *offp) {
	char *data;
	data = PDE_DATA(file_inode(filp));
	if (!data) {
		printk(KERN_INFO "Null data");
		return 0;
	}
	if (count > temp) {
		count = temp;
	}
	temp -= countl
	copy_to_user(buf, data, count);

	if (count == 0) {
		temp = len
	}
	return count;
}

struct file_operations proc_fops = { read : read_proc};
void create_new_proc_entry() {
	msg = "hello world";
	proc = proc_create_data("hello", 0, NULL, &proc _fops, msg);
	len = strlen(msg);
	temp = len;
}

int proc_init(void) {
	create_new_proc_entry();
	return 0;
}

void proc_cleanup(void) {
	remove_proc_entry("hello", NULL);
}

MODULE_LICENSE("GPL");

module_init(proc_init);
module_exit(proc_cleanup);