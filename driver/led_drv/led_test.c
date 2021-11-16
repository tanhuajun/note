#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/*
 * ./ledtest /dev/led0 on
 * ./ledtest /dev/led0 off
 */

int main(int argc, char *argv[]) {
	int fd;
	int status;
	
	if(argc < 3) {
		printf("usage: %s <dev> on|off\n", argv[0]);
		return -1;
	}
	fd = open(argv[1], O_RDWR);
	if(fd == -1) {
		printf("can not open %s\n", argv[1]);
		return -1;
	}

	if(strcmp(argv[2], "on") == 0) {
		status = 1;
		write(fd, &status, 1);
	}
	else {
		status = 0;
		write(fd, &status, 1);
	}
	return 0;
}

