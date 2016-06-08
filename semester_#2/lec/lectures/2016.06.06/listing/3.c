struct socket{
	socket_state state;
	short type;

	//для синхронизации доступа
	insigned long flags;

	//ссылает на дейсвтие подулюченного протокола
	const struct proto_ops *ops;

	//спиcок асинхронного запуска
	struct fasync_struct *fasync_list;

	struct file *file;
	struct sock *sk;
	wait_queue_head_t wait;
};