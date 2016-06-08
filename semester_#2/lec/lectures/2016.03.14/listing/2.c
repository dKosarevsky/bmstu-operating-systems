struct file *dentry_open(struct dentry *dentry, struct vfsmount *mnt, int flags) {
 	struct file *f = // get an empty file structure
 	f->f_flags = flags;

 	// call open() used inode
 	struct inode = dentry->d_inode;
 	
 	f->f_op = fops_get(inode->i_fop);
 	f->f_op = open(inode, f);
 }