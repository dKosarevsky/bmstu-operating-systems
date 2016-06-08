struct dentry {
 	struct super_block *d_sb;
 	struct dentry *d_parent;
 	struct list_head d_subdirs;

 	//определяет операции с элементом каталога
 	struct dentry_operations *d_op; 

 	unsigned char d_iname[];

 	//связанный inode
 	struct inod *d_inode; 
 	...
 }

 struct vfsmount {
 	struct list_head mnt_hash;
 	struct vfsmount *mnt_parent;
 	struct dentry *mnt_mountpoint;
 	struct dentry *mnt_root;
 	struct super_block *mnt_sb;
 	struct list_head mnt_mount;
 	struct list_head mnt_child;
 	atomic_t mnt_count;
 	int mnt_flags;
 }