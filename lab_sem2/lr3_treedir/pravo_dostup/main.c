#include <fcntl.h>

int main () {
	int fd = creat("file_WANT_READ", 0000);
	write(fd, "abc", 3);

	umask(0000);
	creat("file_u0000_d0777", 0777);
	creat("file_u0000_d0000", 0000);

	umask(0777);
	creat("file_u0777_d0777", 0777);
	creat("file_u0777_d0000", 0000);

	return 0;
}
