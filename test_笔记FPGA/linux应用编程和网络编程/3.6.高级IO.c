/*
//=======================================================================================================
									3.6.高级IO
//=======================================================================================================
3.6.1.非阻塞IO
3.6.2.阻塞式IO的困境
3.6.3.并发式IO的解决方案
3.6.4.IO多路复用原理
3.6.5.IO多路复用实践
3.6.6.异步IO
3.6.7.存储映射IO
//=======================================================================================================
3.6.1.非阻塞IO
	本节讲解什么是非阻塞IO, 如何将文件描述符修改为非阻塞式.
3.6.2.阻塞式IO的困境
	本节通过实例代码运行结果, 让大家看到在并发式IO访问时非阻塞IO遭遇的困境, 由此引入非阻塞式IO.
3.6.3.并发式IO的解决方案
	本节介绍解决并发式IO问题的三种方法, 并且写代码进行讲解非阻塞式IO方法.
3.6.4.IO多路复用原理
	本节讲述IO多路复用的实现原理和相关函数select、poll的参数和使用要点.
3.6.5.IO多路复用实践
	本节进行代码实践, 使用select和poll来实际解决前面的同时读取鼠标和键盘的任务.
3.6.6.异步IO
	本节讲解异步IO的实现原理, 并且实际写代码用异步IO实现同时读取鼠标和键盘.
3.6.7.存储映射IO
	本节以LCD显示和SystemV IPC的共享内存为案例, 简单分析了存储映射IO的原理和优势.
//=======================================================================================================
									3.6.1.非阻塞IO
//-------------------------------------------------------------------------------------------------------
	1. 阻塞与非阻塞
	
	2. 为什么有阻塞式
	
		1) 常见的阻塞：
			
			a) 函数本身就是阻塞: wait、pause、sleep等函数; 
			
			b) 操作某些对象时, 会阻塞: read或write某些文件(???设备文件)时.
		
		2) 阻塞式的好处
			
			阻塞时, 进程并不消耗CPU;
			有时候对于整个系统来说, 阻塞更合理, 且好实现.
			
	3. 非阻塞

		1) 为什么要实现非阻塞.
			
			多路IO时, 比如读取鼠标&键盘的输出, 读取鼠标时, 就不能使用阻塞式, 必须使用非阻塞访问.
		
		2) 如何实现非阻塞IO访问：O_NONBLOCK和fcntl.
			
			O_NONBLOCK: 打开文件的时候加这个标记, 以非阻塞方式打开. 获取的文件描述符去读写时就是非阻塞.
			
			fcntl:		对于已经打开的文件, 使用这个函数修改文件描述符属性.

//=======================================================================================================
									3.6.2.阻塞式IO的困境
//-------------------------------------------------------------------------------------------------------
	1. 程序中读取键盘
	
		int main(void)
		{
			// 读取键盘
			// 键盘就是标准输入，stdin
			
			char buf[100];
			
			memset(buf, 0, sizeof(buf));
			printf("before read.\n");
			read(0, buf, 5);						// 标准输入的fd=0
			printf("读出的内容是：[%s].\n", buf);
			
			return 0;
		}
		
		1) 标准输入就是键盘, 文件描述符是0.  stdin是默认打开的, 直接用文件描述符.
		2) read(0, buf, 5); 标准输入读取5个字节, 会阻塞.
		3) 命令行输入是行缓冲, 输入的字符都在控制台缓冲区保存着, 需要按下回车, 才写入stdin中.
		4) 输入"12345678" 回车.
			
			输出内容:
				before read.
				12345678
				读出的内容是：[12345].
				root@ubuntu:~/l_software/3/6.seniorIO# 678
				678: command not found
			
			(?????) 剩下的678被当做命令去执行??????

	2. 程序中读取鼠标
	
		int main(void)
		{
			// 读取鼠标
			int fd = -1;
			char buf[200];
			
			fd = open("/dev/input/mouse1", O_RDONLY);
			if (fd < 0)
			{
				perror("open:");
				return -1;
			}
			
			memset(buf, 0, sizeof(buf));
			printf("before read.\n");
			read(fd, buf, 50);
			printf("读出的内容是：[%s].\n", buf);
			
			return 0;
		}
	
		1) 鼠标设备文件ls /dec/input/下mouse0 mouse1 , 先选择一个,cat /dec/input/mouse0, 移动鼠标,
		   看终端是否有数据.
				cat 会阻塞住, 一定鼠标, 会出现乱码. CTRL+C终止程序.
				
		2) 鼠标文件系统默认没有打开, 需要先打开文件.
		3) 控制台上打印的都是乱码, 是因为鼠标输出的数据都是二进制的, 而控制台是用字符解析的, 所以会
		   是乱码, 这个要等到学了鼠标的驱动, 就会明白.
		   
	3. 程序中同时读取键盘和鼠标
	
		int main(void)
		{
			int fd = -1;
			char buf[200];
			
			fd = open("/dev/input/mouse1", O_RDONLY);
			if (fd < 0)
			{
				perror("open:");
				return -1;
			}
			
			// 读取鼠标
			memset(buf, 0, sizeof(buf));
			printf("before 鼠标 read.\n");
			read(fd, buf, 50);
			printf("鼠标读出的内容是：[%s].\n", buf);
			
			// 读键盘
			memset(buf, 0, sizeof(buf));
			printf("before 键盘 read.\n");
			read(0, buf, 5);
			printf("键盘读出的内容是：[%s].\n", buf);
			
			return 0;
		}		
		
		问题分析: 只能先动鼠标, 再动键盘程序才可正常工作. 如果先操作键盘, 则不会读取键盘数据(阻塞在鼠标
		          读取数据处).

//=======================================================================================================
									3.6.3.并发式IO的解决方案
//-------------------------------------------------------------------------------------------------------
	1. 非阻塞式IO
	
		1) stdin的文件描述符是0 , 默认是阻塞方式打开的. 
		
		2) 用fcntl函数修改键盘打开方式.
		
			// 把0号文件描述符（stdin）变成非阻塞式的
			flag = fcntl(0, F_GETFL);		// 先获取原来的flag
			flag |= O_NONBLOCK;				// 添加非阻塞属性
			fcntl(0, F_SETFL, flag);		// 更新flag
				
			(?????) 文件描述符和这里的flag是一个东西??? 应该不是!
			
		3) 	鼠标文件以非阻塞打开
		
			fd = open("/dev/input/mouse1", O_RDONLY | O_NONBLOCK);
		
		4) 代码测试:
		
			int main(void)
			{
				// 读取鼠标
				int fd = -1;
				int flag = -1;
				char buf[200];
				int ret = -1;
				
				fd = open("/dev/input/mouse1", O_RDONLY | O_NONBLOCK);
				if (fd < 0)
				{
					perror("open:");
					return -1;
				}
				
				// 把0号文件描述符（stdin）变成非阻塞式的
				flag = fcntl(0, F_GETFL);		// 先获取原来的flag
				flag |= O_NONBLOCK;				// 添加非阻塞属性
				fcntl(0, F_SETFL, flag);		// 更新flag
				// 这3步之后，0就变成了非阻塞式的了
				
				while (1)
				{
					// 读鼠标
					memset(buf, 0, sizeof(buf));
					//printf("before 鼠标 read.\n");
					ret = read(fd, buf, 50);
					if (ret > 0)
					{
						printf("鼠标读出的内容是：[%s].\n", buf);
					}
					
					// 读键盘
					memset(buf, 0, sizeof(buf));
					//printf("before 键盘 read.\n");
					ret = read(0, buf, 5);
					if (ret > 0)
					{
						printf("键盘读出的内容是：[%s].\n", buf);
					}
				}
				return 0;
			}
	
	总结:
			1) 尝试用非阻塞的方式解决上节问题.
			
			2) 多路复用IO, 异步IO也是解决上述问题, 且效率更高.
			
			3) 两种以非阻塞打开文件的方法.

//=======================================================================================================
									3.6.4-5.IO多路复用原理, 实践
//-------------------------------------------------------------------------------------------------------
	1. 何为IO多路复用
	
		1) IO multiplexing.
		
		2) 用在什么地方？
		
			多路,且非阻塞式IO, 为了达到性能或者及时响应的目的, 发明了IO多路复用.
			
		3) 解决什么问题?
		
		    上一节非阻塞式的设计, 像是轮询的方式的, CPU要不停的去读取. 这种轮询有缺陷: 轮询周期越短,
			越浪费CPU, 时间太长, 响应不及时, 或者漏掉事件.
			
	2. select和poll
	
		1) 实现了IO多路复用, 用法也差不多.
		2) UNIX发展了几个支路, select和poll可能是两个不同的分支使用的函数. 到了后来的LINUX, 兼容了这
		   两个实现方法.
	
		3) 实现原理:
			
			外部阻塞式, 内部非阻塞式 自动轮询 多路阻塞式IO
			
			a) select函数外部看, 阻塞式的.
			b) 内部是非阻塞式自动轮询的.
			c) 被轮询的多路IO是阻塞式的.
			d) 多路IO是阻塞的, select函数内部是非阻塞式查询的. 非阻塞式如何读取阻塞IO, 这个不用去管,是
			   该函数去做的.
			
	3. select函数介绍
		
		1) man 2 select
		
		   int select(int nfds, fd_set *readfds, fd_set *writefds, 
					  fd_set *exceptfds, struct timeval *timeout);
		
		   void FD_CLR(int fd, fd_set *set);
		   int  FD_ISSET(int fd, fd_set *set);
		   void FD_SET(int fd, fd_set *set);
		   void FD_ZERO(fd_set *set);

			a) int nfds, 多路IO中最大的文件描述符+1.
			
			b) struct fd_set可以理解为一个集合, 这个集合中存放的是文件描述符(filedescriptor), 即文件
			   句柄.
			   
			    fd_set集合可以通过一些宏由人为来操作，比如：
				FD_ZERO(fd_set *);清空集合
				FD_SET(int, fd_set *);将一个给定的文件描述符加入集合之中
				FD_CLR(int, fd_set*); 将一个给定的文件描述符从集合中删除
				检查集合中指定的文件描述符是否可以读写FD_ISSET(int ,fd_set* )
				
			c)  fd_set* readfds：是指向fd_set结构的指针, 这个集合中应该包括文件描述符, 我们是要监视这
				些文件描述符的"读"变化的, 即我们关心是否可以从这些文件中 读取数据了, 如果这个集合中有
				一个文件可读, select就会返回一个大于0的值, 表示有文件可读, 如果没有可读的文件, 则根据
				timeout参数再判断 是否超时, 若超出timeout的时间, select返回0, 若发生错误返回负值. 可以
				传入NULL值, 表示不关心任何文件的读变化.
				
				fd_set* writefds：是指向fd_set结构的指针, 这个集合中应该包括文件描述符, 我们是要监视这
				些文件描述符的写变化的, 即我们关心是否可以向这些文件 中写入数据了, 如果这个集合中有一个
				文件可写, select就会返回一个大于0的值, 表示有文件可写, 如果没有可写的文件, 则根据
				timeout参数再判 断是否超时, 若超出timeout的时间, select返回0, 若发生错误返回负值. 可以
				传入NULL值, 表示不关心任何文件的写变化.
				
				fd_set * errorfds：同上面两个参数的意图, 用来监视文件错误异常.
				
				struct timeval 是一个大家常用的结构, 用来代表时间值, 有两个成员, 一个是秒数, 另一个是微秒.
				
				select 返回值：
					负值：	select错误
					正值：	某些文件可读写或出错
					0：		等待超时，没有可读写或错误的文件	
					
		2) 代码测试
		
			int main(void)
			{
				// 读取鼠标
				int fd = -1, ret = -1;
				char buf[200];
				fd_set myset;
				struct timeval tm;
				
				fd = open("/dev/input/mouse1", O_RDONLY);
				if (fd < 0)
				{
					perror("open:");
					return -1;
				}
				// 当前有2个fd，一共是fd一个是0
				// 处理myset
				FD_ZERO(&myset);
				FD_SET(fd, &myset);									// 添加两个文件描述符
				FD_SET(0, &myset);
				
				tm.tv_sec = 10;
				tm.tv_usec = 0;

				ret = select(fd+1, &myset, NULL, NULL, &tm);		// 不关心传入NULL(!!!!!)
				if (ret < 0)
				{
					perror("select: ");
					return -1;
				}
				else if (ret == 0)
				{
					printf("超时了\n");
				}
				else
				{
					// 等到了一路IO，然后去监测到底是哪个IO到了，处理之
					if (FD_ISSET(0, &myset))						// 判断是否文件有写变化.
					{
						// 这里处理键盘
						memset(buf, 0, sizeof(buf));
						read(0, buf, 5);
						printf("键盘读出的内容是：[%s].\n", buf);
					}
					if (FD_ISSET(fd, &myset))
					{
						// 这里处理鼠标
						memset(buf, 0, sizeof(buf));
						read(fd, buf, 50);
						printf("鼠标读出的内容是：[%s].\n", buf);
					}
				}
				return 0;
			}

	4. poll函数介绍
		
		1) man 2 poll
		
			int poll(struct pollfd *fds, nfds_t nfds, int timeout);
			
		　　struct pollfd
			{
		　　　　int fd； 			// file descriptor
		　　　　short event；		// event of interest on fd		要检测的IO事件, 用户设置的.
		　　　	short revent；		// event that occurred on fd	发生的IO事件, 内核设置的.
		　　}
		
			poll函数的事件标志符值

			常量 说明
			POLLIN 普通或优先级带数据可读
			POLLRDNORM 普通数据可读
			POLLRDBAND 优先级带数据可读
			POLLPRI 高优先级数据可读
			POLLOUT 普通数据可写
			POLLWRNORM 普通数据可写
			POLLWRBAND 优先级带数据可写
			POLLERR 发生错误
			POLLHUP 发生挂起
			POLLNVAL 描述字不是一个打开的文件

			返回值和错误代码:
			
				成功时, poll()返回结构体中revents域不为0的文件描述符个数; 如果在超时前没有任何事件发
				生, poll()返回0; 失败时, poll()返回-1.

		2) 代码测试:
		
			int main(void)
			{
				// 读取鼠标
				int fd = -1, ret = -1;
				char buf[200];
				struct pollfd myfds[2] = {0};					// 定义成一个数组. poll()原型可知
				
				fd = open("/dev/input/mouse1", O_RDONLY);
				if (fd < 0)
				{
					perror("open:");
					return -1;
				}
				
				// 初始化我们的pollfd
				myfds[0].fd = 0;			// 键盘
				myfds[0].events = POLLIN;	// 等待读操作
				
				myfds[1].fd = fd;			// 鼠标
				myfds[1].events = POLLIN;	// 等待读操作

				ret = poll(myfds, fd+1, 10000);					// 
				if (ret < 0)
				{
					perror("poll: ");
					return -1;
				}
				else if (ret == 0)
				{
					printf("超时了\n");
				}
				else
				{
					// 等到了一路IO，然后去监测到底是哪个IO到了，处理之
					if (myfds[0].events == myfds[0].revents)
					{
						// 这里处理键盘
						memset(buf, 0, sizeof(buf));
						read(0, buf, 5);
						printf("键盘读出的内容是：[%s].\n", buf);
					}
					if (myfds[1].events == myfds[1].revents)
					{
						// 这里处理鼠标
						memset(buf, 0, sizeof(buf));
						read(fd, buf, 50);
						printf("鼠标读出的内容是：[%s].\n", buf);
					}
				}
				return 0;
			}

//=======================================================================================================
											3.6.6.异步IO
//-------------------------------------------------------------------------------------------------------
	1. 何为异步IO
	
		1) 几乎可以认为：异步IO就是'操作系统'用'软件实现'的一套中断响应系统.
		
		2) 异步IO的工作方法是：我们当前进程注册一个异步IO事件(使用signal注册一个信号SIGIO的处理函数),
		   然后当前进程可以正常处理自己的事情, 当异步事件发生后当前进程会收到一个SIGIO信号从而执行
		   绑定的处理函数去处理这个异步事件.
		   
	2. 涉及的函数：
	
		1) fcntl(F_GETFL、F_SETFL、O_ASYNC、F_SETOWN)
		
			a) 把鼠标的文件描述符设置为可以接受异步IO

				flag = fcntl(mousefd, F_GETFL);
				flag |= O_ASYNC;
				fcntl(mousefd, F_SETFL, flag);

			b) 把异步IO事件的接收进程设置为当前进程
			
				fcntl(mousefd, F_SETOWN, getpid());
	
		2) signal或者sigaction(SIGIO)
			
			a) 注册当前进程的SIGIO信号捕获函数
				
				signal(SIGIO, func);
		
	3. 代码实践(同时读取鼠标和键盘数据)
		
		// 绑定到SIGIO信号，在函数内处理异步通知事件
		void func(int sig)
		{
			char buf[200] = {0};
			
			if (sig != SIGIO)
				return;

			read(mousefd, buf, 50);
			printf("鼠标读出的内容是：[%s].\n", buf);
		}

		int main(void)
		{
			// 读取鼠标
			char buf[200];
			int flag = -1;
			
			mousefd = open("/dev/input/mouse1", O_RDONLY);
			if (mousefd < 0)
			{
				perror("open:");
				return -1;
			}	
			// 把鼠标的文件描述符设置为可以接受异步IO
			flag = fcntl(mousefd, F_GETFL);
			flag |= O_ASYNC;
			fcntl(mousefd, F_SETFL, flag);
			// 把异步IO事件的接收进程设置为当前进程
			fcntl(mousefd, F_SETOWN, getpid());
			
			// 注册当前进程的SIGIO信号捕获函数
			signal(SIGIO, func);
			
			// 读键盘
			while (1)
			{
				memset(buf, 0, sizeof(buf));
				//printf("before 键盘 read.\n");
				read(0, buf, 5);
				printf("键盘读出的内容是：[%s].\n", buf);
			}
			return 0;
		}

//=======================================================================================================
									3.6.7.存储映射IO
//-------------------------------------------------------------------------------------------------------
	1. 存储映射IO

		把文件和内存映射起来.
	
	2. mmap函数
	
		1) mmap就是memory map, 内存映射. 
		
		2) 裸机的时候讲到, LCD试验时, 在内存开辟了一个显示缓冲区, 这个内存区域与LCD的硬件上的内存对应,
		   内存缓冲区是什么东西, LCD就会显示什么东西.
		   
		3) 在操作系统下, 与LCD对应那块内存在内核中. 而应用程序读取的图片数据也需要有一个内存缓冲区(比如
		   需要把数据从硬盘读取). 这个内存其实是内核的一个映射, 这样才能提高处理速度.
		   
		4) mmap()函数就是做内存映射. 应用程序读取硬盘的图片, 复制一次就到了内核的LCD的缓冲区.
	
	4. 应用场景: LCD显示和IPC之共享内存
	
	5. 存储映射IO的特点
	
		1) 共享而不是复制, 减少内存操作.
		2) 处理大文件时效率高, 小文件不划算.

//=======================================================================================================







