typedef struct_DEVICE_EXTENSION {
	KSPIN_LOCK slinlock 
} DEVICE_EXTENTION, *PDEVICE_EXTENTION;
....

//инициализируем спин лок
NTSTATUS DriverEntry(...){
	KeInitializeSpinLock(&extension->spinlock);
}

//
NTSTATUS DispatchReadWrite(...) {
	KIRQL OldIrql;
	KeAcquireSpinLock(&extension -> spinlock, &OldIrql);

	//обработка данных

	KeReleaseSpinLock(&extension -> spinlock, OldIrql);
	...
}