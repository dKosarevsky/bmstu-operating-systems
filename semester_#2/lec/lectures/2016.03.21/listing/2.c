register_proc_files() {
	//создаем дирректрию test_dir
	test_dir = proc_mkdir("test_dir", &proc_root);

	//аналогичной ф-ей является ф-я creat_proc_read_entry("test", 0444, test_dir). Эти функции используются если требуется создать в proc файлы, для отображения какой либо информации. Позволяет зарегистрировать функцию для чтения информации из proc
	if (!create_proc_into_entry("test", 0444, test_dir, test_proc_get_info)) {

		//выполняет ф-и в ядре
		printk(KERN_DEBUG, "TEST: Error creating /proc/test"); 
	}

	entry = creat_proc_etrry("test_rw", 0644, test_dir);
	entry->nlink = 1;
	entry->data = (*void)&variable;
	entry->read_proc = test_proc_read;
	entry->write_proc = test_proc_write;
}

int test_proc_get_info(char *buf, char **stast, off_t offset, int len) {
	len = sprint(buf, "\n This is ntest module\n\n");

	 //используется для получения информации в user mode на ряду с copy_to_user()
	len += sprintf(buf + len, "integer:%n\n", variable1);
	
	return len;
}
