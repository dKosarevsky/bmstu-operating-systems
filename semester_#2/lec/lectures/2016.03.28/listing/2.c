#include <linux/proc_fs.h>
#define PROCFS_NAME "bufferlk"
static char procfs_buffer[1024];

//много аргументов - чтобы на этапе компиляции осуществлялась проверка соответсвие типов и порядка передаваемых значений, а в конечном итоге это предпосылка для надежного кода. 
int procfile_read (char *buffer, char **buffer_location, off_t offset, int buffer_length, int eof, void *data) {
	int ref;
	printk(KERN_INFO "procfile_read (/proc/%s) called \n", PROCFS_NAME);
	if (offset>0) {
		/* we have finished to read, return 0 */
		ref = 0;
	} else {
		/* fill the buffer, return the buffer sizee */
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ref = procfs_buffer_size;
	}
	return ref;
}

int procfile_write (struct file *file, const char buffer, unsigned longcount, void *data) {
	procfs_buffer_size = count;
	if (procfs_buffer_size > 1024) {
		procfs_buffer_size = 1024;
	}
	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size)) {
		return -EFAULT;
	}
	return procfs_buffer_size;
}