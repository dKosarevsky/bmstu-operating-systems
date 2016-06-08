#include <linux/irqreturn.h>
#define MOUSEIRQ 12

...

irqreturn_t irq_handler(int irq, void *dev_id, struct pt_regs *regs) {
	if (irq == MOUSEIRQ) {
		tasklet_shedule(&my_tasklet);
		return IRQ_HANDLER;
	} else {
		//устройство, от которого пришло прерывание распозноно
		return IEQ_NONE; //если не удалось
	}
} // устройство не является обработчиком

int init_module() {
	return request_irq(MOUSEIRQ, (irq_handler_t) irq_handler, IRQF_SHARED, "test_mouse_irq_handler", (void *)(irq_handler));
}

void cleanup_module() {
	free_irq(MOUSEIRQ, (void *) (irq_handler));
	tasklet_disable(&my_tasklet);
	tasklet_kill(&my_tasklet);
}