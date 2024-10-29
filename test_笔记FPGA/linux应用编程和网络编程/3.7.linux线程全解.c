/*
//=======================================================================================================
									3.7.linux线程全解
//=======================================================================================================
3.7.1.再论进程
3.7.2.线程的引入
3.7.3.线程常见函数
3.7.4.线程同步之信号量1
3.7.5.线程同步之信号量2
3.7.6.线程同步之互斥锁 
3.7.7.线程同步之条件变量
//=======================================================================================================
3.7.1.再论进程
	本节再次回顾进程, 使用多进程的方式解决同时读取键盘和鼠标的问题, 从而让大家体会进程的调度特性带来的
	IO并发解决方案.
3.7.2.线程的引入
	本节使用线程再次重写解决同时读取键盘和鼠标的问题, 让大家体会进程和线程的相同之处, 然后再讲解线程机
	制的优势.
3.7.3.线程常见函数
	本节对线程编程中常用的一些主要函数进行讲解, 其实围绕着讲解线程编程的细节也就出来了.
3.7.4.线程同步之信号量1
	本节开始讲解线程同步, 主要是线程同步的概念和原因, 然后开始讲线程同步的第一种方法信号量.
3.7.5.线程同步之信号量2
	本节接上节讲解信号量来做线程同步, 并且从零开始写了一个案例来演示信号量如何实现线程同步,
3.7.6.线程同步之互斥锁 
	本节引入互斥锁, 并且使用互斥锁技术来实现线程同步, 再进行代码实践.
3.7.7.线程同步之条件变量
	本节讲解线程同步的第三种办法条件变量, 并且进行代码编程实践使用条件变量来完成上节课的例子.
//=======================================================================================================
									3.7.1.再论进程
//-------------------------------------------------------------------------------------------------------
	1. 多进程实现同时读取键盘和鼠标
		
		1) 思路: 创建子进程, 然后父子进程中分别进行读键盘和鼠标的工作.

		2) 程序设计:
		
			int main(void)
			{
				// 思路就是创建子进程，然后父子进程中分别进行读键盘和鼠标的工作
				int ret = -1;
				int fd = -1;
				char buf[200];
				
				ret = fork();										// 创建子进程
				if (ret == 0)
				{
					// 子进程
					fd = open("/dev/input/mouse1", O_RDONLY);		// 不能设置为非阻塞
					if (fd < 0)
					{
						perror("open:");
						return -1;
					}
					while (1)
					{
						memset(buf, 0, sizeof(buf));
						printf("before read.\n");
						read(fd, buf, 50);
						printf("读出鼠标的内容是：[%s].\n", buf);
					}	
				}
				else if (ret > 0)
				{
					// 父进程
					while (1)
					{
						memset(buf, 0, sizeof(buf));
						printf("before read.\n");
						read(0, buf, 5);
						printf("读出键盘的内容是：[%s].\n", buf);			
					}
				}
				else
				{
					perror("fork:");
				}
				return 0;
			}
			
	

	2. 使用进程技术的优势
	
		1) CPU时分复用, 单核心CPU可以实现宏观上的并行.
		2) 实现多任务系统需求(多任务的需求是客观的).
		
	3. 进程技术的劣势
	
		1) 进程间切换开销大.
		2) 进程间通信麻烦而且效率低.
		
			进程与进程是天然隔离的. 有好的方面也有不好的方面, 通信就是不好的一方面, 通信很麻烦效率低.
		
	4. 解决方案就是线程技术
	
		1) 线程技术保留了进程技术实现多任务的特性. (线程也被操作系统调度)
		2) 线程的改进就是在线程间切换和线程间通信上提升了效率.
		3) 多线程在多核心CPU上面更有优势.

//=======================================================================================================
									3.7.2.线程的引入
//-------------------------------------------------------------------------------------------------------
	1. 线程的引入
		
		本节还没讲线程的一些函数, 先使用实现上一节的键盘鼠标同时读取的功能.
	
	2. 使用线程技术同时读取键盘和鼠标
	
		void *func(void *arg)
		{
			while (1)
			{
				memset(buf, 0, sizeof(buf));
				printf("before read.\n");
				read(0, buf, 5);
				printf("读出键盘的内容是：[%s].\n", buf);			
			}	
			
		}

		int main(void)
		{
			// 思路就是创建子进程，然后父子进程中分别进行读键盘和鼠标的工作
			int ret = -1;
			int fd = -1;
			pthread_t th = -1;									// 用于接收新创建的线程的标识符
			
			ret = pthread_create(&th, NULL, func, NULL);		// 创建线程
			
			if (ret != 0)
			{
				printf("pthread_create error.\n");
				return -1;
			}
			// 主任务
			fd = open("/dev/input/mouse1", O_RDONLY);
			if (fd < 0)
			{
				perror("open:");
				return -1;
			}
			while (1)
			{
				memset(buf, 0, sizeof(buf));
				printf("before read.\n");
				read(fd, buf, 50);
				printf("读出鼠标的内容是：[%s].\n", buf);
			}	
			return 0;
		}		
	
		(!!!!!!) 注意编译的时候依赖动态链接库: gcc xxx.c -lpthread
	
	3. linux中的线程简介
	
		1) 一种轻量级进程.
		2) 线程是参与内核调度的最小单元.
		3) 一个进程中可以有多个线程.
		
	4. 线程技术的优势
	
		1) 像进程一样可被OS调度.
		2) 同一进程的多个线程之间很容易高效率通信.
			相当于两个函数进行通信, 可以使用全局变量.
		3) 在多核心CPU(对称多处理器架构SMP)架构下效率最大化.

//=======================================================================================================
									3.7.3.线程常见函数
//-------------------------------------------------------------------------------------------------------
	1. 线程常见函数

		1) 线程创建与回收
		
			pthread_create			主线程用来创造子线程的
			pthread_join			主线程用来等待(阻塞)回收子线程
			pthread_detach			主线程用来分离子线程, 分离后主线程不必再去回收子线程
			
			总结: 
				上一节程序没有考虑子线程回收问题. 因为子线程是死循环, 应该用pthread_detach()函数.

		2) 线程取消
		
			pthread_cancel			一般都是主线程调用该函数去取消(让它赶紧死)子线程
			pthread_setcancelstate	子线程设置自己是否允许被取消
			pthread_setcanceltype

		3) 线程函数退出相关(子线程自己退出)
		
			pthread_exit与return	退出
			pthread_cleanup_push
			pthread_cleanup_pop

		4) 获取线程id

			pthread_self			
	
	2. pthread_create 线程创建函数
		
       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.	
	   
		1) (!!!!!!) 编译时要加 -lpthread

		2) pthread_create函数用于创建一个新线程并使其运行指定的函数. 以下是每个参数的详细解释：

			a) pthread_t *thread：此参数是一个指向pthread_t类型的指针, 用于接收新创建的线程的标识符.
			   pthread_t类型是一个无符号长整型(unsigned long int).
			b) const pthread_attr_t *attr：此参数是一个指向pthread_attr_t类型的指针, 用于设置新线程
			   的属性. 如果传入NULL, 那么将使用默认的线程属性. 要自定义线程属性, 请使用
			   pthread_attr_init、pthread_attr_setdetachstate等函数.
			c) void *(*start_routine) (void *)：此参数是一个指向函数的指针. 该函数将在新线程中运行,
			   函数的返回值类型为void *, 并接受一个void *类型的参数.
			d) void *arg：此参数是一个指向void的指针, 将被传递给start_routine函数.
			e) pthread_create函数的原码通常位于glibc库中.
			f) On  success, pthread_create() returns 0; on error, it returns an error number, and 
			   the contents of *thread are unde‐fined.
			   
	3. pthread_join (主线程用来等待(阻塞)回收子线程)
	
       int pthread_join(pthread_t thread, void **retval);

       Compile and link with -pthread.
	
	4. pthread_detach (主线程用来分离子线程, 分离后主线程不必再去回收子线程)
	
       int pthread_detach(pthread_t thread);

       Compile and link with -pthread.

	5. 	pthread_cancel	(一般都是主线程调用该函数去取消子线程)

	    int pthread_cancel(pthread_t thread);

		Compile and link with -pthread.
		
		是否可以结束子线程, 还得看子线程是否允许被取消.

	6.	pthread_setcancelstate,pthread_setcanceltype	
	
       int pthread_setcancelstate(int state, int *oldstate);
       int pthread_setcanceltype(int type, int *oldtype);
	
	7. pthread_exit (子线程自己退出)

		void pthread_exit(void *retval);

		retval会被返回给主线程的pthread_join()函数. pthread_join()函数的第二个参数是二重指针.
		
		(!!!!!!) 子线程中的返回可以使用return返回, 但是不能用exit()函数来返回, 因为exit返回时,
		          会把进程结束.

	8. 	pthread_cleanup_push(),	pthread_cleanup_pop()
	
       void pthread_cleanup_push(void (*routine)(void *), void *arg);
       void pthread_cleanup_pop(int execute);

		(?????) 一些内容理解可能不正确, 例子来自课程的举例.
		
		1) 主线程可以通道 pthread_cancel 主动终止子线程, 但是子线程中可能还有未被释放的资源, 比如
		    获取了互斥锁等资源. 需要清理.
			
		2) pthread_cleanup_push 的作用是创建栈帧, 设置回调函数, 该过程相当于入栈. 相当于压入了一个
		   回调函数, 在成对出现的pthread_cleanup_pop()函数调用时被执行(该函数参数为非0时, 为0时不会
		   调用).
		   
		3) 两个函数必须成对使用.
		
		4) 子线程中, cnt表示资源互斥量.
			
			if(cnt==0)
			{
				cnt++;					// 上锁
				
				pthread_cleanup_push(func, arg);
				
				// 资源xx使用中
				
				pthread_cleanup_pop(0);				// 
				
				cnt--;					// 解锁
			}

			void func(void)
			{
				cnt--					// 解锁
			}

			a) 如果主线程取消时子进程运行在上锁后, 解锁前的程序段, 则会有问题.
			b) pthread_cleanup_push(func, arg), 压栈一个回调函数.
			c) pthread_cleanup_pop(0), 0表示执行回调函数. 非0表示不执行.

	9. pthread_self 获取线程ID
	
		pthread_t pthread_self(void);

//=======================================================================================================
									3.7.4-5.线程同步之信号量1,2
//-------------------------------------------------------------------------------------------------------
	1. 任务：用户从终端输入任意字符然后统计个数显示, 输入end则结束.
	
		while(1)
		{
			scanf("%s",buf);
			printf("本次输入了%d个字符.\n", strlen(buf));
			memset(buf,0,sizeof(buf));
		}
		
		while(scanf("%s",buf))
		{
			printf("本次输入了%d个字符.\n", strlen(buf));
			memset(buf,0,sizeof(buf));
		}
		
		(!!!!!) 两种写法是一样的. 
		(!!!!!) while(scanf("%s",buf))永远出不来循环体, 因为scanf()是阻塞的, 函数返回肯定是非0, 永远
		        不会退出循环体.
	
	
	2. 使用多线程实现：主线程获取用户输入并判断是否退出, 子线程计数.
	
		1) 为什么需要多线程实现
		2) 问题和困难点是？
		3) 理解什么是线程同步
		
	3. 信号量的介绍和使用
	
		1) 信号量定义:
		
			sem_t sem;			// 两个线程, 所以是一个全局变量.
			
		2) 信号量初始化:
		
		    int sem_init(sem_t *sem, int pshared, unsigned int value);
			
			a) The pshared argument indicates whether this semaphore is to be shared between the 
			   threads of a process,  or  between processes.

			   If  pshared has the value 0, then the semaphore is shared between the threads of a 
			   process, and should be located at some address that is visible to all threads (e.g., 
			   a global variable, or a variable  allocated  dynamically  on  the heap).

			   If  pshared  is nonzero, then the semaphore is shared between processes, and should 
			   be located in a region of shared  memory. 
				
			   (!!!!!) 一般设置为0.	
			
			b) int value, 设置初值.

		3) 信号量激活
		
			int sem_post(sem_t *sem);

		4) 信号量获取

			int sem_wait(sem_t *sem);

		5) 信号量销毁
		
			int sem_destroy(sem_t *sem);

	4. 程序实现:

		// 子线程程序，作用是统计buf中的字符个数并打印
		void *func(void *arg)
		{
			// 子线程首先应该有个循环
			// 循环中阻塞在等待主线程激活的时候，子线程被激活后就去获取buf中的字符
			// 长度，然后打印；完成后再次被阻塞
			sem_wait(&sem);
			while (strncmp(buf, "end", 3) != 0)
			{	
				printf("本次输入了%d个字符\n", strlen(buf));
				memset(buf, 0, sizeof(buf));
				sem_wait(&sem);
			}
			pthread_exit(NULL);
		}
		
		int main(void)
		{
			int ret = -1;
			pthread_t th = -1;
			
			sem_init(&sem, 0, 0);
			
			ret = pthread_create(&th, NULL, func, NULL);
			if (ret != 0)
			{
				printf("pthread_create error.\n");
				exit(-1);
			}
			
			printf("输入一个字符串，以回车结束\n");
			while (scanf("%s", buf))
			{
				// 去比较用户输入的是不是end，如果是则退出，如果不是则继续		
				if (!strncmp(buf, "end", 3))
				{
					printf("程序结束\n");
					sem_post(&sem);	
					break;
				}
				sem_post(&sem);	
			}
			// 回收子线程
			printf("等待回收子线程\n");
			ret = pthread_join(th, NULL);
			if (ret != 0)
			{
				printf("pthread_join error.\n");
				exit(-1);
			}
			printf("子线程回收成功\n");
			
			sem_destroy(&sem);
			
			return 0;
		}


	5. 注意问题:
	
		1) 
			a) 主线程中, 输入end后退出, 回收子线程.
		
				// 回收子线程
				printf("等待回收子线程\n");
				ret = pthread_join(th, NULL);
				if (ret != 0)
				{
					printf("pthread_join error.\n");
					exit(-1);
				}
				printf("子线程回收成功\n");
		
			b) 而在子线程中, 如果是while(1)类似的死循环, 则主线程会一致回收不成功.
			
				while (1)
				{	
					printf("本次输入了%d个字符\n", strlen(buf));
					memset(buf, 0, sizeof(buf));
					sem_wait(&sem);
				}
			
			总结: 这样不会收回成功, 因为子线程是死循环.

//=======================================================================================================
									3.7.6.线程同步之互斥锁 
//-------------------------------------------------------------------------------------------------------
	1. 什么是互斥锁
	
		1) 互斥锁又叫互斥量(mutex)
		
		2) 相关函数：pthread_mutex_init, pthread_mutex_destroy
					 pthread_mutex_lock, pthread_mutex_unlock
					 
			pthread_mutex_lock() 上锁时, 如果已经被锁, 则阻塞.		 
					 
		3) 互斥锁和信号量的关系：可以认为互斥锁是一种特殊的信号量.
		
		4) 互斥锁主要用来实现"关键段保护".
		
	2. 用互斥锁来实现上节的代码(这个实例用互斥锁不太合适)
	
		pthread_mutex_t mutex;

		pthread_mutex_lock(&mutex);
		
		// 临界代码.
		
		pthread_mutex_unlock(&mutex);

		pthread_mutex_destroy(&mutex);

	注意：
			man 3 pthread_mutex_init时提示找不到函数, 说明你没有安装pthread相关的man手册(系统默认没安装).
			安装方法：1、虚拟机上网; 2、sudo apt-get install manpages-posix-dev

//=======================================================================================================
									3.7.7.线程同步之条件变量
//-------------------------------------------------------------------------------------------------------
	1. 什么是条件变量
	
	2.相关函数
	
		pthread_cond_init		pthread_cond_destroy
		pthread_cond_wait		pthread_cond_signal/pthread_cond_broadcast

	3. 使用条件变量来实现上节代码
		
		1) 定义互斥量,条件变量
		
			pthread_mutex_t mutex;
			pthread_cond_t cond;

		2) 主线程中舒适化, 给出条件变量	

			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);

			pthread_cond_signal(&cond);
			
			pthread_mutex_destroy(&mutex);
			pthread_cond_destroy(&cond);

			
		3) 子线程中获取条件变量
		
			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);
			printf("本次输入了%d个字符\n", strlen(buf));
			memset(buf, 0, sizeof(buf));
			pthread_mutex_unlock(&mutex);
			

	4. 线程同步总结
		
		1) 条件变量使用时, 需要一个互斥量.
		
			pthread_cond_wait(&cond, &mutex);
		
		2) 等待条件变量时, 前面给互斥量加锁.

			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);
			//---------------------
			// 条件成立, 执行操作.
			//---------------------
			pthread_mutex_unlock(&mutex);

//=======================================================================================================






