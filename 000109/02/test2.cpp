#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../../include/mydaemon.h"

int main()
{
    my_daemon();
    /*char *buf = "1953072 –§≈Ù∑…\n";
	int fd;
    while(1){

		if ((fd = open("mydaemon.txt", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0)
		{
			printf("Open file error\n");
			exit(1);
		}
        
		write(fd, buf, strlen(buf) + 1);
        sleep(5);
	close(fd);

    }*/

    while(1){
        printf("1953072 –§≈Ù∑…\n");
        fflush(stdout);
        sleep(5);
    }
    
    return 0;
}