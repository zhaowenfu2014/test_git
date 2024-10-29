/*
//=======================================================================================================
									3.5.linux中的信号
//=======================================================================================================
3.5.1.什么是信号
3.5.2.常见信号介绍
3.5.3.进程对信号的处理
3.5.4.alarm和pause函数
//=======================================================================================================
3.5.1.什么是信号
	本节介绍什么是信号, 以及信号由谁发送、由谁处理, 怎么处理的问题, 目的是站在一定高度上认识信号的作用
	和意义.
3.5.2.常见信号介绍
	本节对常见需要注意的几个信号进行介绍, 其他不常用信号可以暂时不理, 遇到时再去查文档处理.
3.5.3.进程对信号的处理
	本节介绍进程对信号的三种处理方法, signal函数和sigaction函数用来捕获信号时的差异.
3.5.4.alarm和pause函数
	本节对alarm函数和pause函数进行讲解和实战编程, 这两个函数的实现都和信号有关.
//=======================================================================================================
									3.5.1.什么是信号
//-------------------------------------------------------------------------------------------------------
	1. 信号是内容受限的一种异步通信机制 (操作系统与进程, 进程与进程)
	
		1) 信号的目的：用来通信.
		2) 信号是异步的(对比硬件中断), 类似与软件中断.
		3) 信号本质上是int型数字编号(事先定义好的).
		
	2. 信号由谁发出
	
		1) 用户在终端按下按键.
		2) 硬件异常后由操作系统内核发出信号.
		3) 用户使用kill命令向其他进程发出信号.
		4) 某种软件条件满足后也会发出信号, 如alarm闹钟时间到会产生SIGALARM信号; 如向一个读端已经关闭的
		   管道write时会产生SIGPIPE信号(本进程接收这个信号, 就知道对方无法接收到了).
		   
	3. 信号由谁处理、如何处理
	
		1) 忽略信号.
		2) 捕获信号(信号绑定了一个函数).
		3) 默认处理(当前进程没有明显的管这个信号, 按照操作系统默认的处理：忽略或终止进程).
		
			如果明确了忽略还是捕获信号, 则默认的处理就会失效.

//=======================================================================================================
									3.5.2.常见信号介绍
//-------------------------------------------------------------------------------------------------------
	1. 常见信号介绍
	
		1) SIGINT			2		Ctrl+C时OS送给前台进程组中每个进程
		2) SIGABRT			6		调用abort函数，进程异常终止
		3) SIGPOLL	SIGIO	8		指示一个异步IO事件，在高级IO中提及
		4) SIGKILL			9		杀死进程的终极办法
		5) SIGSEGV			11		无效存储访问时OS发出该信号
		6) SIGPIPE			13		涉及管道和socket
		7) SIGALARM			14		涉及alarm函数的实现
		8) SIGTERM			15		kill命令发送的OS默认终止信号
		9) SIGCHLD			17		子进程终止或停止时OS向其父进程发此信号
		10)
		   SIGUSR1			10		用户自定义信号，作用和意义由应用自己定义
		   SIGUSR2			12		用户自定义信号，作用和意义由应用自己定义

	2. 解释:
	
		1) CTRL+C, 发送SIGINT信号给前台进程.  不会发给后台进程.
		2) abort()函数调用后会发送SIGABRT信号. (???? 进程调用该函数终止自己???)
		3) 高级IO, 是说异步通信IO, 或者多路复用IO. 用来处理并发事件.
		   初级IO, 是说的文件IO.
		4) SIGKILL信号, 是不能被拦截的. 操作系统设计出来, 就是为了可以处理恶意的用户程序.
			kill -9 pid  (当然这里涉及到权限问题).
		5) SIGSEGV, 段错误信息就属于这种信号. 系统发送出来.
		6) SIGPIPE, 当在对方已经关闭的管道时, 会发送这个信号.
		7) SIGTERM, 也是用来终止进程的信号.

//=======================================================================================================
									3.5.3.进程对信号的处理
//-------------------------------------------------------------------------------------------------------
	1. signal函数介绍
	
		#include <signal.h>

		typedef void (*sighandler_t)(int);

		sighandler_t signal(int signum, sighandler_t handler);

		1) sighandler_t 是一个函数指针.
		2) signal()函数的作用: 向操作系统注册一个信号的处理方法. sighandler_t handler指针指向的函数就是
		   该处理方法.
		3) 返回值(????)
			signal()  returns  the previous value of the signal handler, or SIG_ERR
			on error.  In the event of an error,  errno  is  set  to  indicate  the
			cause.

	2. 用signal函数处理SIGINT信号

		1) 默认处理
		
			默认处理就是不管它, 之前的程序都是不管的. 
			中断输入CTRL+C, 发送SIGINT信号, 终止当前进程.
		
		2) 忽略处理
		
		3) 捕获处理
		
			void func(int sig)
			{
				if (SIGINT != sig)
					return;
				
				printf("func for signal: %d.\n", sig);
			}

			int main(void)
			{
				signal(SIGINT, func);					// 注册一个信号处理函数.

				printf("before while(1)\n");
				while(1);
				printf("after while(1)\n");
				
				return 0;
			}		
			
			a) 运行后, CTRL+C不能终止程序.
			b) CTRL+C, 调用func函数.
			c) 如何关闭?  可以在另外一个中断中, ps -ajx 查询PID, 然后 kill -9 pid.		

	3. 细节：
	
		1) signal函数绑定一个捕获函数后信号发生后会自动执行绑定的捕获函数，并且把信号编号作为传参传给
		   捕获函数.
		   
		2) signal的返回值在出错时为SIG_ERR, 绑定成功时返回旧的捕获函数.
			
			a) SIG_ERR 在 /usr/include/i386-linux-gnu/bits/signum.h 中有定义:
			
				/* Fake signal functions.  *
				#define SIG_ERR ((__sighandler_t) -1)           /* Error return.  *
				#define SIG_DFL ((__sighandler_t) 0)            /* Default action.  *
				#define SIG_IGN ((__sighandler_t) 1)            /* Ignore signal.  *

				__sighandler_t 是内核使用的, sighandler_t是应用层使用的. 
			
			b) SIG_DFL是默认处理:
			
				signal(SIGINT, SIG_DFL);		// 指定信号SIGINT为默认处理
				
			c) SIG_IGN 是忽略处理:
				
				signal(SIGINT, SIG_IGN);		// 指定信号SIGINT为忽略处理
				
	4. signal函数的优点和缺点
	
		1) 优点：简单好用, 捕获信号常用.
		
		2) 缺点：无法简单直接得知之前设置的对信号的处理方法.
		
		    The behavior of signal() varies across UNIX versions, and has also var‐
		    ied historically across different versions of Linux.   Avoid  its  use:
            use sigaction(2) instead.  See Portability below.
			
		Portability
		    The  only  portable use of signal() is to set a signal's disposition to
		    SIG_DFL or SIG_IGN.  The semantics when using signal() to  establish  a
		    signal handler vary across systems (and POSIX.1 explicitly permits this
		    variation); do not use it for this purpose.
		   
		    使用SIG_DFL, SIG_IGN时, 不同LINUX发行版本的程序可移植. 而在建立一个捕获函数的时候, 
			在不同版本不同.


	5. sigaction函数

		#include <signal.h>

		int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	
        struct sigaction {
            void     (*sa_handler)(int);
            void     (*sa_sigaction)(int, siginfo_t *, void *);
            sigset_t   sa_mask;
            int        sa_flags;
            void     (*sa_restorer)(void);
        };
		
		If act is non-NULL, the new action for signal signum is installed  from
		act.  If oldact is non-NULL, the previous action is saved in oldact.

		1) 一般都是使用第一个参数, 其他参数不用考虑.
		2) sigaction()函数, 第二个参数有const, 是给函数传参的. 第三个参数没有const, 是函数向外边传参的.
		3) oldact, 上一次设置的指针.
		4) 第二个参数设置为NULL时, 用于读取捕获函数指针, 而不设置新的捕获函数.
		   第三个参数设置为NULL时, 表示不读取老的捕获函数.
		
	6. sigaction函数说明:
	
		1) 两个都是API, 但是sigaction比signal更具有可移植性.
		
		2) 用法关键是两个sigaction指针

		3) sigaction比signal好的一点：sigaction可以一次得到设置新捕获函数和获取旧的捕获函数.
		   (其实还可以单独设置新的捕获或者单独只获取旧的捕获函数), 而signal函数不能单独获取旧的捕获
		   函数而必须在设置新的捕获函数的同时才获取旧的捕获函数.
		   
		   所以如果用signal()函数获取当前的捕获函数, 而不想设置新的捕获函数. 需要: 先调用该函数, 设置
		   一个新的函数; 再把获取的旧的函数指针再次当做新的函数指针, 再次调用一次signal()函数.

		总结: 
				1) signal函数要想知道旧的捕获函数, 必须先设置一个新的捕获函数.
				2) sigaction函数如果想知道旧的捕获函数, 则把第二个参数设置为NULL即可.

		(?????)捕获函数什么情况下需要更改???

//=======================================================================================================
									3.5.4.alarm和pause函数
//-------------------------------------------------------------------------------------------------------
	1. alarm函数

		unsigned int alarm(unsigned int seconds);

		alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds 
		seconds.
		

		1) 内核以API形式提供的闹钟.
		
		2) 时间到了以后, 内核发送一个SIGALRM给进程, 进程可以捕获该信号(绑定一个捕获函数).
		
		3) 第一次调用函数的返回值是0, 之后调用是定时剩余的秒数.
		
		4) 系统为每一个进程只提供了一个定时闹钟, 每次调用都会刷新闹钟值.

	2. alarm函数编程实践
	
		void func(int sig)
		{
			if (sig == SIGALRM)
			{
				printf("alarm happened.\n");
			}
		}		
	
		int main(void)
		{
			unsigned int ret = -1;
			
			// 使用signal()函数实现
			//signal(SIGALRM, func);					// 注册一个信号处理函数.
			
			// 使用sigaction()函数实现
			struct sigaction act = {0};
			act.sa_handler = func;
			sigaction(SIGALRM, &act, NULL);

			ret = alarm(5);
			printf("1st, ret = %d.\n", ret);
			
			while (1);									// 等待SIGALRM
			return 0;
		}		
		
		运行结果:
			1st, ret = 0.
			alarm happened.


	3. pause函数

		#include <unistd.h>

		int pause(void);

		pause()  causes  the  calling  process  (or  thread) to sleep until a signal is delivered that either terminates the
		process or causes the invocation of a signal-catching function.

		pause() returns only when a signal was caught and the signal-catching  function  returned.   In  this  case  pause()
		returns -1, and errno is set to EINTR.

	
		1) 内核挂起
		
			a) pause函数的作用就是让当前进程暂停运行, 交出CPU给其他进程去执行. 当当前进程进入pause状态
			   后当前进程会表现为“卡住、阻塞住”, 要退出pause状态当前进程需要被信号唤醒.
			
			b) 与while(1) 不同, 会占用CPU的时间.
			
	4. 使用alarm和pause来模拟sleep

		void func(int sig)
		{												// 空函数

		}

		void mysleep(unsigned int seconds)
		{
			struct sigaction act = {0};
			
			act.sa_handler = func;
			sigaction(SIGALRM, &act, NULL);
			
			alarm(seconds);
			pause();
		}

		int main(void)
		{
			printf("before mysleep.\n");
			mysleep(3);
			printf("after mysleep.\n");
			
			return 0;
		}

		运行结果:
			before mysleep.
			after mysleep.

//=======================================================================================================





















