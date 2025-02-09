/*
//=======================================================================================================
									3.4.linux进程全解
//=======================================================================================================
3.4.1.程序的开始和结束
3.4.2.进程环境
3.4.3.进程的正式引入
3.4.4.fork创建子进程
3.4.5.父子进程对文件的操作
3.4.6.进程的诞生和消亡
3.4.7.父进程wait回收子进程
3.4.8.waitpid介绍
3.4.9.exec族函数及实战1
3.4.10.exec族函数及实战2
3.4.11.进程状态和system函数
3.4.12.进程关系
3.4.13.守护进程的引入
3.4.14.编写简单守护进程
3.4.15.使用syslog来记录调试信息
3.4.16.让程序不能被多次运行
3.4.17.linux的进程间通信概述
3.4.18.linux的IPC机制1-管道
3.4.19.SystemV IPC介绍
//=======================================================================================================
3.4.1.程序的开始和结束
	本节讲述一个典型程序的开始运行和结束运行, 引入引导代码让大家更容易的理解操作系统是如何运行一个程序的.
3.4.2.进程环境
	本节讲解进程的环境变量和虚拟地址空间, 这些都是一个进程在系统中运行时的外部环境.
3.4.3.进程的正式引入
	本节正式引入进程的概念, 讲述了进程的ID以及获取进程ID的函数, 多进程调度实现宏观上并行的原理.
3.4.4.fork创建子进程
	本节引入子进程, 并且讲解并实战演示了fork()函数如何创建子进程.
3.4.5.父子进程对文件的操作
	本节通过父子进程对文件的操作来说明父子进程的区别和联系.
3.4.6.进程的诞生和消亡
	本节讲述进程的诞生和消亡过程, 着重讲了僵尸进程和孤儿进程的概念, 进程资源回收和状态返回等.
3.4.7.父进程wait回收子进程
	本节讲解wait函数回收子进程的信号式异步通信工作原理, 并且实战演练了使用wait来回收子进程的过程.
3.4.8.waitpid介绍
	本节首先介绍waitpid和wait函数的差别, 然后实战演示了waitpid函数的3种常见用法, 最后简单讲解了竟态的
	概念.
3.4.9.exec族函数及实战1
	本节开始讲解exec族函数的作用和各个API的差异, 并且写代码进行演示.
3.4.10.exec族函数及实战2
	本节演示了exec族的p后缀和e后缀函数的用法.
3.4.11.进程状态和system函数
	本节详细讲解了linux中进程的5种状态和状态转换图, 最后讲了下system函数.
3.4.12.进程关系
	本节讲解进程的四种关系：无关系、父子关系、进程组和会话.
3.4.13.守护进程的引入
	本节引入守护进程的概念, 并且介绍了常见的一些系统级服务器守护进程及其作用.
3.4.14.编写简单守护进程
	本节实践编程自己实现一个守护进程, 让大家熟悉守护进程的创建过程.
3.4.15.使用syslog来记录调试信息
	本节讲解如何在程序中使用syslog记录日志信息, 这是一种非常常见的程序调试信息输出手段, 也是守护进程
	必用的调试信息输出手段.
3.4.16.让程序不能被多次运行
	本节介绍如何让我们的程序只能运行一次, 即所谓单例运行的常规实现方法. 这个在实际工作中很有用.
3.4.17.linux的进程间通信概述
	本节进行linux中进程间通信IPC的概述, 指明了后面如何讲解IPC.
3.4.18.linux的IPC机制1-管道
	本节详细讲了传统Unix的进程间通信方法：管道和有名管道.
3.4.19.SystemV IPC介绍	
	本节对SystemV IPC的三种(信号量、消息队列、共享内存)方式进行概括性讲解和对比.
//=======================================================================================================
									3.4.1.程序的开始和结束
//-------------------------------------------------------------------------------------------------------
	1. main()函数由谁调用
	
		1) 编译链接时的引导代码. 操作系统下的应用程序其实在main()执行前也需要先执行一段引导代码才能去
		   执行main(), 我们写应用程序时不用考虑引导代码的问题, 编译连接时(准确说是连接时)由链接器将编
		   译器中事先准备好的引导代码给连接进去和我们的应用程序一起构成最终的可执行程序.
		
			a) 裸机程序中, 开始时汇编阶段的引导代码start.S, 之后才能执行main()函数. 
			   操作系统中, 也需要一段引到代码, 只不过这段代码时操作系统帮我们添加的.
			b) 操作系统添加的引导代码的作用: 构建C语言运行环境((???)数据区数据赋值, 清BSS段, 重定位等).
			c) 同一个操作系统上, 应用程序的引到代码是一样的, 是由操作系统帮我们提供的. 
			d) gcc xx.c 编译时, 不用指定链接脚本,  GCC默认使用了一个链接脚本, 是固定的.  
			e) gcc -v xx.c 编译时可以显示编译连接的过程:
				...
				/usr/lib/gcc/i686-linux-gnu/4.8/collect2 --sysroot=/ --build-id --eh-frame-hdr -m 
						elf_i386 --hash-style=gnu --as-needed -dynamic-linker /lib/ld-linux.so.2 -z 
						relro /usr/lib/gcc/i686-linux-gnu/4.8/../../../i386-linux-gnu/crt1.o 
						/usr/lib/gcc/i686-linux-gnu/4.8/../../../i386-linux-gnu/crti.o 
						/usr/lib/gcc/i686-linux-gnu/4.8/crtbegin.o -L/usr/lib/gcc/i686-linux-gnu/4.8 
						-L/usr/lib/gcc/i686-linux-gnu/4.8/../../../i386-linux-gnu 
						-L/usr/lib/gcc/i686-linux-gnu/4.8/../../../../lib -L/lib/i386-linux-gnu 
						-L/lib/../lib -L/usr/lib/i386-linux-gnu -L/usr/lib/../lib 
						-L/usr/lib/gcc/i686-linux-gnu/4.8/../../.. /tmp/ccu4mvJ1.o 
						-lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s 
						--no-as-needed /usr/lib/gcc/i686-linux				
				...
				这里collect2就是链接脚本.  crt1.o,crti.o,crtbegin.o就是GCC提供的默认的那些启动代码(
				引导程序).  最后生成a.out可执行程序.
			f) ./a.out执行时, 又涉及到了加载器.	
		
		2) 运行时的加载器. 加载器是操作系统中的程序, 当我们去执行一个程序时(譬如./a.out, 譬如代码中用
		   exec族函数来运行)加载器负责将这个程序加载到内存中去执行这个程序.
		   
		   加载器做了很多事情, 比如说重定位的过程, 设计到应用程序的虚拟机地址和物理地址的对应问题(???).
		   
		3) 程序在编译连接时用'链接器', 运行时用'加载器'，这两个东西对程序运行原理非常重要.
		
			涉及到操作系统原理的很多东西, 先不用深究.
		
		4) argc和argv的传参如何实现.
		
			在shell环境, ./a.out -v. shell也是一个进程, 会把参数传给引导代码, 最后传递到main().

	2. 程序如何结束
	
		1) 正常终止：return、exit、_exit.
		
			main()函数中return 程序终止.
		
		2) 非正常终止：自己或他人发信号终止进程.
		
			后续课程有详细介绍.  CTRL+C时, 操作系统就会发送一个终止信号. 
		
	3. atexit() 向操作系统 '注册' '进程终止处理函数'
	
		1) 实验演示
		
		
			void func1(void)
			{
				printf("func1\n");
			}

			void func2(void)
			{
				printf("func2\n");
			}

			int main(void)
			{
				printf("hello world.\n");
				
				// 当进程被正常终止时，系统会自动调用这里注册的func1执行
				atexit(func2);
				atexit(func1);
				
				printf("my name is lilei hanmeimei\n");
				
				//return 0;				// 第一种终止 return
				//exit(0);				// 第二种终止 exit(0)
				_exit(0);				// 第三种终止 _exit(0)
			}		
			a) 第一种终止时, 先打印hello..., 再打印 my name..., 最后打印注册函数的内容.
			b) return和exit()效果一样, 都是会执行进程终止处理函数, 但是用_exit()终止进程时并不执行.
		
		2) atexit注册多个进程终止处理函数, 先注册的后执行(先进后出, 和栈一样).
		
		3) return、exit和_exit的区别：return和exit()效果一样, 都是会执行进程终止处理函数, 但是用_exit()
		   终止进程时并不执行atexit()注册的进程终止处理函数.
			
			注册函数, 起始就是把函数指针赋值给了回调函数.
			
			(????)进程终止处理函数, 在紧急情况下可以不执行??? 不用清理???
			
//=======================================================================================================
										3.4.2.进程环境
//-------------------------------------------------------------------------------------------------------
	1. 环境变量
	
		1) export命令查看环境变量
			
			a) 之前查看都是用的echo, 比如查看PATH, echo $PATH
			b) 命令行 export , 显示内容:
				...
				declare -x PAPERSIZE="letter"
				declare -x PATH="/usr/local/arm/arm-2009q3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:
				                 /usr/bin:/sbin:/bin:/usr/games:/usr/local/games"
				declare -x PWD="/root"
				...
		
		2) 进程环境表介绍. 每一个进程中都有一份所有环境变量构成的一个表格, 也就是说我们当前进程中可以
		   直接使用这些环境变量. 进程环境表其实是一个字符串数组, 用environ变量指向它.
		   
		3) 程序中通过'environ全局变量'使用环境变量.
		
		4) 我们写的程序中可以无条件直接使用系统中的环境变量, 所以一旦程序中用到了环境变量那么程序就和
		   操作系统环境有关了.
		   
		   (!!!!!) 程序编译好之后, 在这个机器上运行时对的, 但是在另一个机器上运行就不正常. 这就可能是
		   运行机器操作系统的环境变量设置不同导致的.  
		   
		5) 进程环境变量表测试:

			int main(void)
			{
				extern char **environ;		// 声明就能用
				int i = 0;
				
				while (NULL != environ[i])
				{
					printf("%s\n", environ[i]);
					i++;
				}
				
				
				return 0;
			}
			a) char **environ; 是一个全局变量.
			b) 二重指针可以指向指针数组, 所以可以 environ[i]引用. (?????!!!!! 需要加深理解)
			
		6) 应用程序如何获取指定环境变量? 使用getenv()函数.
			如果程序依赖环境变量, 需要使用该函数进行获取, 或者设置. 
			
			char *getenv(const char *name);				// 使用举例 : getenv("PATH"))
			
			int setenv(const char *name, const char *value, int overwrite);
														// 
			a) 这里的函数和uboot中的命令很相似, 因为uboot就是参考了内核来设计的.
			b) 这里改变的是当前进程的环境变量, 不是操作系统的韩静变量.

	2. 进程运行的虚拟地址空间
	
		1) 操作系统中每个进程在独立地址空间中运行. 每一个进程都认为自己是独享资源的.
		
		2) 每个进程的'逻辑地址'空间均为4GB(32位系统).
		
		3) 0-1G为OS, 1-4G为应用. 而实际的系统物理地址可能只有512M.
		
		4) 虚拟地址到物理地址空间的映射.
		
		5) 意义. 
		
			a) 进程隔离(为了安全, 比如银行支付应用和QQ应用, 就需要隔离).

			b) 提供多进程同时运行:
			
				程序运行的时候, 运行地址和链接地址需要相同. 如果没有虚拟地址到物理地址的映射, 就需要
				知道运行的物理地址, 链接地址与其相同(原来裸机就是这么做的).
				
				而实际上, 多个应用程序运行时, 根本就不知道将来会把某一个程序的运行物理地址, 所以做了
				虚拟地址映射, 在虚拟地址的层面上, 每一个应用程序都是从0虚拟地址开始的, 占用多少空间
				就是0开始的那段虚拟地址. 将来映射到什么物理地址, 是操作系统做的事情. 链接程序在将来
				物理地址上运行时也不会出错, 操作系统会做虚拟地址到物理地址的转换. 所以对于每一个应用
				程序来说, 只要把它链接到0地址开始就可以了, 这就是应用程序编译的时候不用提供链接脚本,
				默认的链接脚本就链接到0地址了(gcc xx.c).
				
	3. 总结:
			1) 虚拟地址是操作系统很重要的一个概念. linux, 安卓, win等复杂操作系统, 能够提供从虚拟地址
			   到物理地址的映射, 能够去编写应用程序, 成为高级操作系统.
			   
			2) RTOS操作系统里面使用的都是物理地址, 所以里面叫任务, 不是进程.
			
				(????) 不能够在运行的时候去更新程序, 只能静态的修改了程序重新编译后,烧写进去. 之前的
				功能机就是这种系统. 现在的智能机可以动态的安装程序,卸载程序, 就是因为有虚拟地址的操作.

//=======================================================================================================
									3.4.3.进程的正式引入
//-------------------------------------------------------------------------------------------------------
	1. 什么是进程
	
		1) 进程是动态过程而不是静态实物(比如文件).
		2) 进程就是程序的一次运行过程, 一个静态的可执行程序 a.out 的一次运行过程(./a.out去运行到结束)
		   就是一个进程.
		3) 进程控制块PCB( process control block ), 内核中专门用来管理一个进程的数据结构. 用来记录进程的
		   各种信息/管理进程. (进程ID就包含在PCB中)

	2. 进程ID
	
		1) getpid、getppid、getuid、geteuid、getgid、getegid.
			
			这些API或者库函数, 可以获取进程ID.  getpid(获取当前进程ID), getppid(获取父进程ID),
			getuid(获取当前进程的用户ID, root用户ID是0, aston用户ID是1...), getgid(获取当前进程的组ID).

			geteuid(有效用户ID) getegid(有效组ID)
			
		2) 实际用户ID和有效用户ID区别(可百度), 实际组ID和有效组ID.
		
			总结: 实际用户ID和有效用户ID区别, 实际组ID和有效组ID. 一般用不到. 不用去深究.
			
		3) man 2 getpid
		
		   #include <sys/types.h>
		   #include <unistd.h>

		   pid_t getpid(void);
		   pid_t getppid(void);		// pid_t	int类型的,或者是long类型的整数
		   
		4) 测试
	
			pid_t p1 = -1, p2 = -1;
			
			printf("hello.\n");
			p1 = getpid();
			printf("pid = %d.\n", p1);	
			p2 = getppid();
			printf("parent id = %d.\n", p2);	
			
			运行结果:
				hello.
				pid = 11999.
				parent id = 2825.
			ps 命令查看:
				  PID TTY          TIME CMD
				 2824 pts/3    00:00:00 su
				 2825 pts/3    00:00:00 bash
				12101 pts/3    00:00:00 ps			
			
			可以看到, 程序的父进程就是bash. 再次运行时, 得到的pid会变, 大于11999. 
			
	3. ps命令
	
		1) 命令行用ps命令, 可以查看进程信息:

			root@ubuntu:~/l_software/3/4.process# ps
			  PID TTY          TIME CMD
			 2824 pts/3    00:00:00 su
			 2825 pts/3    00:00:00 bash
			11762 pts/3    00:00:00 ps
			
			PID就是进程ID, TTY就是在哪个中断上边(???),
	
			-a	显示同一终端下的所有进程
			-A	显示所有进程
			c	显示进程的真实名称
			-N	反向选择
			-e	等于“-A”
			e	显示环境变量
			f	显示程序之间的关系
			-H	显示树状结构
			r	显示当前终端的进程
			T	显示当前终端的所有程序
			-au	显示较详细的资讯
			-aux	显示所有包含其他使用者的行程	
			
		2) 命令行用ps -aux命令, 可以查看所有用户的所有进程信息:
		
			USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
			root         1  0.0  0.0   4572  2632 ?        Ss   Jul19   0:06 /sbin/init
			root         2  0.0  0.0      0     0 ?        S    Jul19   0:00 [kthreadd]
			root         3  0.0  0.0      0     0 ?        S    Jul19   0:01 [ksoftirqd/0]
			root         4  0.0  0.0      0     0 ?        S    Jul19   0:00 [kworker/0:0]
			root         5  0.0  0.0      0     0 ?        S<   Jul19   0:00 [kworker/0:0H]
			root         7  0.0  0.0      0     0 ?        S    Jul19   0:06 [rcu_sched]

			aston     2352  0.0  0.1 154732 17440 ?        Sl   Jul19   0:00 /usr/lib/i386-linu
			aston     2811  0.0  0.0   6928  3240 pts/3    Ss   Jul19   0:00 bash
			root      2824  0.0  0.0   6360  1712 pts/3    S    Jul19   0:00 su
			root      2825  0.0  0.0   5788  2104 pts/3    S    Jul19   0:00 bash

			(???) TTY怎么理解?  
			PID等于0的进程没有, 因为0号进程是内核态下面的,用来统计系统空闲等等操作.  1号进程就是init
			进程, 是用户第一个进程, 开始也是内核进程, 执行了跟文件系统上的一个init程序, 变成了第一个
			用户进程. 其他的进程都是进程1生成的. PID号并不连续, 因为有的进程运行一会后就终止了.
	
	4. 多进程调度原理
	
		1) 操作系统同时运行多个进程.
		2) 宏观上的并行和微观上的串行.
		3) 实际上现代操作系统最小的调度单元是线程而不是进程.

//=======================================================================================================
									3.4.4.fork创建子进程
//-------------------------------------------------------------------------------------------------------
	1. fork创建子进程, 为什么要创建子进程

		1) 每一次程序的运行都需要一个进程.
		
		2) 多进程实现宏观上的并行.

	2. fork的内部原理
	
		1) 进程的分裂生长模式. 如果操作系统需要一个新进程来运行一个程序, 那么操作系统会用一个现有的进
		   程来复制生成一个新进程. 老进程叫父进程, 复制生成的新进程叫子进程.
		   
		   PCB进程控制块复制出来一个, 然后把其中的一些项修改(比如PID, 其中表示运行程序的参数等).
		   
		2) fork函数调用一次会返回2次, 返回值等于0的就是子进程, 而返回值大于0的就是父进程.
		
		3) 典型的使用fork的方法：使用fork后然后用if判断返回值, 并且返回值大于0时就是父进程, 等于0时就
		   是子进程.
		   
		4) fork的返回值在子进程中等于0, 在父进程中等于本次fork创建的子进程的进程ID.
		
	3. fork的演示
			
		1) man 2 fork
			
			#include <unistd.h>

			pid_t fork(void);
			   
		2) 	测试:
			int main(void)
			{
				pid_t p1 = -1;
				
				p1 = fork();		// 返回2次
				
				if (p1 == 0)
				{
					// 这里一定是子进程
					
					// 先sleep一下让父进程先运行，先死
					sleep(1);
					
					printf("子进程, pid = %d.\n", getpid());		
					printf("hello world.\n");
					printf("子进程, 父进程ID = %d.\n", getppid());
				}
				
				if (p1 > 0)
				{
					// 这里一定是父进程
					printf("父进程, pid = %d.\n", getpid());
					printf("父进程, p1 = %d.\n", p1);
				}
				
				if (p1 < 0)
				{
					// 这里一定是fork出错了
				}
				
				return 0;
			}
		总结:
				如果父进程结束, 其子进程如果调用了getppid(), 则返回init进程的ID. 
			
	4. 关于子进程
	
		1) 子进程和父进程的关系.
			fork()系统调用完成后, 子进程和父进程就是两个独立的进程. 子进程的运行不依懒于父进程.
		2) 子进程有自己独立的PCB.
			子进程的PCB是从父进程复制而来的, 之后有修改部分参数.
		3) 子进程被内核同等调度.

//=======================================================================================================
									3.4.5.父子进程对文件的操作
//-------------------------------------------------------------------------------------------------------
	1. 子进程继承父进程中打开的文件
	
		1) 上下文：父进程先open打开一个文件得到fd, 然后再fork创建子进程. 之后在父子进程中各自write向
		   fd中写入内容.
		   
		2) 测试结论是：接续写. 实际上本质原因是父子进程之间的fd对应的文件指针是彼此关联的(很像O_APPEND
		   标志后的样子).
		   
		3) 实际测试时有时候会看到只有一个, 有点像分别写. 但是实际不是, 原因是其中一个进程先结束, 
		   默认执行close(????), 另一个没有写进去.

	2. 父子进程各自独立打开同一文件实现共享
	
		1) 父进程open打开1.txt然后写入, 子进程打开1.txt然后写入. 结论是：分别写. 
			原因是父, 子进程分离后才各自打开的1.txt, 这时候这两个进程的PCB已经独立了, 文件表也独立了, 
			因此2次读写是完全独立的.
		2) open时使用O_APPEND标志看看会如何? 
			实际测试结果标明O_APPEND标志可以把父,子进程各自独立打开的fd的文件指针给关联起来, 实现接续写.
			
	3. 总结
	
		1) 父子进程间终究多了一些牵绊.
		2) 父进程在没有fork之前自己做的事情对子进程有很大影响, 但是父进程fork之后在自己的if里做的事情
		   就对子进程没有影响了. 本质原因就是因为fork内部实际上已经复制父进程的PCB生成了一个新的子进程,
		   并且fork返回时子进程已经完全和父进程脱离并且独立被OS调度执行.
		3) 子进程最终目的是要独立去运行另外的程序.

//=======================================================================================================
									3.4.6.进程的诞生和消亡
//-------------------------------------------------------------------------------------------------------
	1. 进程的诞生
		
		1) 进程0和进程1
			进程0是操作系统内核再启动过程中, 手工构建的(进程0内的结构体的元素都是内核一点一点添加的).
			进程1是进程0 在内核态调用内核中的类似fork的函数(课程说可以这么认为)创建的. 
			
		2) fork, vfork
		
			fork和vfork都是用来创建一个子进程的.
			fork()子进程拷贝父进程的数据段和代码段, 这里通过拷贝页表实现. vfork()子进程与父进程共享
			地址空间, 无需拷贝页表, 效率更高. 
			
			fork()父子进程的执行次序不确定. vfork()保证子进程先运行, 在调用 exec 或 exit 之前与父进程
			数据是共享的. 父进程在子进程调用 exec 或 exit 之后才可能被调度运行, 如果在调用这两个函数之
			前子进程依赖于父进程的进一步动作, 则会导致死锁.
			
			(课程说只要知道这两个都是创建子进程的就可以了)
		
	2. 进程的消亡
	
		1) 正常终止和异常终止.
		2) 进程在运行时需要消耗系统资源(内存(譬如malloc申请的资源)、IO(比如打开了一个串口设备)), 进程
		   终止时理应完全释放这些资源(如果进程消亡后仍然没有释放相应资源则这些资源就丢失了).
		   
		   比如进程打开了一个文件, 如果进程结束, 也没有去关闭, 操作系统会认为这个文件一直被占用着.在
		   ubuntu中, 有时候vim打开一个文件时, 系统会提示改文件只能读不能写. 这时候ls -a查看会看到swap
		   文件, 表明有进程正在打开相应的文件. 而进程可能被意外终止了, 这个swap文件没有删除. 此时,
		   只要手动删除, vim打开的文件就可以写了.
		   
		3) linux系统设计时规定：每一个进程退出时, 操作系统会自动回收这个进程涉及到的所有的资源(譬如
		   malloc申请的内容没有free时, 当前进程结束时这个内存会被释放, 譬如open打开的文件没有close的
		   在程序终止时也会被关闭). 但是操作系统只是回收了这个进程工作时消耗的内存和IO, 而并没有回收
		   这个进程本身占用的内存(8KB, 主要是task_struct和栈内存). 父进程fork时占用的, 不是子进程运行
		   时使用的, 操作系统不会回收.
		   
		4) 因为进程本身的8KB内存操作系统不能回收需要别人来辅助回收, 因此我们每个进程都需要一个帮助它
		   收尸的人, 这个人就是这个进程的父进程.

	3. 僵尸进程
	
		1) 子进程先于父进程结束. 子进程结束后父进程此时并不一定立即就能帮子进程“收尸”, 在这一段(子进程
		   已经结束且父进程尚未帮其收尸)子进程就被成为僵尸进程.
		   
		2) 子进程除task_struct和栈外其余内存空间皆已清理.
		
		3) 父进程可以使用wait或waitpid以显式回收子进程的剩余待回收内存资源并且获取子进程退出状态.
		
			父进程调用显示回收前, 子进程就是僵尸进城.
		
		4) 父进程也可以不使用wait或者waitpid回收子进程, 此时父进程结束时一样会回收子进程的剩余待回收
		   内存资源. (这样设计是为了防止父进程忘记显式调用wait/waitpid来回收子进程从而造成内存泄漏)
	
	4. 孤儿进程

		1) 父进程先于子进程结束, 子进程成为一个孤儿进程.
		2) linux系统规定：所有的孤儿进程都自动成为一个特殊进程(进程1, 也就是init进程)的子进程.
			这个子进程结束时, 又会由进程1去回收, 不会有资源的泄露.
			
		注意: 在 ubuntu中, init进程的ID不是1.

//=======================================================================================================
									3.4.7.父进程wait回收子进程
//-------------------------------------------------------------------------------------------------------
	1. wait的工作原理
	
		1) 子进程结束时, 系统向其父进程发送SIGCHILD信号.
		2) 父进程调用wait函数后阻塞.
		3) 父进程被SIGCHILD信号唤醒然后去回收僵尸子进程.
		4) 父子进程之间是异步的, SIGCHILD信号机制就是为了解决父子进程之间的异步通信问题, 让父进程可以
		   及时的去回收僵尸子进程.
		5) 若父进程没有任何子进程则wait返回错误.
		
	2. man查阅wait系统调用API

       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *status);

		1) 参数为int *status, 没有加const, 说明是一个输出型参数. 参数时int类型的.
		
		2) 
		
	3. wait实战编程
	
		1) wait的参数status. status用来返回子进程结束时的状态, 父进程通过wait得到status后就可以知道子
		   进程的一些结束状态信息.

		2) wait的返回值pid_t, 这个返回值就是本次wait回收的子进程的PID. 当前进程有可能有多个子进程, 
		   wait函数阻塞直到其中一个子进程结束wait就会返回, wait的返回值就可以用来判断到底是哪一个子
		   进程本次被回收了.

		   总结: 对wait做个总结：wait主要是用来回收子进程资源, 回收同时还可以得知被回收子进程的pid和
		         其退出状态.

		3) fork后wait回收实例.
			
			int main(void)
			{
				pid_t pid = -1;
				pid_t ret = -1;
				int status = -1;
				
				pid = fork();
				if (pid > 0)
				{
					// 父进程
					printf("parent.\n");
					ret = wait(&status);										// 父进程被阻塞
					
					printf("子进程已经被回收，子进程pid = %d.\n", ret);
					printf("子进程是否正常退出：%d\n", WIFEXITED(status));		// 
					printf("子进程是否非正常退出：%d\n", WIFSIGNALED(status));	//
					printf("正常终止的终止值是：%d.\n", WEXITSTATUS(status));	//
				}
				else if (pid == 0)
				{
					// 子进程
					printf("child pid = %d.\n", getpid());
					return 51;													// 进程返回值. 8位
					//exit(0);
				}
				else
				{
					perror("fork");
					return -1;
				}
				return 0;
			}
		
		4) WIFEXITED、WIFSIGNALED、WEXITSTATUS这几个宏用来获取子进程的退出状态.

			WIFEXITED宏用来判断子进程是否正常终止(return、exit、_exit退出).
			WIFSIGNALED宏用来判断子进程是否非正常终止(被信号所终止).
			WEXITSTATUS宏用来得到正常终止情况下的进程返回值(8位)的.

		总结: 进程正常退出: 	return、exit、_exit退出.
			  进程非正常退出:	被信号所终止等.
			  
//=======================================================================================================
									3.4.8.waitpid介绍
//-------------------------------------------------------------------------------------------------------
	1. waitpid和wait差别
	
		1) 基本功能一样, 都是用来回收子进程.
		2) waitpid可以回收指定PID的子进程.
		3) waitpid可以阻塞式或非阻塞式两种工作模式.
		
	2. waitpid原型介绍
	
        pid_t waitpid(pid_t pid, int *status, int options);
	   
		1) 参数
			pid_t pid, 回收的子进程的ID;  -1 -> 回收任意一个子进程.
			int *status, 
			int options, 可以实现阻塞,非阻塞. WNOHANG -> 非阻塞. 0 -> 阻塞
			
		2) 返回值
			被回收的子进程的ID.
		
	3. 代码实例
	
		1) 使用waitpid实现wait的效果
		
		   ret = waitpid(-1, &status, 0);  		-1表示不等待某个特定PID的子进程而是回收任意一个子进程, 
			                                     0表示用默认的方式(阻塞式)来进行等待, 返回值ret是本次
												 回收的子进程的PID.
												 
		2) ret = waitpid(pid, &status, 0);		等待回收PID为pid的这个子进程, 如果当前进程并没有一个
												ID号为pid的子进程, 则返回值为-1; 如果成功回收了pid这个
												子进程则返回值为回收的进程的PID.
												
		3) ret = waitpid(pid, &status, WNOHANG); 这种表示父进程要非阻塞式的回收子进程. 此时如果父进程
		                                         执行waitpid时子进程已经先结束等待回收, 则waitpid直接
												 回收成功, 返回值是回收的子进程的PID; 如果父进程waitpid
												 时子进程尚未结束则父进程立刻返回(非阻塞), 但是返回值
												 为0(表示回收不成功). 
												 
		总结: waitpid(pid, &status, 0), 如果当前进程没有一个ID号为pid的子进程, 则返回-1. 如果没有回收
		      成功(子进程未结束), 则返回0. 

			   waitpid(): on success, returns the process ID of the child whose  state
			   has changed; if WNOHANG was specified and one or more child(ren) speci‐
			   fied by pid exist, but have not yet changed state, then 0 is  returned.
			   On error, -1 is returned.


	4. 竟态初步引入
	
		1) 竟态全称是：竞争状态, 多进程环境下, 多个进程同时抢占系统资源(内存、CPU、文件IO(普通或设备)).
		2) 竞争状态对OS来说是很危险的, 此时OS如果没处理好就会造成结果不确定.
		3) 写程序当然不希望程序运行的结果不确定, 所以我们写程序时要尽量消灭竞争状态. 操作系统给我们
		   提供了一系列的消灭竟态的机制, 我们需要做的是在合适的地方使用合适的方法来消灭竟态.

		比如: 父进程fork之后, 回收子程序时, 需要在父进程fork后, 加一个sleep(1), 才能保证子程序肯定先
			  结束. 如果不加, 则运行结果不确定(父进程回收子进程时, 子进程可能还没有结束). 这就是一种
			  不确定的竞争状态. (如何消除, 后续课程会讲)
			  
//=======================================================================================================
									3.4.9.exec族函数及实战1
//-------------------------------------------------------------------------------------------------------
	1. 为什么需要exec函数
	
		1) fork子进程是为了执行新程序(fork创建了子进程后, 子进程和父进程同时被OS调度执行, 因此子进程
		   可以单独的执行一个程序, 这个程序宏观上将会和父进程程序同时进行).
		   
		2) 可以直接在子进程的if中写入新程序的代码. 这样可以, 但是不够灵活, 因为我们只能把子进程程序的
		   源代码贴过来执行(必须知道源代码, 而且源代码太长了也不好控制), 譬如说我们希望子进程来执行
		   ls -la 命令就不行了(没有源代码, 只有编译好的可执行程序).
		   
		3) 使用exec族运行新的可执行程序(exec族函数可以直接把一个编译好的可执行程序直接加载运行).
		
		4) 我们有了exec族函数后, 我们典型的父子进程程序是这样的：子进程需要运行的程序被单独编写、单独
		   编译连接成一个可执行程序(比如叫hello), (项目是一个多进程项目)主程序为父进程, fork创建了子进
		   程后在子进程中exec来执行hello, 达到父子进程分别做不同程序同时(宏观上)运行的效果.
		   
	2. exec族的6个函数介绍
	
		int execl(const char *path, const char *arg, ...);			// ... 变参. 以NULL结尾
		int execlp(const char *file, const char *arg, ...);
		int execle(const char *path, const char *arg, .., char * const envp[]);
      
		int execv(const char *path, char *const argv[]);
		int execvp(const char *file, char *const argv[]);
		int execvpe(const char *file, char *const argv[], char *const envp[]);
	   
		1) execl和execv 	
			这两个函数是最基本的exec, 都可以用来执行一个程序, 区别是传参的格式不同. 
			execl是把参数列表(本质上是多个字符串, 必须以NULL结尾)依次排列而成(l其实就是list的缩写),
			execv是把参数列表事先放入一个字符串数组中, 再把这个字符串数组传给execv函数.
			
		2) execlp和execvp	
			这两个函数在上面2个基础上加了p, 较上面2个来说, 区别是：上面2个执行程序时必须指定可执行程序
			的全路径(如果exec没有找到path这个文件则直接报错), 而加了p的传递的可以是file(也可以是path,
			只不过兼容了file. 加了p的这两个函数会首先去找file, 如果找到则直接执行, 如果没找到则会去环
			境变量PATH所指定的目录下去找, 如果找到则执行如果没找到则报错).
			
			(?????) 如果只写file, 在哪个目录下去找?????
			
		3) execle和execvpe	
			这两个函数较基本exec来说加了e, 函数的参数列表中也多了一个字符串数组envp形参, e就是
			environment环境变量的意思, 和基本版本的exec的区别就是：执行可执行程序时会多传一个环境变量
			的字符串数组给待执行的程序.
			
			(?????) 需要传递环境变量的情况不多. 什么情况下用? (朱说自己也没有用过)
					普通程序执行, 是从父进程继承的系统的环境变量. 
			
	3. exec实战1
	
		1) 使用execl运行ls -l -a
		   先确定ls命令的路径, which ls	
		   显示: /bin/ls
		   
			int main(void)
			{
				pid_t pid = -1;
				pid_t ret = -1;
				int status = -1;
				
				pid = fork();
				if (pid > 0)
				{
					// 父进程
					printf("parent, 子进程id = %d.\n", pid);
				}
				else if (pid == 0)
				{
					// 子进程
					execl("/bin/ls", "ls", "-l", "-a", NULL);		// ls -l -a
					return 0;
				}
				else
				{
					perror("fork");
					return -1;
				}
				return 0;
			}
			
			总结:	
			
				a) execl("/bin/ls", "ls", "-l", "-a", NULL), "ls"是作为argv[0]传递进来的, 是程序名,
			       如果改为"ssss" 测试也正确. 但是不可以省略. 省略后, 其后的参数"-l" 不起作用.
				b) execl("/bin/ls", "ls", "-al", NULL), 显示也正常.
				
		2) 使用execv运行ls

			char * const arg[] = {"ls", "-l", "-a", NULL};			// 注意最后的NULL
			
			execv("/bin/ls", arg);

		3) 使用execl运行自己写的程序
			
			a) 创建一个hello.c, 输入如下内容
			
				int main(int argc, char **argv)
				{
					int i = 0;
					
					printf("argc = %d.\n", argc);
					
					while (NULL != argv[i])
					{
						printf("argv[%d] = %s\n", i, argv[i]);
						i++;
					}
					
					return 0;
				}
				
				编译: gcc hello.c -o hello
				
			b) 父进程中执行hello程序
			
				α) execl("hello", "hello", NULL);	// 第二个"hello" 是argv[0], 必须有, 名称随意.
				
				β) char * const arg[] = {"hello", NULL};
				   execv("hello", arg);

	总结:
			这些函数用在多进程的程序设计, 常用在框架性的设计,比如GUI等庞大程序. 平时写程序用的很少.
//=======================================================================================================
									3.4.10.exec族函数及实战2
//-------------------------------------------------------------------------------------------------------
	1. execlp和execvp
	
		1) 加p和不加p的区别是：不加p时需要全部路径+文件名, 如果找不到就报错了. 加了p之后会多帮我们到
		   PATH所指定的路径下去找一下.
		
			execlp("ls", "ls", "-l", "-a", NULL);	
			
			注意: 子进程中执行了execl或者execlp后, 就去执行别的程序了, 这一句后续的代码不会执行了(!!!!!)
			
	2. execle和execvpe
	
		1) main函数的原型其实不止是int main(int argc, char **argv), 而可以是:
		
		   int main(int argc, char **argv, char **env)	
		   
		   第三个参数是一个字符串数组, 内容是环境变量.
		   
		2) 如果用户在执行这个程序时没有传递第三个参数, 则程序会自动从父进程继承一份环境变量(默认的,
		   最早来源于OS中的环境变量); 如果我们exec的时候使用execlp或者execvpe去给传一个envp数组, 则
		   程序中的实际环境变量是我们传递的这一份(取代了默认的从父进程继承来的那一份).

			char * const envp[] = {"AA=aaaa", "XX=abcd", NULL};
			execle("hello", "hello", NULL, envp);						// 最后放环境变量指针. 
																		// NULL是之前的部分.
			输出:
				argc = 1.
				argv[0] = hello
				env[0] = AA=aaaa
				env[1] = XX=abcd

		注意:
				1) 命令行中, 输入 export 命令, 可以打印环境变量.
				
				2) 传递环境参数:
				
					int main(int argc, char **argv, char **env)
					{
						int i = 0;
						
						printf("argc = %d.\n", argc);
						
						while (NULL != argv[i])
						{
							printf("argv[%d] = %s\n", i, argv[i]);
							i++;
						}
						
						i = 0;
						while (NULL != env[i])
						{
							printf("env[%d] = %s\n", i, env[i]);
							i++;
						}
						return 0;
					}
					
					a) (!!!!!!) 编译之后, 在命令行运行./hello 打印结果:
						
						argc = 1.
						argv[0] = ./hello
						env[0] = LC_PAPER=en_US.UTF-8
						env[1] = XDG_VTNR=7
						...
						
					b) (!!!!!!) 编译之后, 在命令行运行./hello aaa bbb 打印结果:
					
						argc = 3.
						argv[0] = ./hello
						argv[1] = aaa
						argv[2] = bbb
						env[0] = LC_PAPER=en_US.UTF-8
						env[1] = XDG_VTNR=7
						...
					(????) 运行main程序时, 默认传递了环境变量的指针?????	

//=======================================================================================================
									3.4.11.进程状态和system函数
//-------------------------------------------------------------------------------------------------------
	1. 进程的5种状态
	
		1) 就绪态. 这个进程当前所有运行条件就绪, 只要得到了CPU时间就能直接运行.
		2) 运行态. 就绪态时得到了CPU就进入运行态开始运行.
		3) 僵尸态. 进程已经结束但是父进程还没来得及回收.
		4) 等待态(浅度睡眠&深度睡眠). 进程在等待某种条件, 条件成熟后可进入就绪态. 等待态下就算你给他
		   CPU调度进程也无法执行. 浅度睡眠等待时进程可以被(信号)唤醒, 而深度睡眠等待时不能被唤醒只能
		   等待的条件到了才能结束睡眠状态.
		5) 暂停态. 暂停并不是进程的终止, 只是被人(信号)暂停了, 还可以恢复的.
		
	2. 进程各种状态之间的转换图
	
		1) fork和exec之后, 进程默认处于就绪态.
		2) 深度睡眠得到资源, 进入就绪态; 浅度睡眠得到资源或者收到信号(wake_up),进入就绪态.
		
		总结: 为什么设计这么多状态: 为了充分利用系统的资源.
		
	3. system函数简介
	
		1) system函数 = fork + exec.
		
		2) 原子操作. 原子操作意思就是整个操作一旦开始就会不被打断的执行完. 原子操作的好处就是不会被人
		   打断(不会引来竞争状态), 坏处是自己单独连续占用CPU时间太长影响系统整体实时性, 因此应该尽量
		   避免不必要的原子操作, 就算不得不原子操作也应该尽量原子操作的时间缩短.
		   
		   system函数就是原子操作.
		   
		3) 函数原型:
			int system(const char *command);
			
		4) 原理:
		
			使用fork创建一个子进程.
			子进程使用 execl 执行 command 中指定的 shell 命令.
			system函数在子进程命令执行完成后返回.
			在命令执行过程中, SIGCHLD 将被阻塞, SIGINT 和 SIGQUIT 将被忽略.
			
			由上面几点我们能够得到：

				system是一个阻塞函数, 使用system需等待命令执行结束后才会继续跑接下去的代码.
				SIGCHLD 信号将被阻塞.
				
		5) 使用举例:
		
			 system("ls -l");

//=======================================================================================================
									3.4.12.进程关系
//-------------------------------------------------------------------------------------------------------
	1. 进程和进程之间的关系
	
		1) 无关系.
		
			两个进程有自己独立的地址空间, 进程A不能去访问进程B.
			
		2) 父子进程关系.
		
			这种进程关系还是挺紧密的, 比如父进程打开了一个文件,得到了文件描述符. 创建子进程后, 这个文件
			描述符会继承给子进程. 另外别的一些东西也会继承给子进程(当然只限于fork之前的东西); 比如父进程
			可以调用wait回收子进程; 比如子进程中可以getppid, 获取父进程的ID.
			
		3) 进程组(group)
		
			由若干进程构成一个进程组. 这么做是希望这些进程之间的关系, 更近一些, 为了方便管理.
			
			(?????) 参考其他的书籍进一步了解. 实际用处不大.
		
		4) 会话(session)
		
			会话就是进程组的组.
			(?????) 参考其他的书籍进一步了解. 实际用处不大. 

//=======================================================================================================
								3.4.13.守护进程的引入
//-------------------------------------------------------------------------------------------------------
	1. 进程查看命令 ps
	
		1) ps -ajx	偏向显示各种有关的ID号.
		
			 PPID   PID  PGID   SID TTY      TPGID STAT   UID   TIME COMMAND
				0     1     1     1 ?           -1 Ss       0   0:04 /sbin/init
				0     2     0     0 ?           -1 S        0   0:00 [kthreadd]
				2     3     0     0 ?           -1 S        0   0:03 [ksoftirqd/0]
			...
			 2646  2666  2666  2666 pts/0     3832 Ss    1000   0:00 bash
				1  2830  2830  2830 ?           -1 Ss       0   0:00 /usr/sbin/cupsd -f
			 2830  2833  2833  2830 ?           -1 S        7   0:00 /usr/lib/cups/notifier/dbus 
			 2666  2876  2876  2666 pts/0     3832 S        0   0:00 su
			 2876  2877  2877  2666 pts/0     3832 S        0   0:00 bash
			... 			
			
			(????) 这里的TTY是说在哪一个终端是上. pts/0就是ps命令显示的那几个对应的进程.
			PGID, SID : 进程组ID, 会话ID.
		
		2) ps -aux	偏向显示进程各种占用资源.
		
			USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
			root         1  0.0  0.0   4556  2628 ?        Ss   09:34   0:04 /sbin/init
			root         2  0.0  0.0      0     0 ?        S    09:34   0:00 [kthreadd]
			root         3  0.0  0.0      0     0 ?        S    09:34   0:03 [ksoftirqd/0]
			root         5  0.0  0.0      0     0 ?        S<   09:34   0:00 [kworker/0:0H]
		
		3) ps
			
			  PID TTY          TIME CMD
			 2876 pts/0    00:00:00 su
			 2877 pts/0    00:00:00 bash
			 3367 pts/0    00:00:00 su
			 3398 pts/0    00:00:00 su
			 3399 pts/0    00:00:00 bash
			 3831 pts/0    00:00:00 ps	
			
			(?????) 只显示当前终端下的进程. pts/0就是当前的终端.
			
			有些进程的TTY是?, 这个进程不属于任何控制台.
			 
	2. 向进程发送信号指令kill
	
		1) kill -信号编号 进程ID.
			
			向一个进程发送一个信号
			
		2) kill -9 xxx.
		
			将向xxx这个进程发送9号信号, 也就是要结束这个进程.
			
			注意: (????)之前课程讲到过: 如果一个父进程fork一个子进程, 然后子进程中有一个while(1)死循环,
				  如果父进程先结束, 怎么子进程就移植运行, 无法CTRL+C结束. 这时候有两种方法结束子进程:
				  a) 关闭终端(???? 原因是什么?)
				  b) ps查看PID, 通过kill -9 pid 结束进程.
			
	3. 何谓守护进程
	
		1) daemon, 表示守护进程, 简称为d(进程名后面带d的基本就是守护进程). 
		
			daemon还有后台运行的意思, 守护进程一般都是后台运行的.
		
		2) 长期运行(一般是开机运行直到关机时关闭).
		
			(!!!!!) ls 命令不是守护进程, 因为执行完输出后就结束了. 如果一个进程是while死循环, 也不是
			守护进程, 因为之前讲过, 结束终端也能结束这个进程.
		
		3) 与控制台脱离(普通进程都和运行该进程的控制台相绑定, 表现为如果终端被强制关闭了则这个终端中
		   运行的所有进程都被会关闭, 背后的问题还在于会话).
		   
		   比如man命令, 可以按下q退出这个进程, 也可以关闭终端结束. 
		   一个终端下运行的所有进程, 同属于一个会话. 会话的中断被关闭, 所有进程也会结束.
		   守护进程脱离了控制台. ps -aux 时, 有些进程的TTY是? 这个进程不属于任何控制台, 是守护进程(?)
		   
		4) 服务器(Server), 服务器程序就是一个一直在运行的程序, 可以给我们提供某种服务(譬如nfs服务器给
		   我们提供nfs通信方式), 当我们程序需要这种服务时我们可以调用服务器程序(和服务器程序通信以得到
		   服务器程序的帮助)来进程这种服务操作. 服务器程序一般都实现为守护进程.
		   
	4. 常见守护进程
	
		1) syslogd, 系统日志守护进程, 提供syslog功能.
		
		2) cron, cron进程用来实现操作系统的时间管理, linux中实现定时执行程序的功能就要用到cron.
			
			比如: 编程实现一个闹钟软件, 实现一个定期垃圾清理工作的软件. 
		
		总结: 查看某个进程的PID:

				ps -aux | grep "syslogd"

//=======================================================================================================
								3.4.14.编写简单守护进程
//-------------------------------------------------------------------------------------------------------
	1. 任何一个进程都可以将自己实现成守护进程
	
		1) 任何进程, 如果想要成为一个守护进程, 都可以. 主要是看需不需要成为守护进程.
		2) 需要实现成服务器这种东西(长期运行), 就要实现为守护进程.

	2. 如何成为一个守护进程
	
		可以写一个函数(create_daemon), 这个函数一经被调用, 就可以把调用它的进程, 编程守护进程.
		
	3. create_daemon函数的要素(具备了一下的要素, 就可以把一个进程编程守护进程)
	
		1) 子进程等待父进程退出.
		
		2) 子进程使用setsid创建新的会话期session，目的就是让当前进程脱离控制台.
		
			本课程没有详细讲控制台和会话的关系, 可以参考其他书籍. 其实不必懂, 记住这些就可以了.
		
		3) 调用chdir将当前工作目录设置为/ .
		
			进程如果不是根目录, 可能会依赖于某些文件系统. 这样一直运行的守护进程就依赖这个文件系统(
			与守护进程的目的不符合).
		
		4) umask设置为0以取消任何文件权限屏蔽.
		
		5) 关闭所有文件描述符.
		
			create_daemon()函数可能在任何地方调用, 如果之前打开了文件, 在变成守护进程前, 关闭之前打开
			的文件. 
			先要获取当前系统中所允许打开的最大文件描述符数目(sysconf(_SC_OPEN_MAX)), 在for循环中关闭.
		
		6) 将0、1、2定位到/dev/null.
		
			上一步关闭了所有的文件(标准输入,输出,错误(0,1,2)也关闭了).
			这一步只需要打开三次/dev/null(这是一个字符型的设备文件). 前三次打开文件返回的文件描述符
			就是0,1,2, 分别对应标准输入,输出,错误.
			
			(?????)这里的意思是, 不需要标准输入,输出,错误.
			
	4. 代码:
		
		int main(void)
		{
			create_daemon();
			
			while (1)
			{
				printf("I am running.\n");
				sleep(1);
			}
			return 0;
		}

		// 函数作用就是把调用该函数的进程变成一个守护进程
		void create_daemon(void)
		{
			pid_t pid = 0;
			
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(-1);
			}
			if (pid > 0)
			{
				exit(0);		// 父进程直接退出
			}
			
			// 执行到这里就是子进程
			
			// setsid将当前进程设置为一个新的会话期session，目的就是让当前进程
			// 脱离控制台。
			pid = setsid();
			if (pid < 0)
			{
				perror("setsid");
				exit(-1);
			}
			
			// 将当前进程工作目录设置为根目录
			chdir("/");
			
			// umask设置为0确保将来进程有最大的文件操作权限
			umask(0);
			
			// 关闭所有文件描述符
			// 先要获取当前系统中所允许打开的最大文件描述符数目
			int cnt = sysconf(_SC_OPEN_MAX);
			int i = 0;
			for (i=0; i<cnt; i++)
			{
				close(i);
			}
			
			open("/dev/null", O_RDWR);
			open("/dev/null", O_RDWR);
			open("/dev/null", O_RDWR);
		}
		
		测试:
				1)  运行./a.out , ps -ajx查看:
				
					 2019  3884  3884  3884 ?           -1 Ss       0   0:00 ./a.out
					 3864  3885  3885  2666 pts/0     3885 R+       0   0:00 ps -ajx
					 
				2) 可以再次运行./a.out, ps -ajx查看:
				
					 2019  3884  3884  3884 ?           -1 Ss       0   0:00 ./a.out
					 2019  3887  3887  3887 ?           -1 Ss       0   0:00 ./a.out
					 3864  3888  3888  2666 pts/0     3888 R+       0   0:00 ps -ajx	

				3) 这时候可以看到, 中断上并没有打印while中的printf内容, 因为标准输出被定为到了
				   /dev/null上.
				   
				4) 只能用 kill -9 3884结束守护进程. 因为没有和任何的控制台绑定, 不能通过关闭开控制台
				   关闭.
				   
				   测试: 
					在一个控制台中, ./a.out执行, 然后关闭这个控制台. 然后再打开一个, ps -ajx, 可以发现
					仍然有a.out进程.
			
		(?????) main()中, 调用了create_daemon(), create_daemon()调用了fork, 那么fork后, main函数的内容
		        也是分别存在父进程和子进程中???. create_daemon()内容也是分别存在父进程和子进程中???

//=======================================================================================================
								3.4.15.使用syslog来记录调试信息
//-------------------------------------------------------------------------------------------------------
	1. 使用syslog来记录调试信息 
		
		上一节提到过, 守护进程与控制台脱离了关系, 不能通过控制台打印调试信息. 那怎么调试守护进程呢,
		可以使用openlog、syslog、closelog三个函数.
		
	2. openlog、syslog、closelog函数.

       #include <syslog.h>

       void openlog(const char *ident, int option, int facility);
       void syslog(int priority, const char *format, ...);
       void closelog(void);

		1) const char *ident: 识别的字符串, 一般设置为当前应用程序的名字. 好多应用程序都向日志文件输出
			         信息. 
		   int option: 选项.  
					LOG_CONS:  Write  directly  to system console if there is an error while sending to
							   system logger.
					LOG_PID    Include PID with each message. 光有const char *ident还不足以定为哪一个
						       进程, 有可能好几个进程名字一样.
							   
		   int facility: 表示这条log信息是与什么相关的.
					 LOG_AUTH       security/authorization messages
					 LOG_AUTHPRIV   security/authorization messages (private)
					 LOG_CRON       clock daemon (cron and at)
				     LOG_FTP        ftp daemon
					 LOG_USER (default) generic user-level messages		// 最常用.
					 
		2) int priority
			This determines the importance of the message.  The levels are, in order of decreasing  
			impor‐tance:

			   LOG_EMERG      system is unusable
			   LOG_ALERT      action must be taken immediately
			   LOG_CRIT       critical conditions
			   LOG_ERR        error conditions
			   LOG_WARNING    warning conditions
			   LOG_NOTICE     normal, but significant, condition
			   LOG_INFO       informational message
			   LOG_DEBUG      debug-level message
			const char *format, ...
				可变参数.
				
	3. 编程实战
	
		1) 一般log信息都在操作系统的/var/log/messages这个文件中存储着, 但是ubuntu中是在
		   /var/log/syslog文件中的.
		
		2) .c文件内容:
		
			int main(void)
			{
				printf("my pid = %d.\n", getpid());
				
				openlog("b.out", LOG_PID | LOG_CONS, LOG_USER);
				
				syslog(LOG_INFO, "this is my log info.%d", 23);
				syslog(LOG_INFO, "this is another log info.");
				syslog(LOG_INFO, "this is 3th log info.");
				
				closelog();
			}
		3) /var/log/syslog 日志文件内容
			
			Jul 24 23:17:01 ubuntu CRON[3856]: (root) CMD (   cd / && run-parts --report 
																			/etc/cron.hourly)
			Jul 25 08:10:47 ubuntu b.out[3930]: this is my log info.23
			Jul 25 08:10:47 ubuntu b.out[3930]: this is another log info.
			Jul 25 08:10:47 ubuntu b.out[3930]: this is 3th log info.
			
		总结: 	
				1) 关闭终端, 再次打开一个终端, cat /var/log/syslog查看, 上述信息还有.
				2) 普通的进程也可以调用这几个函数, 完成日志文件的输出. 是不是守护进程与此无关.

	4. syslog的工作原理
	
		1) 操作系统中有一个守护进程syslogd(开机运行, 关机时才结束), 这个守护进程syslogd负责进行日志
		   文件的写入和维护.
		2) syslogd是独立于我们任意一个进程而运行的. 我们当前进程和syslogd进程本来是没有任何关系的, 
		   但是我们当前进程可以通过调用openlog打开一个和syslogd相连接的通道, 然后通过syslog向syslogd
		   发消息, 然后由syslogd来将其写入到日志文件系统中.
		3) syslogd其实就是一个日志文件系统的服务器进程, 提供日志服务. 任何需要写日志的进程都可以通过
		   openlog/syslog/closelog这三个函数来利用syslogd提供的日志服务. 这就是操作系统的服务式的设计.

//=======================================================================================================
								3.4.16.让程序不能被多次运行
//-------------------------------------------------------------------------------------------------------
	1. 问题
	
		1) 因为守护进程是长时间运行而不退出, 因此./a.out执行一次就有一个进程, 执行多次就有多个进程.
		2) 这样并不是我们想要的. 我们守护进程一般都是服务器, 服务器程序只要运行一个就够了, 多次同时
		   运行并没有意义甚至会带来错误.
		3) 因此我们希望我们的程序具有一个'单例运行'的功能. 意思就是说当我们./a.out去运行程序时, 如果
		   当前还没有这个程序的进程运行则运行之, 如果之前已经有一个这个程序的进程在运行则本次运行直接
		   退出(提示程序已经在运行).
		   
	2. 实现方法：
	
		1) 最常用的一种方法就是：用一个文件的存在与否来做标志. 具体做法是程序在执行之初去判断一个特定
		   的文件是否存在, 若存在则标明进程已经在运行, 若不存在则标明进程没有在运行. 然后运行程序时去
		   创建这个文件. 当程序结束的时候去删除这个文件即可.
		2) 这个特定文件要古怪一点, 确保不会凑巧真的在电脑中存在的.

	3. 程序实现:
	
		#define FILE	"/var/aston_test_single"
		void delete_file(void);

		int main(void)
		{
			// 程序执行之初，先去判断文件是否存在
			int fd = -1;
			fd = open(FILE, O_RDWR | O_TRUNC | O_CREAT | O_EXCL, 0664);
			if (fd < 0)
			{
				if (errno == EEXIST)				// 文件存在
				{
					printf("进程已经存在，并不要重复执行\n");
					return -1;
				}
			}
			
			atexit(delete_file);					// 注册进程清理函数
			
			int i = 0;
			for (i=0; i<10; i++)
			{
				printf("I am running...%d\n", i);
				sleep(1);
			}
			return 0;
		}

		void delete_file(void)						// 进程结束时执行
		{
			remove(FILE);							// 删除文件		man 3		
		}
	
		1) ./a.out 运行程序后, 控制台输出10S的数据. 此段时间内, 控制台被该进程占用: 这时候命令行输入
			ls 命令, 不起作用.
			
		2) (!!!!!!!) 当遇到一个终端被占用的情况时, 可以打开另外一个终端. (右击终端图标再次打开一个)
			
			一个终端执行时, 另一个终端ls查看是否有创建的文件, 执行完毕后再ls查看文件是否已经删除.
			
		3) 两个控制台分别运行./a.out. 一个在执行时, 另一个无法执行.

//=======================================================================================================
								3.4.17.linux的进程间通信概述
//-------------------------------------------------------------------------------------------------------
	1. 为什么需要进程间通信

		1) 进程间通信(IPC)指的是2个任意进程之间的通信. (父进程与子进程间, 进程组内进程间, 会话内进程间,
			                                            无关系的两个进程间)
														
		2) 同一个进程在一个地址空间中, 所以同一个进程的不同模块(不同函数、不同文件)之间都是很简单的(很
		   多时候都是全局变量、也可以通过函数形参实参传递).
		   
		3) 2个不同的进程处于不同的地址空间, 因此要互相通信很难.
		
			不同地址空间的进程, 通信很难, 因为操作系统设计的时候考虑了安全性设计导致的. 进程不知道其他
			进程的存在. 好处是安全, 但在通信上带来了不便.

	2. 什么样的程序设计需要进程间通信
	
		1) 99%的程序是不需要考虑进程间通信的. 因为大部分程序都是单进程的(可以多线程, 目前多是用多线程
		                                                                 实现).
		
		2) 复杂、大型的程序, 因为设计的需要就必须被设计成多进程程序(我们整个程序就设计成多个进程同时
		   工作来完成的模式), 常见的如GUI、服务器.
		   
		3) 结论：IPC技术在一般中小型程序中用不到, 在大型程序中才会用到.

	3. linux内核提供多种进程间通信机制
	
		1) 无名管道和有名管道. 
		
			可以提供父子进程间的通信.
		
		2) SystemV IPC：信号量、消息队列、共享内存.
		
			SystemV和BSD是Unix的两个分支. 这些通信是SystemV的通信机制. LINUX也拿来用了.
		
		3) Socket域套接字.
		
			不局限与一台电脑的两个进程间通信, 还可以在两台电脑间两个进程通信. 比如浏览器就是这样的一个
			进程, 与服务器端的进程通信.
			
			Socket域套接字是BSD上设计的通信机制. LINUX也拿来用了.
		
		4) 信号.
			
			操作系统和进程之间可以发送信号; 进程和进程之间也可以发送信号.
		
		总结: LINUX 照单全收了好个系统的进程间通信方式, 每种都是一套不同的实现方式. 给学习带来了困难.
		
	4. 为什么不详细讲IPC
	
		1) 日常使用少, 只有大型程序才能用上.
		2) 更为复杂, 属于linux应用编程中难度最大的部分.
		3) 细节多.
		4) 面试较少涉及, 对找工作帮助不大.
		5) 建议后续深入学习时再来实际写代码详细探讨.

//=======================================================================================================
								3.4.18.linux的IPC机制-管道
//-------------------------------------------------------------------------------------------------------
	1. 管道(无名管道) (一般说的管道, 就是这种)
	
		1) 管道通信的原理：内核维护的一块内存, 有读端和写端(管道是单向通信的).
		
			进程可以和内核通信, 不可以和其他进程通信. 管道就是内核提供一个公共的区域.
		
		2) 管道通信的方法：父进程创建管理后fork子进程, 子进程继承父进程的管道fd.
		
			int pipe(int pipefd[2]);
			父进程先创建管道, 返回两个文件描述符(分别是读文件,写文件).
			a) (!!!!!?????) 课程说道:  int pipefd[2] 说明是输出型参数.
			b) (??????) int pipefd[2] 这个参数起始还是传递了一个int型的指针变量???
			
		3) 管道通信的限制：只能在父子进程间通信、半双工.
		
			可以改变通信方向(从右到左或者从左到右), 但不能同一时刻两个方向. 双向通信时, 一般是建立
			两个管道, 每个管道单向.
			
			因为是子进程继承了父进程的文件描述符, 所以才能使用管道通信.
		
		4) 管道通信的函数：pipe(创建)、write、read、close.

	2. 有名管道(fifo)
	    
		为了解决无名管道只能父子进程通信的限制.
		
		1) 有名管道的原理：实质也是内核维护的一块内存, 表现形式为一个有名字的文件.

		2) 有名管道的使用方法：固定一个文件名, 2个进程分别使用mkfifo创建fifo文件, 然后分别open打开获
		   取到fd, 然后一个读一个写.
		   
		   通过mkfifo, 把文件名和进程关联起来.
		
		3) 有名管道通信限制：半双工(注意不限父子进程, 任意2个进程都可).
		
		4) 有名管道通信的函数：mkfifo、open、write、read、close.

//=======================================================================================================
									3.4.19.SystemV IPC介绍
//-------------------------------------------------------------------------------------------------------
	1. SystemV IPC的基本特点
	
		1) 系统通过一些专用API来提供SystemV IPC功能.
		
			管道通信, 还是使用的UNIX的文件操作的API来实现的. 而SystemV IPC 引用了一些新的API.
		
		2) 三种通信方式：信号量、消息队列、共享内存.
		
		3) 其实质也是内核提供的公共内存.
		
	2. 消息队列
	
		1) 本质上是一个队列, 队列可以理解为(内核维护的一个)FIFO.
		2) 工作时A和B两个进程进行通信, A向队列中放入消息, B从队列中读出消息.

	3. 信号量
	
		1) 实质就是个计数器(其实就是一个可以用来计数的变量, 可以理解为int a).
		2) 通过计数值来提供互斥或同步.
	
	4. 共享内存
	
		1) 大片内存直接映射
		
			比如几个进程, 一个负责录像, 一个负责解码, 一个负责从网络发出去. 数据量大就需要共享内存.
		
		2) 类似于LCD显示时的显存用法.
		
		总结: A进程放进去时, B进程是否已经读取了上一次的数据. 因此实际使用共享内存时, 需要用信号量
		      配合实现.

	5. 剩余的2类IPC
	
		1) 信号
		2) Unix域套接字  socket

//=======================================================================================================










