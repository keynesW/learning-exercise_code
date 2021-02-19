/*线程生产消费模型*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;//初始化锁
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;//初始化条件变量

int accint =0;//定义全局变量位0（假定资产生产消费都会变化）
void *pthrducer_do(void *arg)//生产(赚)线程
{
	int i=0;
	while(1){
		pthread_mutex_lock(&mtx);//抢占锁
		i++;//生产
		accint++;//对应资产增
		printf("pthrducer :%d  accint :%d \n",i,accint);
		pthread_cond_signal(&cond);//条件完成通知其它变量
		pthread_mutex_unlock(&mtx);//释放锁
		sleep(4);//避免消费线程释放锁后立即抢占锁
	}
}

void *p_do(void *arg)//生产(赚)线程
{
    while(1)
    {
        pthread_cond_signal(&cond);//条件完成通知其它变量
        printf("p_do\n");
        sleep(4);
    }
}

void *pthrsumer_do(void *arg)//消费线程
{
	int i=0;
	while(1){
		pthread_mutex_lock(&mtx);//抢占锁
        
		if(accint<=0){      //判断条件资产不能为负
			pthread_cond_wait(&cond,&mtx);//条件不满足临时释放锁
		}
		i++;//消费量
		accint--;
		printf("pthrsumer:%d  accint  :%d\n",i,accint);
		pthread_mutex_unlock(&mtx);//释放锁
		sleep(4);//避免消费线程释放锁后立即抢占锁
	}
}

int main(int argc, const char *argv[])
{
	pthread_mutex_init(&mtx,NULL);//初始化锁

	pthread_t tid1,tid2,tid3;//定义两个变量保存线程号
	pthread_create(&tid1,NULL,pthrducer_do,NULL);//创建生产(赚钱)线程
	pthread_create(&tid2,NULL,pthrsumer_do,NULL);//创建消费线程
	pthread_create(&tid3,NULL,p_do,NULL);//创建消费线程

	pthread_join(tid1,NULL);//接收线程结束返回值
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mtx);//注销锁
	return 0;
}
