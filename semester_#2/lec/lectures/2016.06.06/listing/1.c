asmlinkage long sys_socketcall(int call, unsigned long *args) {
	int err;
	...
	if copy_from_user(a, args, nargs[call]) {
		return -EFAULT;
	}

	switch (call) {
		case SYS_SOCKET: err = sys_socket(a0, a1, a2); break;
		//...
	}

	return err;
}