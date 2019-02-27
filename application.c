#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define BUFFER_LENGTH 256
static char recieve[BUFFER_LENGTH];
int main()
{
	int ret,fd;
	char stringToSend[BUFFER_LENGTH];
	printf("starting device test code example....\n");
	fd=open("/dev/Marvellous Driver 1",O_RDWR);
	if(fd<0)
	{
		perror("failed to open device..\n");
		return errno;
	}
	printf("type in a short string to send to the kernel module\n");
	scanf("%[^'\n']%*c",stringToSend);
	printf("writing message to the device[%s]\n",stringToSend);
	ret=write(fd,stringToSend,strlen(stringToSend));
	if(ret<0)
	{
		perror("failed to write the message to the device\n");
		return errno;
	}
	printf("press ENTER to read back from device\n");
	getchar();
	printf("Reading from the device\n");
	ret=read(fd,recieve,BUFFER_LENGTH);
	if(ret<0)
	{
		perror("failed to read the message from the device");
		return errno;
	}
	printf("the recieved message is:[%s]\n",recieve);
	printf("end of program\n");
	close(fd);
	return 0;
}
