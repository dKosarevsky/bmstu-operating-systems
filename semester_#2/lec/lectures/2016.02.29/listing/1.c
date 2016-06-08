struct inode {
	struct list_head i_hash;
	struct list_head i_list; //содержит все inode
	struct list_head i_dentry;
	...
	unsigned long i_ino;
	uid_t i_uid;
	time_t i_atime;
	time_t i_mtime;
	time_t i_ctime;
	struct inode_operations *i_op; //возможные операции на inode
	struct inode_operations {
		int (*create ) (..)
		struct dentry *(*lookup)();
		int (*mkdir)();
		int (*rename)();
	}
	struct file_operations *i_fop;
	struct file_operations {
		struct module *owner;
		ssize_t (*read)(..);
		ssize_t (*write)(..);
		int (*open)(struct inode *, struct file *);
	}
	struct super_bloct *i_sb;
	wait_queue_head_t i_wait;
	...
	union {
		struct minix_inode_info struct_i;
		struct ext2_inode_info ext2_t;
		struct socket socket_i;
		...
	} u;
};
