int sysopen(const char *name, int flags, int mode)   {
	int fd = get_unused_fd();
	struct file *f = filp_open(name, flags, mode);
	fd_install(sd, f);
	return fd
}

 struct file *filp_open(const char *name, int flags, int mode) {
 	struct nameidata nd;
 	open_namei(filename, namei_flags, mode, &nd);
 	return dentry_open(nd.dentry, nd.mnt, flags);
 }