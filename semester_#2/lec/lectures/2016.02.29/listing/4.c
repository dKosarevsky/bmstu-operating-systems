struct super_operations {
	struct inode *(*alloc_inode (struct super_block *sb));
	void (*destroy_inode) (struct inode *);
	void (*read_inode)(struct inode *);
	void (*write_inode)(struct inode *, int);
	int (*sync_fs)(struct super_block *sb, int wait);
}
