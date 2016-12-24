#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm-generic/uaccess.h>

static char msg[128];
static int len = 0;
static int len_check = 1;

/* Элементы procfs */
struct proc_dir_entry *kmodule, *kmodule_dir, *kmodule_sym;
static const char *ent = "simple_ent";
static const char *dir = "simpleproc";
static const char *sym_des = "simple_sym";
static const char *sym_tar = "/proc/simpleproc/simple_ent";

int simple_proc_open(struct inode * sp_inode, struct file *sp_file)
{
	printk(KERN_INFO "proc called open\n");
	return 0;
}

int simple_proc_release(struct inode *sp_indoe, struct file *sp_file)
{
	printk(KERN_INFO "proc called release\n");
	return 0;
}

int simple_proc_read(struct file *sp_file,char __user *buf, size_t size, loff_t *offset)
{
	if (len_check)
	 len_check = 0;
	else {
	 len_check = 1;
	 return 0;
	}
	printk(KERN_INFO "proc called read %d\n",size);
	copy_to_user(buf,msg,len);
	return len;
}

int simple_proc_write(struct file *sp_file,const char __user *buf, size_t size, loff_t *offset)
{
	printk(KERN_INFO "proc called write %d\n",size);
	len = size;
	copy_from_user(msg,buf,len);
	return len;
}

struct file_operations fops = {
	.open = simple_proc_open,
	.read = simple_proc_read,
	.write = simple_proc_write,
	.release = simple_proc_release
};

static int __init init_simpleproc (void)
{
	printk(KERN_INFO "init simple proc\n");
	
	kmodule_dir = proc_mkdir(dir, NULL);

	kmodule = proc_create(ent, 0644, kmodule_dir, &fops);
	kmodule_sym = proc_symlink(sym_des, kmodule_dir, sym_tar);

	return 0;
}

static void __exit exit_simpleproc(void)
{
	remove_proc_entry(kmodule_sym, kmodule_dir);
	remove_proc_entry(kmodule, kmodule_dir);
	remove_proc_entry(kmodule_dir, NULL);

	printk(KERN_INFO "exit simple proc\n");
}

module_init(init_simpleproc);
module_exit(exit_simpleproc);

MODULE_AUTHOR("Ilya P");
MODULE_LICENSE("GPL v3");
MODULE_DESCRIPTION("A simple module to input/output using proc filesystem");