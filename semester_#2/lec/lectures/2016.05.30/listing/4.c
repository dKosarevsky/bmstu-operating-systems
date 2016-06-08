static int_ init usb_skel_init(void) {
	int result;
	result = usb_register(&skel_driver);
	if (result) {
		err("usb register failed. error number %d", result);
	}
	return result;
}