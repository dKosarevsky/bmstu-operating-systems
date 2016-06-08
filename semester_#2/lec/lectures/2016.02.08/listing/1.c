//описывает каждый открытый файл, сокет, ...
struct file {
	mode_tfmode;

	// текущая позиция в файле для операции чтения в файле
	loff_t f_pos;
	
	...
	struct inode *f_inode;

	// описывает операции, определенные на файле в системе
	struct file_operations *f_op;
}