struct vfssw vfssw[]={
	{0,0,0,0}
	{"spec", specinit, &spec_vfsops, 0}
	{"ufs", ufsinit, &ufs_vfsops, 0}
}

struct vfs {
	struct vfs *vfsnext;
	struct vfs *vfs_op;

	//vnode mounted on
	struct vnode *vfs_vnode_covered 
	
	struct vfs *vfs_hash;
}
