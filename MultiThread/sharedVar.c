#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#define LOOP_TIMES 10000000
#define NR_THREAD 4
pthread_rwlock_t rwlock;
int global_cnt = 0;

void *thread_work(void *param)
{
	int i;

	pthread_rwlock_rdlock(&rwlock);
	for(i = 0; i < LOOP_TIMES;i++)
	{
		global_cnt++;
	}
	pthread_rwlock_unlock(&rwlock);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid[NR_THREAD];
	char err_buf[1024];
	int i, ret;
	
	ret = pthread_rwlock_init(&rwlock,NULL);
	if(ret)
	{
		fprintf(stderr,"init rw lock failed (%s)\n",strerror_r(ret,err_buf,sizeof(err_buf)));
		exit(1);
	}

	pthread_rwlock_wrlock(&rwlock);

	for(i = 0; i < NR_THREAD; i++)
	{
		ret = pthread_create(&tid[i],NULL,thread_work,NULL);
		if(ret != 0)
		{
			fprintf(stderr,"create thread failed,return %d (%s)\n",ret,strerror_r(ret,err_buf,sizeof(err_buf)));
		}
	}

	pthread_rwlock_unlock(&rwlock);

	for(i = 0 ; i < NR_THREAD; i++)
	{
		pthread_join(tid[i],NULL);
	}

	pthread_rwlock_destroy(&rwlock);

	printf("thread num	: %d\n",NR_THREAD);
	printf("loops per thread: %d\n",LOOP_TIMES);
	printf("expect result	: %d\n",LOOP_TIMES*NR_THREAD);
	printf("actual result	: %d\n",global_cnt);
	
	exit(0);
}













