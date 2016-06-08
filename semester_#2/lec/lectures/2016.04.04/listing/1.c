#include <linux/spinlock.h>
spinlock_t my_spinlock = SPIN_LOCK_UNLOCKED;

//process #1
spin_lock(&my_spinlock);
a->next = q->next;
q->next = a;
spin_unlock(&my_spinlock)

//process #2 
spin_lock(&my_spinlock);
b->next = q->next;
q->next = b;
spin_unlock(&my_spinlock);