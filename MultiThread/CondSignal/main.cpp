#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//节点结构体
struct msg
{
    int num; //数据区
    struct msg *next; //链表区
};
 
struct msg *head = NULL;//头指针
struct msg *mp = NULL;  //节点指针
//利用宏定义的方式初始化全局的互斥锁和条件变量
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
 
void *producter(void *arg)
{
    while (1) 
	{
        mp = (struct msg*)malloc(sizeof(struct msg));
        mp->num = rand() % 400 + 1;
        printf("---producted---%d\n", mp->num);
 
        pthread_mutex_lock(&mutex);//访问共享区域必须加锁
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);
 
        pthread_cond_signal(&has_product);//通知消费者来消费
		
        sleep(rand() % 3);
    }
 
    return NULL;
}
 
void *consumer(void *arg)
{
    while (1)
	{
        pthread_mutex_lock(&mutex);//访问共享区域必须加锁
        while (head == NULL)//如果共享区域没有数据，则解锁并等待条件变量
	{
            pthread_cond_wait(&has_product, &mutex);
        }
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&mutex);
 
        printf("------------------consumer--%d\n", mp->num);
        free(mp); //释放被删除的节点内存
        mp = NULL;//并将删除的节点指针指向NULL，防止野指针
		
        sleep(rand() % 3);
    }
 
    return NULL;
}
 
int main(void)
{
    pthread_t ptid, ctid;
 
    //创建生产者和消费者线程
    pthread_create(&ptid, NULL, producter, NULL);
    pthread_create(&ctid, NULL, consumer, NULL);
    //主线程回收两个子线程
    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
 
    return 0;
}