#include <stdio.h>
#include <stdlib.h>
 
int main()
{
	int pipe_fd[2];
	pid_t pid;
	char r_buf[4096];
	char w_buf[4096];
	int writenum;
	int rnum;
	memset(r_buf,0,sizeof(r_buf));
	if(pipe(pipe_fd)<0)
	{
		printf("[PARENT] pipe create error\n");
		return -1;
	}

	//child process
	if((pid=fork()) == 0)
	{
		close(pipe_fd[1]);
		while(1)
		{
			rnum = read(pipe_fd[0],r_buf,1000);
			printf("[CHILD ] readnum is %d\n",rnum);
			if(rnum == 0) /*meet EOF*/
			{
				printf("[CHILD ] all the writer of pipe are closed. break and exit.\n");
				break;
			}
		}
		close(pipe_fd[0]);
		exit(0);
	}

	//parent process
	else if(pid>0)
	{
		close(pipe_fd[0]);
		memset(w_buf,0,sizeof(w_buf));
		if((writenum = write(pipe_fd[1],w_buf,4096)) == -1)
			printf("[PARENT] write to pipe error\n");
		else
		{
			printf("[PARENT} the bytes write to pipe is %d \n", writenum);
		}

		sleep(3);
		printf("[PARENT} I will close the last write end of pipe.\n");
		close(pipe_fd[1]);

		sleep(2);
		return 0;
	}
}

