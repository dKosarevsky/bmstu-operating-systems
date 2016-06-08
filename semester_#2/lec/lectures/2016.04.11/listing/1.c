spinlock_t my_spin_lock = SPIN_LOCK_UNLOCKED;
unsigned long flags;
spin_lock_irqsave(&my_spin_lock, flags);
//критич секция
//...
spin_lock_irqre_store(&my_spin_lock, flags);
//flags передается по значению, потому что эти функции частично выполнены в виде макросов.