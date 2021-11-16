#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
 * ./hello_drv_test -w abc
 * ./hello_drv_test -r
 */
int main(int argc, char *argv[]) {
	int fd;
	int len;
	char buf[1024];

	if(argc < 2) {
		printf("usage: %s -w <string>\n", argv[0]);
		printf("       %s -r\n", argv[0]);
		return -1;
	}

	fd = open("/dev/hello", O_RDWR);
	if(fd == -1) {
		printf("open /dev/hello err\n");
		return -1;
	}

	if((argc == 3) && (strcmp(argv[1], "-w") == 0)) {
		len = strlen(argv[2]) + 1;
		len = len > 1024 ? 1024 : len;
		write(fd, argv[2], len);
	}
	else {
		len = read(fd, buf, 1024);
		buf[1023] = '\0';
		printf("APP read: %s\n", buf);
	}

	close(fd);

	return 0;
}

