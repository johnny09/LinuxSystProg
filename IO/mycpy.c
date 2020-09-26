#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 48

int main(int argc,char **argv)
{
	int fds, fdd;
	char buf[BUF_SIZE];
	ssize_t readByteNum = 0,writeByteNum = 0;
	if(argc < 3)
	{
		fprintf(stderr,"Usage..\n");
		exit(1);
	}

	fds = open(argv[1],O_RDONLY);
	if(fds < 0)
	{
		perror("open()");//read only
		exit(1);
	}

	fdd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0600);//write only
	if(fdd < 0)
	{
		perror("open()");
		close(fds);//close the opened source file
		exit(1);
	}

	//copy	
	while(1)
	{
		readByteNum = read(fds,buf,BUF_SIZE);
		//read fail
		if(readByteNum < 0)
		{
			perror("read()");
			break;//break to close the file
		}

		//read to the end
		if(readByteNum == 0)
		{
			break;//break to close the file	
		}
		
		writeByteNum = write(fdd,buf,readByteNum);
		if(writeByteNum < 0)
		{
			perror("write()");
			break;
		}	
	}

	close(fds);
	close(fdd);
	exit(0);
}
