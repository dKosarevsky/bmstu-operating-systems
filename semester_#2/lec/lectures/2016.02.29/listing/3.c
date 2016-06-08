struct super_block {
	// инфа для ФС
	union {} 
	семафоры;
	struct list_head _list;

	// опрееляет операции, специфичные для конкретной ФС
	struct super_operations s_op; 

	//каталоги точки монтирования
	struct dentry *s_root; 

	//всех подмонтированных подсистем
	struct list_head s_mount;

	//список индексов
	struct list_head s_inode; 

	//список измененных индексов
	struct list_head s_dirty; 

	// список всех открытых файлов в данном суперблоке
	struct list_head s_files; 
}
