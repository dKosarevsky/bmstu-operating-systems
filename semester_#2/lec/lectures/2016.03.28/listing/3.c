static struct proc_dir_entry *our_proc_file;

int init_module() {
	/*create the /proc file */
	our_proc_file = create_new_proc_entry(PROCFS_NAME, 0644, NULL);
	if (our_proc_file == NULL) {
		remove_proc_entry(PROCFS_NAME, &proc_root);
		printk(KERNAL_ALERT "Error: Coud't initialize /proc/%s\n", PROCFS_NAME);
		return -ENOMEM;
	}
	/* struct proc_dir_entry */
	our_proc_file -> read_proc = procfile_read;
	our_proc_file -> write_proc = procfile_write;
	our_proc_file -> owner = THIS_MODULE;
	our_proc_file -> mode = S_IFREG | S_IRUGO;
	our_proc_file -> uid = 0;
	our_proc_file -> gid = 0;
	our_proc_file -> size = 37;
	printk(KERN_INFO "/proc/%s created \n" PROCFS_NAME);
	return 0;
}