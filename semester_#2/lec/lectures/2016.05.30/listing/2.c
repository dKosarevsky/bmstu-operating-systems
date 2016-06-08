// Для простых USB  драйверов, которые контролируют одно устройство, структура  USB_DEVICE_ID  может быть определена следующим образом:
static struct usb_device_id skel_table[] = {
	{USB_DEVICE(USB_SKEL_VENDOR, USB_SKEL_PRODUCT_ID)},
	{} //закрытые входы, так можно определять не все поля.
};

// skel_table - таблица устройств, которые работают с конкретным драйвером. Устанавливается макросом
MODULE_DEVICE_TABLE(usb, skel_table); 

//если это PCI драйвер, то этот макрос необходим, чтобы разрешить инструментам режима пользователя, выяснить, какое устройство может контролировать этот драйвер. Для USB устрйоств строка usb должна быть ???.