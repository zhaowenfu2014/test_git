/*
//=======================================================================================================
										3.3.获取系统信息
//=======================================================================================================
3.3.1.关于时间的概念
3.3.2.linux系统中的时间
3.3.3.时间相关API实战1
3.3.4.时间相关API实战2
3.3.5.linux中使用随机数
3.3.6.proc文件系统介绍
3.3.7.proc文件系统的使用
//=======================================================================================================
3.3.1.关于时间的概念
	本节讲述有关时间的一些概念, 包括GMT时间、UTC时间和计算机中与时间有关的部件、工作原理.
3.3.2.linux系统中的时间
	本节讲解linux系统中如何记录时间, 以及linux API中与时间操作有关的部分.
3.3.3.时间相关API实战1
	本节通过实践编写代码测试的方式来逐一测试使用linux中时间相关API函数.
3.3.4.时间相关API实战2
	本节通过实践编写代码测试的方式来逐一测试使用linux中时间相关API函数.
3.3.5.linux中使用随机数
	本节讲解随机数和伪随机数的概念, 并且讲述linux下获取随机数的API并写代码实际测试.
3.3.6.proc文件系统介绍
	本节介绍linux中/proc目录代表的proc虚拟文件系统工作原理和作用, 并讲述了proc中常见的几个文件的作用.
3.3.7.proc文件系统的使用
	本节讲述proc文件系统的使用方法并写代码进行实践测试.
//=======================================================================================================
									3.3.1.关于时间的概念
//-------------------------------------------------------------------------------------------------------
	1. GMT时间
	
		1) GMT是格林尼治时间, 也就是格林尼治地区的当地之间. 是通过天文观测确定的时间.
		2) GMT时间的意义？用格林尼治的当地时间作为全球国际时间, 用以描述全球性的事件的时间, 方便大家
		   记忆.
		3) 一般为了方便, 一个国家都统一使用一个当地时间.

	2. UTC时间
	
		1) GMT时间是以前使用的, 近些年来越来越多的使用UTC时间.
		2) 关于北京时间，可以参考：http://www.cnblogs.com/qiuyi21/archive/2008/03/04/1089456.html

		总结:
				整个地球分为二十四时区, 每个时区都有自己的本地时间. 在国际无线电通信场合, 为了统一起见,
				使用一个统一的时间, 称为通用协调时(UTC, Universal Time Coordinated). 
				UTC与格林尼治平均时(GMT, Greenwich Mean Time)一样, 都与英国伦敦的本地时相同. 
				在本文中, UTC与GMT含义完全相同.

				北京时区是东八区, 领先UTC八个小时, 在电子邮件信头的Date域记为+0800. 如果在电子邮件的信
				头中有这么一行：Date: Fri, 08 Nov 2002 09:42:22 +0800
				说明信件的发送地的地方时间是二○○二年十一月八号, 星期五, 早上九点四十二分(二十二秒), 这
				个地方的本地时领先UTC八个小时(+0800, 就是东八区时间).

	3. 计算机中与时间有关的部件
	
		1) 点时间和段时间: 段时间 = 点时间 - 点时间.
		
		2) 定时器和实时时钟. 定时器(timer)定的时间就是段时间, 实时时钟(RTC)就是和点时间有关的一个器件.

//=======================================================================================================
									3.3.2.linux系统中的时间
//-------------------------------------------------------------------------------------------------------
	1. jiffies的引入
	
		1) jiffies是linux内核中的一个全局变量, 这个变量用来记录以内核的节拍时间为单位时间长度的一个数值.
		
		2) 内核配置的时候定义了一个节拍时间, 实际上linux内核的调度系统工作时就是以这个节拍时间为时间
		   片的.
		   
		3) jiffies变量开机时有一个基准值, 然后内核每过一个节拍时间jiffies就会加1, 然后到了系统的任意
		   一个时间我们当前时间就被jiffies这个变量所标注.

	2. linux系统如何记录时间
	
		1) 内核在开机启动的时候会读取RTC硬件获取一个时间作为初始基准时间, 这个基准时间对应一个jiffies值
		   (这个基准时间换算成jiffies值的方法是：用这个时间减去1970-01-01 00:00:00 +0000(UTC), 然后把这
		   个时间段换算成jiffies数值), 这个jiffies值作为我们开机时的基准jiffies值存在. 然后系统运行时
		   每个时钟节拍的末尾都会给jiffies这个全局变量加1, 因此操作系统就使用jiffies这个全局变量记录了
		   下来当前的时间. 当我们需要当前时间点时, 就用jiffies这个时间点去计算(计算方法就是先把这个
		   jiffies值对应的时间段算出来, 然后加上1970-01-01 00:00:00 +0000(UTC)即可得到这个时间点).
		   
		2) 其实操作系统只在开机时读一次RTC, 整个系统运行过程中RTC是无作用的. RTC的真正作用其实是在OS的
		   2次开机之间进行时间的保存.
		   
		3) 理解时一定要点时间和段时间结合起来理解. jiffies这个变量记录的其实是段时间(其实就是当前时间
		   和1970-01-01 00:00:00 +0000(UTC)这个时间的差值).
		   
		4) 一个时间节拍的时间取决于操作系统的配置, 现代linux系统一般是10ms或者1ms. 这个时间其实就是调
		   度时间, 在内核中用HZ来记录和表示. 如果HZ定义成1000难么时钟节拍就是1/HZ, 也就是1ms. 这些在
		   学习驱动时会用到.

	3. linux中时间相关的系统调用
	
		1) 常用的时间相关的'API'和'C库'函数有9个：time/ctime/localtime/gmtime/mktime/asctime/strftime/
		   gettimeofday/settimeofday.

		2) time()系统调用返回当前时间以秒为单位的距离1970-01-01 00:00:00 +0000(UTC)过去的秒数. 这个
		   time内部就是用jiffies换算得到的秒数. 其他函数基本都是围绕着time来工作的.

			time_t time(time_t *t);				// man 2 time
			
			On success, the value of time in seconds since the Epoch is returned.  On
			error, ((time_t) -1) is returned, and errno is set appropriately.

		3) gmtime()和localtime()会把time得到的秒数变成一个struct tm结构体表示的时间. 区别是gmtime()得到
		   的是国际时间, 而localtime得到的是本地(指的是你运行localtime()函数的程序所在的计算机所设置的
		   时区对应的本地时间)时间. mktime()用来完成相反方向的转换(struct tm到time_t).

			struct tm *gmtime(const time_t *timep);
			struct tm *localtime(const time_t *timep);

		
           struct tm {
               int tm_sec;         /* seconds */
               int tm_min;         /* minutes */
               int tm_hour;        /* hours */
               int tm_mday;        /* day of the month */
               int tm_mon;         /* month */
               int tm_year;        /* year */
               int tm_wday;        /* day of the week */
               int tm_yday;        /* day in the year */
               int tm_isdst;       /* daylight saving time */
           };						/*
		
		4) 如果从struct tm出发想得到字符串格式的时间, 可以用asctime()或者strftime()都可以. (如果从
		   time_t出发想得到字符串格式的时间用ctime即可).

		5) gettimeofday()返回的时间是由struct timeval和struct timezone这两个结构体来共同表示的, 其中
		   timeval表示时间, 而timezone表示时区. settimeofday()是用来设置当前的时间和时区的.

			   struct timeval {
				   time_t      tv_sec;     /* seconds */
				   suseconds_t tv_usec;    /* microseconds */
			   };

			   struct timezone {
				   int tz_minuteswest;     /* minutes west of Greenwich */
				   int tz_dsttime;         /* type of DST correction */
			   };						  /*

		6) 总结：不管用哪个系统调用, 最终得到的时间本质上都是一个时间(这个时间最终都是从kernel中记录的
		         jiffies中计算得来的), 只不过不同的函数返回的时间的格式不同, 精度不同.

//=======================================================================================================
									3.3.3.时间相关API实战1
//-------------------------------------------------------------------------------------------------------
	1. time()
	
		1) time能得到一个当前时间距离标准起点时间1970-01-01 00:00:00 +0000(UTC)过去了多少秒.
		
		2) man 2 time:
		
			time_t time(time_t *t);				// man 2 time
			
			On success, the value of time in seconds since the Epoch is returned.  On
			error, ((time_t) -1) is returned, and errno is set appropriately.
		
		3) 测试:
		
			time_t tNow = -1;

			tNow = time(NULL);		// 返回值
			if (tNow < 0)
			{
				perror("time");
				return -1;
			}
			printf("time: %ld.\n", tNow);
				

	2. ctime()
	
		1) ctime()可以从time_t出发得到一个容易观察的字符串格式的当前时间.

		2) man 3 ctime
		
			char *ctime(const time_t *timep);

		3) ctime好处是很简单好用, 可以直接得到当前时间的字符串格式, 直接打印来看. 坏处是ctime的打印
		   时间格式是固定的, 没法按照我们的想法去变.
		   
		4) 测试:
		
			time_t tNow = -1;
			
			// time
			time(&tNow);				// 指针做输出型参数
			if (tNow < 0)
			{
				perror("time");
				return -1;
			}
			printf("time: %ld.\n", tNow);
			
			// ctime
			printf("ctime: %s.\n", ctime(&tNow));
			
			运行结果:
			time: 1689750605.
			ctime: Wed Jul 19 15:10:05 2023

			实验结果可以看出, ctime函数得到的时间是考虑了计算机中的本地时间的(计算机中的时区设置).
			
	3. gmtime()和localtime()
	
		1) gmtime()获取的时间中：年份是以1970为基准的差值, 月份是0表示1月, 小时数是以UTC时间的0时区为
		   标准的小时数(北京是东8区, 因此北京时间比这个时间大8)

		2) 猜测localtime()和gmtime()的唯一区别就是localtime以当前计算机中设置的时区为小时的时间基准,
		   其余一样. 实践证明我们的猜测是正确的.
		
		3) man 3 gmtime
			
		   struct tm *gmtime(const time_t *timep);
		   struct tm *gmtime_r(const time_t *timep, struct tm *result);

		   struct tm *localtime(const time_t *timep);
		   struct tm *localtime_r(const time_t *timep, struct tm *result);
		   
           struct tm {
               int tm_sec;         /* seconds */
               int tm_min;         /* minutes */
               int tm_hour;        /* hours */
               int tm_mday;        /* day of the month */
               int tm_mon;         /* month */
               int tm_year;        /* year */
               int tm_wday;        /* day of the week */
               int tm_yday;        /* day in the year */
               int tm_isdst;       /* daylight saving time */
           };						/*					
				
		   tm_sec    The number of seconds after the minute, normally in the range 0
					 to 59, but can be up to 60 to allow for leap seconds.

		   tm_min    The number of minutes after the hour, in the range 0 to 59.

		   tm_hour   The number of hours past midnight, in the range 0 to 23.

		   tm_mday   The day of the month, in the range 1 to 31.

		   tm_mon    The number of months since January, in the range 0 to 11.

		   tm_year   The number of years since 1900.

		   tm_wday   The number of days since Sunday, in the range 0 to 6.

		   tm_yday   The number of days since January 1, in the range 0 to 365.

		   tm_isdst  A flag that indicates whether daylight saving time is in effect
					 at  the time described.  The value is positive if daylight sav‐
					 ing time is in effect, zero if it is not, and negative  if  the
					 information is not available.
		   
		4) 测试:

			time_t tNow = -1;
			struct tm tmNow;

			time(&tNow);				// 指针做输出型参数
			...
			memset(&tmNow, 0, sizeof(tmNow));
			gmtime_r(&tNow, &tmNow);					// 调用可重入版本的函数(!!!!)
			printf("年%d月%d日%d时%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
			
			memset(&tmNow, 0, sizeof(tmNow));
			localtime_r(&tNow, &tmNow);
			printf("年%d月%d日%d时%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
			
			运行结果: (当时时间为2023年7月19日15点)
				年123月6日19时7.
				年123月6日19时15.			
			
			(得到的年并不是实际的2023年, 而是2023-1900. 因为 tm_year   The number of years since 1900)

//=======================================================================================================
									3.3.4.时间相关API实战2
//-------------------------------------------------------------------------------------------------------
	1. mktime()
	
		1) 从OS中读取时间时用不到mktime()的, 这个mktime()是用来向操作系统设置时间时用的.
		
		2) man mktime
		
			time_t mktime(struct tm *tm);
			 
			从tm结构体变量, 得到time_t. 得到一个当前时间距离标准起点过去了多少秒.
			
	2. asctime()
	
		1) asctime()得到一个固定格式的字符串格式的当前时间, 效果上和ctime一样的. 区别是ctime()从time_t
		   出发, 而asctime()从struct tm出发.

	3. strftime()
	
		1) asctime()和ctime()得到的时间字符串都是固定格式的, 没法用户自定义格式.
		
		2) 如果需要用户自定义时间的格式, 则需要用strftime().
			
			size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
			
				// 输入是tm型数据, 输出为字符串char *s, 格式化标准为const char *format, 输出字符串的
				// 大小为max.

			%Y     The year as a decimal number including the century.
		    %m     The month as a decimal number (range 01 to 12).
		    %d     The day of the month as a decimal number (range 01 to 31).
			%H     The hour as a decimal number using a 24-hour clock  (range  00  to
			%M     The minute as a decimal number (range 00 to 59).
			%S     The second as a decimal number (range 00 to 60).  (The range is up
				    to 60 to allow for occasional leap seconds.)
			...		

		3) 测试:
			
			time_t tNow = -1;
			struct tm tmNow;
			char buf[100];
					
			memset(buf, 0, sizeof(buf));
			strftime(buf, sizeof(buf), "%Y * %m * %d, %H-%M-%S.", &tmNow);
			printf("时间为：[%s].\n", buf);

			运行结果: 时间为：[2023 * 07 * 19, 15-46-06.].

	4. gettimeofday()和settimeofday()
	
		1) 前面讲到的基于time()函数的那个系列都是以秒为单位来获取时间的, 没有比秒更精确的时间.
		
		2) 有时候我们程序希望得到非常精确的时间(譬如以us为单位), 这时候就只能通过gettimeofday()来实现了.
		   gettimeofday()返回的时间是由struct timeval和struct timezone这两个结构体来共同表示的, 其中
		   timeval表示时间, 而timezone表示时区. settimeofday()是用来设置当前的时间和时区的.
		3) man 2 gettimeofday
		
			int gettimeofday(struct timeval *tv, struct timezone *tz);
			int settimeofday(const struct timeval *tv, const struct timezone *tz);

			gettimeofday() and settimeofday() return 0 for success, or -1 for failure
			(in which case errno is set appropriately).

			   struct timeval {
				   time_t      tv_sec;     /* seconds */					(!!!!) 秒
				   suseconds_t tv_usec;    /* microseconds */				(!!!!) 微妙
			   };

			   struct timezone {
				   int tz_minuteswest;     /* minutes west of Greenwich */	(???) 举例格林尼治的时区
				   int tz_dsttime;         /* type of DST correction */
			   };						  /*	


		4) 测试：

			struct timeval tv = {0};
			struct timezone tz = {0};
			int ret = -1;

			ret = gettimeofday(&tv, &tz);
			if (ret < 0)
			{
				perror("gettimeofday");
				return -1;
			}
			printf("seconde: %ld.\n", tv.tv_sec);
			printf("timezone:%d.\n", tz.tz_minuteswest);

			运行结果:
				seconde: 1689752766.				// 举例1970年的秒数.
				timezone:-480.						// 480分钟, 8小时. 东8区

//=======================================================================================================
									3.3.5.linux中使用随机数
//-------------------------------------------------------------------------------------------------------
	1. 随机数和伪随机数
	
		1) 随机数是随机出现, 没有任何规律的一组数列.
		2) 真正的完全随机的数列是不存在的, 只是一种理想情况. 我们平时要用到随机数时一般只能通过一些算法
		   得到一个伪随机数序列.
		3) 我们平时说到随机数, 基本都指的是伪随机数.

	2. linux中随机数相关API
	
		1) 连续多次调用rand()函数可以返回一个伪随机数序列.
		2) srand()函数用来设置rand()获取的伪随机序列的种子.
		3) rand是一个库函数, 没有API. 所以 man 2 rand 不可以查看用法.
		
		int rand(void);
		int rand_r(unsigned int *seedp);
		void srand(unsigned int seed);		

		The  rand()  function  returns  a pseudo-random integer in the range 0 to
		RAND_MAX inclusive (i.e., the mathematical range [0, RAND_MAX]). 
		
		RAND_MAX = 2147483647.

	3. 实战演示
	
		1) 单纯使用rand重复调用n次, 就会得到一个0-RAND_MAX之间的伪随机数, 如果需要调整范围, 可以得到
		   随机数序列后再进行计算(结果%N, N就是想要的数字区间).
		   
		2) 单纯使用rand来得到伪随机数序列有缺陷, 每次执行程序得到的伪随机序列是同一个序列, 没法得到其
		   他序列.
		   
		3) 原因是因为rand内部的算法其实是通过一个种子(seed, 其实就是一个原始参数, int类型), rand()内
		   部默认是使用1作为seed的, 种子一定的算法也是一定的, 那么每次得到的伪随机序列肯定是同一个.
		   
		4) 所以要想每次执行这个程序获取的伪随机序列不同, 则每次都要给不同的种子. 用srand()函数来设置
		   种子.

			srand(time(NULL));					// srand()获取一个种子.
			
			for (i=0; i<6; i++)					//
			{
				val = rand();					// 产生一个随机数.
				printf("%d ", (val % 6));		// 产生的随机数0-5.
			}

	4. 总结和说明
	
		1) 在每次执行程序时, 先用srand()设置一个不同的种子, 然后再多次调用rand()获取一个伪随机序列,
		   这样就可以每次都得到一个不同的伪随机序列.
		2) 一般常规做法是用time()函数的返回值来做srand的参数.

	5. 在linux系统中获取真正的随机数
	
		1) linux系统收集系统中的一些随机发生的事件的时间(譬如有人动鼠标, 譬如触摸屏的操作和坐标等)作
		   为随机种子去生成随机数序列.

//=======================================================================================================
									3.3.6.proc文件系统介绍
//-------------------------------------------------------------------------------------------------------
	1. 操作系统级别的调试
	
		1) 简单程序单步调试.
			单步调试有很多限制: 需要有一定的环境支持单步调试; 多线程的程序,也不适合单步调试.
		2) 复杂程序printf打印信息调试.
		3) 框架体系日志记录信息调试.
			适合长时间检测, 把一些信息输出到日志文件中.
		4) 内核调试的困境
			以上所有的方法, 是由内核程序提供的服务. 内核程序有问题时, 以上调试手段可能都不能用.
		
	2. proc虚拟文件系统的工作原理
	
		1) linux内核是一个非常庞大、非常复杂的一个单独的程序, 对于这样的一个程序来说调试是非常复杂的.
		2) 像kernel这样庞大的项目, 给里面添加/更改一个功能是非常麻烦的, 因为你这添加的一个功能可能会
		   影响其他已经有的.
		3) 早期内核版本中尽管调试很麻烦, 但是高手们还可以凭借个人超凡脱俗的能力去驾驭. 但是到了2.4左右
		   的版本的时候, 这个难度已经非常大了.
		4) 为了降低内核调试和学习的难度, 内核开发者们在内核中添加了一些'属性'专门用于调试内核, proc文件
		   系统就是一个尝试.
		5) proc文件系统的思路是：在内核中构建一个虚拟文件系统/proc, 内核运行时将内核中一些关键的数据
		   结构以文件的方式呈现在/proc目录中的一些特定文件中, 这样相当于将不可见的内核中的数据结构以
		   可视化的方式呈现给内核的开发者.
		   
		   比如: 一个进程包含进程结构PCB, 里面有一个文件表, 包含当前进程打开说的所有的文件信息. 这就是
		         内核的一个数据结构. 在内核中是通过变量形式存在的, 我们是看不到的.  但是内核有一个功能:
				 就是实时的把这些数据按照文件的形式写到/proc目录, 我们就可以通过这个目录下的特定的文件,
				 实时的看到内核中的数据结构的值. 就相当于开发者可以看到内核的变量了.
		   
		6) proc文件系统给了开发者一种调试内核的方法：我们通过实时的观察/proc/xxx文件, 来观看内核中特定
		   数据结构的值. 在我们添加一个新功能的前后来对比, 就可以知道这个新功能产生的影响对还是不对.
		   
		7) proc目录下的文件大小都是0, 因为这些文件本身并不存在于硬盘中, 他也不是一个真实文件, 他只是
		   一个接口, 当我们去读取这个文件时, 其实内核并不是去硬盘上找这个文件, 而是映射为内核内部一个
		   '数据结构'被读取并且'格式化成字符串'返回给我们. 所以尽管我们看到的还是一个文件内容字符串,
		   和普通文件一样的; 但是实际上我们知道这个内容是实时的从内核中数据结构来的, 而不是硬盘中来的.
		   
		8) (!!!!!) 这些文件都是只能看, 不能修改.

	3. 常用proc中的文件介绍
	
		1) /proc/cmdline
		
			a) 这个文件保存的内核被实时传参, 传进来的命令行参数. ubuntu中查看: cat /proc/cmdline
			
			   BOOT_IMAGE=/boot/vmlinuz-3.13.0-32-generic root=UUID=e46e78eb-87b1-4f25-b758-19649125d60a 
			           ro find_preseed=/preseed.cfg auto noprompt priority=critical locale=en_US quiet
			b) vi /proc/cmdline 也可以看到内容.
			c) ls -l /proc/cmdline 
				-r--r--r-- 1 root root 0 Jul 19 17:25 cmdline		// 大小是0, 与普通文件不同.

		2) /proc/cpuinfo
		
			查看CPU的所有信息. 都是内核里面的一些结构体变量的数据, 通过格式化后输出的.	
		
		3) /proc/devices
		
			查看内核中安装的所有的驱动.
		
		4) /proc/interrupts

//=======================================================================================================
									3.3.7.proc文件系统的使用
//-------------------------------------------------------------------------------------------------------
	1. proc文件系统的使用
	
		1) cat以手工查看.
		
		2) 程序中可以文件IO访问.
		
			open()打开文件, read()读取文件内容.
		
		3) 在shell程序中用cat命令结合正则表达式来获取并处理内核信息.
		
	2. 程序中读取/proc虚拟文件测试

		int main(int argc, char **argv)
		{
			int fd = -1;
			char buf[512] = {0};
			
			if (argc != 2)
			{
				printf("usage: %s -v|-d\n", argv[0]);
				return -1;
			}
			if (!strcmp(argv[1], "-v"))
			{
				fd = open("/proc/version", O_RDONLY);
				if (fd < 0)
				{
					perror("open /proc/version");
					return -1;
				}
				read(fd, buf, sizeof(buf));
				printf("结果是：%s.\n", buf);
			}
			else if (!strcmp(argv[1], "-d"))
			{
				fd = open("/proc/devices", O_RDONLY);
				if (fd < 0)
				{
					perror("open /proc/devices");
					return -1;
				}
				read(fd, buf, sizeof(buf));
				printf("结果是：%s.\n", buf);
			}
			return 0;
		}

	2. 扩展：sys文件系统
	
		1) sys文件系统本质上和proc文件系统是一样的, 都是虚拟文件系统, 都在根目录下有个目录(一个是/proc
		   目录, 另一个是/sys目录), 因此都不是硬盘中的文件, 都是内核中的数据结构的可视化接口.
		   
		2) 不同的是/proc中的文件只能读, 但是/sys中的文件可以读写. 
		
		3) 读/sys中的文件就是获取内核中数据结构的值, 而写入/sys中的文件就是设置内核中的数据结构的元素
		   的值.
		   
		4) 历史上刚开始先有/proc文件系统, 人们希望通过这种技术来调试内核. 实际做出来后确实很有用, 所以
		   很多内核开发者都去内核调价代码向/proc目录中写文件, 而且刚开始的时候内核管理者对proc目录的
		   使用也没有什么经验也没什么统一规划, 后来的结果就是proc里面的东西又多又杂乱.
		   
		5) 后来觉得proc中的内容太多太乱缺乏统一规划, 于是乎又添加了sys目录. sys文件系统一开始就做了很
		   好的规划和约定, 所以后来使用sys目录时有了规矩.

		总结: /sys 目录的文件也是虚拟文件, 都是内核中数据结构的可视化接口. 但是可以读, 写. 
		
			(?????) 课程中说/proc 目录的文件不可以写, 是不是这样????

//=======================================================================================================








