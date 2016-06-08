//используется для работы с файлами и поддиректорями 
struct proc_dir_entry {

	// номер индекса inode файла.
	unsigned int low_ino; 

	//имя файла
	const char *name; 

	//длина имени
	unsigned short namelen; 

	//права доступа
	mode_t mode; 

	// кол-во ссылок на файл
	nlink_t nlink;

	uid_t uid;
	gid_t gid; 

	//размер
	unsigne long size; 

	struct inode_operations *proc_iops;
	struct file_operations *proc_fops;
	get_info_t *get_info;
	struct module *owner;

	//указатели, позволяющие создавать связанные списки
	struct proc_dir_entry *next, *parent, *subdir; 

	read_proc_t *read_proc;
	write_proc_t *write_proc;

	//кол-во ссылок
	atomic_t count; 
	
	int deleted; 
}