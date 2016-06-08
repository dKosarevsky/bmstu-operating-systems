static int usb_mouse_probe(struct usb_interface *intf, const struct usb_device_id *id) {
	struct usb_device *dev = interface_to_usbdev(inf);
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_mouse *mouse;
	struct input_dev *input_dev;	
	/...

	// вызывется при подключении устройства
	input_dev -> open = usb_mouse_open; 

	input_dev -> close = usb_mouse_close;

	//регистрирует обработчик быстрого прерывания
	usb_file_int_urb(mouse->irq, dev, pipe, mouse -> data, maxp > 8 ? 8 : maxp), usb_mouse_irq, mouse, endpoint -> bInterval);

	//...
} 
