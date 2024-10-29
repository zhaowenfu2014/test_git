/*
//=======================================================================================================
									2.20.buildroot的引入和介绍
//=======================================================================================================
3.1.1.应用编程框架介绍
3.1.2.文件操作的主要接口API
3.1.3.一个简单的文件读写实例
3.1.4.open函数的flag详解1
3.1.5.open函数的flag详解2
3.1.6.文件读写的一些细节
3.1.7.linux系统如何管理文件
3.1.8.lseek详解
3.1.9.多次打开同一文件与O_APPEND
3.1.10.文件共享的实现方式
3.1.11.文件描述符的复制1
3.1.12.文件描述符的复制2
3.1.13.fcntl函数介绍
3.1.14.标准IO库介绍
//=======================================================================================================
3.1.1.应用编程框架介绍
	本节讲述linux应用编程课程的整体设计框架和设计思路, 然后讲了本课程文件IO的含义和课程内容.
3.1.2.文件操作的主要接口API
	本节首先介绍操作系统API的概念, 然后介绍文件IO的概念以及常用的API, 最后讲了文件描述符.
3.1.3.一个简单的文件读写实例
	本节从零开始手写一个简单的读写文件实例程序, 顺带介绍使用man手册获取函数原型的技巧, 实现向文件中写入
	内容和从文件中读取内容.
3.1.4.open函数的flag详解1	
	本节讲解open函数的flag参数, 主要是读写权限flag和判断文件是否存在的flag, 并且同时以实例程序来验证理论.
3.1.5.open函数的flag详解2
	本节接上节继续讲解open的flag, 主要是创建文件标志、非阻塞标志和同步标志, 并且顺便讲了阻塞和非阻塞的
	概念.
3.1.6.文件读写的一些细节	
	本节讲解文件读写中一些细节, 譬如errno的设置和perror函数、read/write函数中的count参数，最后简单探讨了
	io效率问题, 引出了标准IO.
3.1.7.linux系统如何管理文件	
	本节简单探讨linux系统对文件的管理方法, 重点讲了inode、vnode等概念, 文件在硬盘上静态存储和在内存中被
	打开时的映像方式等.
3.1.8.lseek详解	
	本节讲解lseek函数, 该函数用来移动文件的操作指针. 利用这一特性我们可以计算文件长度、生成空洞文件等.
3.1.9.多次打开同一文件与O_APPEND
	本节探讨一个文件被多次打开时的情况, 这种情况一般在文件共享中发生. 重点讲了O_APPEND标志在其中的作用.
3.1.10.文件共享的实现方式
	本节正式提出文件共享的概念, 并且分析了三种最常出现的文件共享的方式, 以及他们的区别和联系.
3.1.11.文件描述符的复制1
	本节引入文件描述符的复制, 重点讲了dup函数, 并且通过实例说明如何使用dup函数复制文件描述符.
3.1.12.文件描述符的复制2
	本节分析dup函数的缺陷, 并且引入dup2函数来解决.
3.1.13.fcntl函数介绍
	本节介绍文件管理函数fcntl, 该函数功能很强大, 以后会经常用到, 这里只是做初步的介绍和示例其基本用法.
3.1.14.标准IO库介绍
	本节引入标准IO库函数, 并且使用常用标准IO库函数写一个简单的文件操作示例程序.
//=======================================================================================================
								3.1.1.应用编程框架介绍
//-------------------------------------------------------------------------------------------------------
	1. 什么是应用编程
		
		1) 整个嵌入式linux核心课程包括5个点, 按照学习顺序依次是：裸机、C高级、uboot和系统移植、linux
		   应用编程和网络编程、驱动.
		2) 典型的嵌入式产品就是基于嵌入式linux操作系统来工作的. 典型的嵌入式产品的研发过程就是；第一步
		   让linux系统在硬件上跑起来(系统移植工作), 第二步基于linux系统来开发应用程序实现产品功能.
		3) 基于linux去做应用编程, 其实就是通过调用linux的'系统API'来实现应用需要完成的任务.

	2. 本课程大纲规划

	3. 课程设计思路
	
		1) 通过本课程9个小课程的学习, 学会如何使用linux系统提供的API(和C库函数)来实现一定的功能, 通过学
		   习对应用层的编程有所掌握来配合后面驱动的学习.
		2) 如果希望深入学习linux应用尤其是网络编程知识, 可以去看一些专门介绍这一块的书.

	4. 什么是文件IO
	
		1) IO就是input/output, 输入/输出. 文件IO的意思就是读写文件. 设计到调用系统API, 操作的硬件包括:
		   磁盘/flash, 内存等.
		   
//=======================================================================================================
								3.1.2.文件操作的主要接口API
//-------------------------------------------------------------------------------------------------------
	1. 什么是操作系统API
	
		1) API是一些函数, 这些函数是由linux系统提供支持的, 由应用层程序来使用.
		2) 应用层程序通过调用API来调用操作系统中的各种功能, 来干活.
		3) 学习一个操作系统, 其实就是学习使用这个操作系统的API.
		4) 今天我们要使用linux系统来读写文件, 手段就是学习linux系统API中和文件IO有关的几个.
		
	2. linux常用文件IO接口
	
		1) open、close、write、read、lseek

	3. 文件操作的一般步骤
	
		1) 在linux系统中要操作一个文件, 一般是先open打开一个文件, 得到一个'文件描述符', 然后对文件进行
		   读写操作(或其他操作), 最后close关闭文件即可.
		2) 强调一点：我们对文件进行操作时, 一定要先打开文件, 打开成功后才能去操作(如果打开本身失败, 后面
		   就不用操作了); 最后读写完成之后一定要close关闭文件, 否则可能会造成文件损坏.
		3) 文件平时是存在'块设备'中的'文件系统'中的, 我们把这种文件叫静态文件. 当我们去open打开一个文件时,
		   linux内核做的操作包括：内核在进程中建立了一个打开文件的数据结构, 记录下我们打开的这个文件; 内
		   核在内存中申请一段内存, 并且将静态文件的内容从块设备中读取到内存中特定地址管理存放(叫动态文件).
		4) 打开文件后, 以后对这个文件的读写操作, 都是针对内存中这一份动态文件的, 而并不是针对静态文件的.
		   当我们对动态文件进行读写后, 此时内存中的动态文件和块设备中的静态文件就不同步了, 当我们close
		   关闭动态文件时, close内部内核将内存中的动态文件的内容去更新(同步)块设备中的静态文件.
		5) 常见的一些现象：
			第一个：打开一个大文件时比较慢
			第二个：我们写了一半的文件, 如果没有点保存直接关机/断电, 重启后文件内容丢失.
		6) 为什么要这么设计？
			因为块设备本身有读写限制(回忆NnadFlash、SD等块设备的读写特征), 本身对块设备进行操作非常不灵活.
			而内存可以按字节为单位来操作, 而且可以随机操作(内存就叫RAM, random), 很灵活. 所以内核设计文件
			操作时就这么设计了.

	4. 重要概念：文件描述符
	
		1) 文件描述符其实实质是一个数字, 这个数字在"一个进程中"表示一个特定的含义, 当我们open打开一个文件
		   时, 操作系统在内存中构建了一些数据结构来表示这个动态文件, 然后返回给应用程序一个数字作为文件描
		   述符, 这个'数字'就和我们'内存中维护这个动态文件的这些数据结构'挂钩绑定上了, 以后我们应用程序如
		   果要操作这一个动态文件, 只需要用这个文件描述符进行区分.
		2) 一句话讲清楚文件描述符：文件描述符就是用来区分一个程序打开的多个动态文件的.
		3) 文件描述符的作用域就是当前进程, 出了当前进程这个文件描述符就没有意义了.

//=======================================================================================================
								3.1.3.一个简单的文件读写实例
//-------------------------------------------------------------------------------------------------------
	1. 打开文件与关闭文件
	
		int open(const char *pathname, int flags);
	
		1) linux中的文件描述符fd的合法范围是0或者一个正整数, 不可能是一个负数.
		2) open返回的fd程序必须记录好, 以后向这个文件的所有操作都要靠这个fd去对应这个文件, 最后关闭文
		   件时也需要fd去指定关闭这个文件. 如果在我们关闭文件前fd丢掉了那就惨了, 这个文件没法关闭了也
		   没法读写了.
		3) 路径名, 可以打开不是当前目录的文件.
		
		测试: touch file1.c   // 创建文件, 编写程序
			  gcc fil21.c
			  ./a.out

	2. 实时查man手册
	
		1) 当我们写应用程序时, 很多API原型都不可能记得, 所以要实时查询, 用man手册.
		2) 	linux shell命令:	man 1 xxx
			linux API:			man 2 xxx 
			库函数查询:			man 3 xxx

	3. 读取文件内容
	
		ssize_t read(int fd, void *buf, size_t count);
		
		1) fd表示要读取哪个文件, fd一般由前面的open返回得到.
		2) buf是应用程序自己提供的一段内存缓冲区, 用来存储读出的内容.
		3) count是我们要读取的字节数.
		4) 返回值ssize_t类型是linux内核用typedef重定义的一个类型(其实就是int), 返回值表示成功读取的字
		   节数.
		   
		总结: count, 是想读取的字节数.  返回值是实际读取到的字节数(可能文件中没有想读取的那么多字节).

	4. 向文件中写入内容
	
		ssize_t write(int fd, const void *buf, size_t count);

		1) 写入用write系统调用, write的原型和理解方法和read相似.
		2) 注意const在buf前面的作用, 结合C语言高级专题中的输入型参数和输出型参数一节来理解.
		3) (!!!!)注意buf的指针类型为void, 结合C语言高级专题中void类型含义的讲解. buf可以是任意的类型.
		4) 刚才先写入12字节, 然后读出结果读出是0(但是读出成功了), 这个问题的答案后面章节会讲, 大家先
		   思考一下.

	5. 总结1:
	
		1) open
		
		   int open(const char *pathname, int flags);
		   int open(const char *pathname, int flags, mode_t mode);
		   int creat(const char *pathname, mode_t mode);
		   
		2) read
		3) write
		4) close
			
			 int close(int fd);
			 
			close()  returns zero on success.  On error, -1 is returned, and errno is
			set appropriately.

	6. 总结2

		用open()函数时, 可以通过 man 2 open, 查看包含了哪些头文件.
		
	7. 总结3:
	
		1) open函数的定义：

			#include <sys/types.h>  
			#include <sys/stat.h>
			#include <fcntl.h>

			int open( const char * pathname, int flags);
			int open( const char * pathname,int flags, mode_t mode);

		2) flags参数:

			1. O_RDONLY 只读打开.
			2. O_WRONLY 只写打开.
			3. O_RDWR 读、写打开.
			4. O_APPEND 每次写时都加到文件的尾端. (以追加的方式打开文件, 打开后文件指针指向文件末尾)
			5. O_CREAT 若此文件不存在则创建它. 使用此选择项时, 需同时说明第三个参数mode, 用其说明该新
			   文件的存取许可权位.
			6. O_EXCL 如果同时指定了O_CREAT, 而文件已经存在, 则出错. 这可测试一个文件是否存在, 如果不
			   存在则创建此文件成为一个原子操作.
			7. O_TRUNC 如果此文件存在, 而且为只读或只写成功打开, 则将其长度截短为0.
			8. O_NOCTTY 如果pathname指的是终端设备, 则不将此设备分配作为此进程的控制终端.
			9. O_NONBLOCK 如果pathname指的是一个F I F O、一个块特殊文件或一个字符特殊文件, 则此选择项
			   为此文件的本次打开操作和后续的I / O操作设置非阻塞方式.
			10. O_NDELAY所产生的结果使I/O变成非阻塞模式(non-blocking), 在读取不到数据或是写入缓冲区已
			   满会马上return, 而不会阻塞等待.
			11. O_SYNC 使每次w r i t e都等到物理I / O操作完成.
			12. O_APPEND 当读写文件时会从文件尾开始移动, 也就是所写入的数据会以附加的方式加入到文件
			    后面.
			13. O_NOFOLLOW 如果参数pathname 所指的文件为一符号连接, 则会令打开文件失败.
			14. O_DIRECTORY 如果参数pathname 所指的文件并非为一目录, 则会令打开文件失败.

		3) mode参数:

			写权限数值.

		4) 例子

			#include <sys/types.h>  
			#include <sys/stat.h>
			#include <fcntl.h>

			int fd;

			fd = open("./test.c",O_CREAT | O_RDONLY,0644);
			
//=======================================================================================================
								3.1.4.open函数的flag详解1
//-------------------------------------------------------------------------------------------------------
	1. open函数的flag. 读写权限：O_RDONLY O_WRONLY O_RDWR

		1) linux中文件有读写权限, 我们在open打开文件时也可以附带一定的权限说明(譬如O_RDONLY就表示以
		   只读方式打开, O_WRONLY表示以只写方式打开, O_RDWR表示以可读可写方式打开).
		2) 当我们附带了权限后, 打开的文件就只能按照这种权限来操作.

	2. 打开存在并有内容的文件时：O_APPEND、O_TRUNC
	
		1) 思考一个问题：当我们打开一个已经存在并且内部有内容的文件时会怎么样?
		
			可能结果1：新内容会替代原来的内容(原来的内容就不见了, 丢了).
			可能结果2：新内容添加在前面, 原来的内容继续在后面.
			可能结果3：新内容附加在后面, 原来的内容还在前面.
			可能结果4：不读不写的时候, 原来的文件中的内容保持不变.
			
		2) O_TRUNC属性去打开文件时, 如果这个文件中本来是有内容的, 则原来的内容会被丢弃. 这就对应上面
		   的结果1.
		3) O_APPEND属性去打开文件时, 如果这个文件中本来是有内容的, 则新写入的内容会接续到原来内容的后
		   面, 对应结果3.
		4) 默认不使用O_APPEND和O_TRUNC属性时就是结果4.
		5) 如果O_APPEND和O_TRUNC同时出现会怎么样? O_TRUNC起作用, O_APPEND不起作用.

	3. exit、_exit、_Exit退出进程
	
		1) 当我们程序在前面步骤操作失败导致后面的操作都没有可能进行下去时, 应该在前面的错误监测中结束
		   整个程序, 不应该继续让程序运行下去了.
		2) 我们如何退出程序？
			第一种：在main用return, 一般原则是程序正常终止return 0, 如果程序异常终止则return -1.
					(!!!!!) 在main()函数中, 可以结束程序. 在其他的函数中, return -1会返回上一级函数中,
					不会终止程序.
			第一种：正式终止进程(程序)应该使用exit或者_exit或者_Exit之一.
					
					exit() : 是库函数. man 3 exit
					_exit(): API
					_Exit(): API
					
					       #include <unistd.h>

							void _exit(int status);

							#include <stdlib.h>

							void _Exit(int status);

//=======================================================================================================
								3.1.5.open函数的flag详解2
//-------------------------------------------------------------------------------------------------------
	1. open函数打开不存在的文件时：O_CREAT、O_EXCL

		1) 思考：当我们去打开一个并不存在的文件时会怎样？当我们open打开一个文件时如果这个文件名不存在
		   则会打开文件错误.
		   
		2) vi或者windows下的notepad++, 都可以直接打开一个尚未存在的文件.
		
		3) open的flag O_CREAT就是为了应对这种打开一个并不存在的文件的. O_CREAT就表示我们当前打开的文件
		   并不存在. 我们是要去创建并且打开它.
		   
		4) 思考：当我们open使用了O_CREAT, 但是文件已经存在的情况下会怎样？文件可以打开成功, 不报错.
		
		5) 结论：open中加入O_CREAT后, 不管原来这个文件存在与否都能打开成功, 如果原来这个文件不存在则
		   创建一个空的新文件, 如果原来这个文件存在则会重新创建这个文件, 原来的内容会被消除掉(有点类
		   似于先删除原来的文件再创建一个新的).
		   
		6) 这样可能带来一个问题？我们本来是想去创建一个新文件的, 但是把文件名搞错了弄成了一个老文件名,
		   结果老文件就被意外修改了. 我们希望的效果是：如果我CREAT要创建的是一个已经存在的名字的文件,
		   则给我报错, 不要去创建.
		   
		7) 这个效果就要靠O_EXCL标志和O_CREAT标志来结合使用. 当这两个标志一起的时候, 则没有文件时创建文
		   件, 有这个文件时会报错提醒我们.
		   
		8) open函数在使用O_CREAT标志去创建文件时, 可以使用第三个参数mode来指定要创建的文件的权限. mode
		   使用4个数字来指定权限的, 其中后面三个很重要, 对应我们要创建的这个文件的权限标志. 譬如一般创
		   建一个可读可写不可执行的文件就用0666.
		   
		测试:
			fd = open("a.txt", O_RDWR | O_CREAT | O_EXCL, 0666);
			if (-1 == fd)		
			{
				//printf("文件打开错误\n");
				perror("文件打开错误");
				_exit(-1);
			}
			else
			{
				printf("文件打开成功，fd = %d.\n", fd);
			}
			
			a) printf("文件打开错误\n"), 输出: 文件打开错误.
			
			b) (!!!!!) perror("文件打开错误"), 输出: 文件打开错误: File exists
			
			c) 设置0777, 然后ls -al 查看属性: -rwxr-xr-x 1 root root   12 Jul 17 12:14 a.txt
				这里的写在其他组加不上, 不知道原因. (?????)
			   (?????) 课程说, 在共享文件夹目录做实验, 查看文件属性不对. 需要在原生的ubuntu目录下.
			

	2. O_NONBLOCK, 阻塞与非阻塞
	
		1) 阻塞与非阻塞. 如果一个函数是阻塞式的, 则我们调用这个函数时当前进程有可能被卡住(阻塞住, 实质
		   是这个函数内部要完成的事情条件不具备, 当前没法做, 要等待条件成熟), 函数被阻塞住了就不能立刻
		   返回; 如果一个函数是非阻塞式的那么我们调用这个函数后一定会立即返回, 但是函数有没有完成任务
		   不一定.
		   
		2) 阻塞和非阻塞是两种不同的设计思路, 并没有好坏. 总的来说, 阻塞式的结果有保障但是时间没保障;
		   非阻塞式的时间有保障但是结果没保障.
		   
		3) 操作系统提供的API和由API封装而成的库函数, 有很多本身就是被设计为阻塞式或者非阻塞式的, 所以
		   我们应用程度调用这些函数的时候心里得非常清楚.
		   
		4) 我们打开一个文件默认就是阻塞式的, 如果你希望以非阻塞的方式打开文件, 则flag中要加
		   O_NONBLOCK标志.
		   
		5) (!!!!!!) 阻塞与非阻塞, 只用于设备文件, 而不用于普通文件.

	3. O_SYNC
	
		1) write阻塞等待底层完成写入才返回到应用层.
		
		2) 无O_SYNC时, write只是将内容写入'底层缓冲区'即可返回, 然后底层(操作系统中负责实现open、write
		   这些操作的那些代码, 也包含OS中读写硬盘等底层硬件的代码)在合适的时候会将buf中的内容一次性的
		   同步到硬盘中. 这种设计是为了提升硬件操作的性能和效率, 提升硬件寿命; 但是有时候我们希望硬件
		   不好等待, 直接将我们的内容写入硬盘中, 这时候就可以用O_SYNC标志.

//=======================================================================================================
								3.1.6.文件读写的一些细节
//-------------------------------------------------------------------------------------------------------
	1. errno和perror()函数
	
		1) errno就是error number, 意思就是错误号码. linux系统中对各种常见错误做了个编号, 当函数执行错误
		   时, 函数会返回一个特定的errno编号来告诉我们这个函数到底哪里错了.
		   
		2) errno是由OS来维护的一个全局变量, 任何OS内部函数都可以通过设置errno来告诉上层调用者究竟刚才发
		   生了一个什么错误.
		   
		3) errno本身实质是一个int类型的数字, 每个数字编号对应一种错误. 当我们只看errno时只能得到一个错
		   误编号数字(譬如-37), 不适应于人看.
		   
		4) linux系统提供了一个函数perror()(意思print error), perror函数内部会读取errno并且将这个不好认
		   的数字直接给转成对应的错误信息字符串, 然后print打印出来.

		举例: 
				perror("文件打开错误");		// 
				
				输出文件打开错误:  File exists ;   ":  File exists" 对应errno.

	2. read()和write()的count

		1) count和返回值的关系. count参数表示我们想要写或者读的字节数, 返回值表示实际完成的写或者读的
		   字节数. 实现的有可能等于想要读写的, 也有可能小于(说明没完成任务).
		   
		2) count再和阻塞非阻塞结合起来, 就会更加复杂. 如果一个函数是阻塞式的, 则我们要读取30个, 结果
		   暂时只有20个时就会被阻塞住, 等待剩余的10个可以读.
		   
		3) 有时候我们写正式程序时, 我们要读取或者写入的是一个很庞大的文件(譬如文件有2MB), 我们不可能
		   把count设置为2*1024*1024, 而应该去把count设置为一个合适的数字(譬如2048、4096), 然后通过多
		   次读取来实现全部读完.

	3. 文件IO效率和标准IO
	
		1) 文件IO就指的是我们当前在讲的open()、close()、write()、read()等API函数构成的一套用来读写文
		   件的体系, 这套体系可以很好的完成文件读写, 但是效率并不是最高的.
		   
		2) 应用层C语言库函数提供了一些用来做文件读写的函数列表, 叫标准IO. 标准IO由一系列的C库函数构成
		   (fopen()、fclose()、fwrite()、fread() ), 这些标准IO函数其实是由文件IO封装而来的(fopen内部
		   其实调用的还是open, fwrite内部还是通过write来完成文件写入的). 标准IO加了封装之后主要是为了
		   在应用层添加一个缓冲机制, 这样我们通过fwrite写入的内容不是直接进入内核中的buf, 而是先进入
		   应用层标准IO库自己维护的buf中, 然后标准IO库自己根据操作系统单次write的最佳count来选择好的
		   时机来完成write到内核中的buf(内核中的buf再根据硬盘的特性来选择好的实际去最终写入硬盘中).

		总结: 标准IO, 在应用层增加了缓冲, 这样就不用每次修改都用去修改OS的缓冲区, 提高了效率.
//=======================================================================================================
								3.1.7.linux系统如何管理文件
//-------------------------------------------------------------------------------------------------------
	1. 硬盘中的静态文件和inode(i节点)
	
		1) 文件平时都在存放在硬盘中的, 硬盘中存储的文件以一种固定的形式存放的, 我们叫静态文件.
		
		2) 一块硬盘中可以分为两大区域：一个是硬盘内容管理表项(哪一个文件, 在哪里存着呢, 包含几个扇区,几
		   块, 先从哪里找, 再在哪里找就能找全它); 另一个是真正存储内容的区域.
		   操作系统访问硬盘时是先去读取硬盘内容管理表, 从中找到我们要访问的那个文件的扇区级别的信息, 然
		   后再用这个信息去查询真正存储内容的区域, 最后得到我们要的文件.

		3) 操作系统最初拿到的信息是文件名, 最终得到的是文件内容. 
			
			a) 第一步就是去查询硬盘内容管理表, 这个管理表中以文件为单位记录了各个文件的各种信息, 每一个
			   文件有一个信息列表(我们叫inode, i节点, 其实质是一个结构体, 这个结构体有很多元素, 每个元
			   素记录了这个文件的一些信息, 其中就包括文件名、文件在硬盘上对应的扇区号、块号那些东西...).
			   
			   强调：硬盘管理的时候是以文件为单位的, 每个文件一个inode, 每个inode有一个数字编号, 对应一
			   个结构体, 结构体中记录了各种信息.
			   
		4) 联系平时实践, 大家格式化硬盘(U盘)时发现有：快速格式化和底层格式化. 快速格式化非常快, 格式化
		   一个32GB的U盘只要1秒钟, 普通格式化格式化速度慢. 这两个的差异? 其实快速格式化就是只删除了U盘
		   中的硬盘内容管理表(其实就是inode), 真正存储的内容没有动. 这种格式化的内容是有可能被找回的.

		总结: 文件存储的最小单位是扇区. 比如好多个很小的文件, 每个文件都需要占用一个扇区.

	2. 内存中被打开的文件和vnode(v节点)
	
		1) 一个程序的运行就是一个进程, 我们在程序中打开的文件就属于某个进程. 每个进程都有一个数据结构
		   用来记录这个进程的所有信息(叫'进程信息表'), 表中有一个指针会指向一个'文件管理表', '文件管理
		   表'中记录了当前进程打开的所有文件及其相关信息. 文件管理表中用来索引各个打开的文件的index就
		   是文件描述符fd, 我们最终找到的就是一个已经被打开的文件的管理结构体vnode.
		   
		2) 一个vnode中就记录了一个被打开的文件的各种信息, 而且我们只要知道这个文件的fd, 就可以很容易的
		   找到这个文件的vnode进而对这个文件进行各种操作.
		   
		总结:
				1) open()打开文件时, 就得到了fd.
				2) open()的时候, 系统内部做了什么呢?  
					打开文件, 在文件管理表中添加了一个表项, 表项的内容就是一个新构建的结构体vnode. 
					新表项对应一个标号, 就是fd返回给应用程序. 可以用这个fd进行文件的操作.

	3. 文件与流的概念
	
		1) 流(stream)对应自然界的水流. 文件操作中, 文件类似是一个大包裹, 里面装了一堆字符, 但是文件被
		   读出/写入时都只能一个字符一个字符的进行, 而不能一股脑儿的读写, 那么一个文件中N多的个字符被
		   挨个一次读出/写入时, 这些字符就构成了一个字符流.
		   
		2) 流这个概念是动态的, 不是静态的.
		
		3) 编程中提到流这个概念, 一般都是IO相关的. 所以经常叫IO流. 文件操作时就构成了一个IO流.

//=======================================================================================================
									3.1.8.lseek()详解
//-------------------------------------------------------------------------------------------------------
	1. lseek()函数介绍
	
		1) 文件指针：当我们要对一个文件进行读写时, 一定需要先打开这个文件, 所以我们读写的所有文件都是
		   动态文件. 动态文件在内存中的形态就是文件流的形式.
		   
		2) 文件流很长, 里面有很多个字节. 那我们当前正在操作的是哪个位置？ GUI模式下的软件用光标来标识
		   这个当前正在操作的位置, 这是给人看的.
		   
		3) 在动态文件中, 我们会通过文件指针来表征这个正在操作的位置. 所谓文件指针, 就是我们文件管理表
		   这个结构体里面的一个指针. 所以文件指针其实是vnode中的一个元素. 这个指针表示当前我们正在操作
		   文件流的哪个位置. 这个指针不能被直接访问, linux系统用lseek()函数来访问这个文件指针.
		   
		4) 当我们打开一个空文件时, 默认情况下文件指针指向文件流的开始. 所以这时候去write()时写入就是
		   从文件开头开始的. write()和read()函数本身自带移动文件指针的功能, 所以当我write了n个字节后,
		   文件指针会自动向后移动n位. 如果需要人为的随意更改文件指针, 那就只能通过lseek()函数了.
		   
		5) read()和write()函数都是从当前文件指针处开始操作的, 所以当我们用lseek()显式的将文件指针移动
		   后, 那么再去read()/write()时就是从移动过后的位置开始的.
		   
		6) 回顾前面一节中我们从空文件, 先write()写了12字节, 然后read时是空的(但是此时我们打开文件后发
		   现12字节确实写进来了).
		   
		   (!!!!!)写操作完成后, 文件指针是12. 因此这时候要读取, 就读取不到东西.

	2. lseek()函数介绍
		
		off_t lseek(int fd, off_t offset, int whence);
		
		1) whence:

			SEEK_SET
				  The offset is set to offset bytes.

			SEEK_CUR
				  The offset is set to its current location plus offset bytes.

			SEEK_END
				  The offset is set to the size of the file plus offset bytes.	
				  
		2) offset: 向后偏移.
		
		3) 返回: 
			returns the resulting offset location as measured in bytes from the beginning of the file.  
			On error, the value (off_t) -1 is returned and errno is set to indicate the error.
			
			(!!!!!)返回值是相对于文件开头的偏移值.
		
	3. 用lseek计算文件长度
	
		1) linux中并没有一个函数可以直接返回一个文件的长度. 但是我们做项目时经常会需要知道一个文件的
		   长度, 怎么办？自己利用lseek()来写一个函数得到文件长度即可.
		   
		2) 实现方法: 
		
			用lseek将文件指针移动到末尾, 然后返回值就是文件指针距离文件开头的偏移量, 也就是文件的长度了.
			ret = lseek(fd, 0, SEEK_END). 
		
		3) 实现代码:
		
			int main(int argc, char *argv[])
			{
				int fd = -1;							// fd 就是file descriptor，文件描述符
				int ret = -1;
				
				if (argc != 2)
				{
					printf("usage: %s filename\n", argv[0]);
					_exit(-1);
				}
				printf("文件长度是：%d字节\n", cal_len(argv[1]));
				return 0;
			}
			
			int cal_len(const char *pathname)
			{
				int fd = -1;		// fd 就是file descriptor，文件描述符
				int ret = -1;
				
				fd = open(pathname, O_RDONLY);

				if (-1 == fd)	
				{
					perror("文件打开错误");
					return -1;
				}

				ret = lseek(fd, 0, SEEK_END);		// 
				return ret;
			}			

	4. 用lseek构建空洞文件
	
		1) 空洞文件就是这个文件中有一段是空的.
		
		2) 普通文件中间是不能有空的, 因为我们write时文件指针是依次从前到后去移动的, 不可能绕过前面直接
		   到后面.
		   
		3) 我们打开一个文件后, 用lseek往后跳过一段, 再write写入一段, 就会构成一个空洞文件.
		
			ret = lseek(fd, 100, SEEK_SET);
			ret = write(fd, writebuf, strlen(writebuf));
		
		4) 空洞文件方法对多线程共同操作文件是及其有用的. 有时候我们创建一个很大的文件, 如果从头开始依
		   次构建时间很长. 有一种思路就是将文件分为多段, 然后多线程来操作每个线程负责其中一段的写入.

//=======================================================================================================
								3.1.9.多次打开同一文件与O_APPEND
//-------------------------------------------------------------------------------------------------------
	文件共享的一些内容: 多次打开同一文件与O_APPEND
//--------------------------------------------------------
	1. 重复打开同一文件'读取'
	
		1) 一个进程中两次打开同一个文件, 然后分别读取, 看结果会怎么样.
		
		2) 结果无非2种情况：一种是fd1和fd2分别读, 第二种是接续读. 经过实验验证, 证明了结果是fd1和fd2
		   分别读.
		   
		3) 分别读说明：我们使用open两次打开同一个文件时, fd1和fd2所对应的文件指针是不同的2个独立的指针.
		   文件指针是包含在动态文件的文件管理表中的, 所以可以看出linux系统的进程中不同fd对应的是不同的
		   独立的文件管理表项.
		
		总结:
				普通文件是可以重复打开的.
				
	2. 重复打开同一文件'写入'
	
		1) 一个进程中2个打开同一个文件, 得到fd1和fd2. 然后看是分别写还是接续写？
		
		2) 正常情况下我们有时候需要分别写, 有时候又需要接续写, 所以这两种本身是没有好坏之分的. 关键看
		   用户需求.
		
		3) 默认情况下(不用O_APPEND打开文件)是：分别写(实验验证)
		
			fd1 = open("a.txt", O_RDWR | O_TRUNC | O_CREAT, 0666);

	3. 加O_APPEND解决覆盖问题
	
		fd1 = open("a.txt", O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0666);
	
		1) 有时候我们希望接续写而不是分别写？办法就是在open时加O_APPEND标志即可.
		
		2) O_APPEND, 以追加的方式打开文件, 打开后文件指针指向文件末尾.

	4. O_APPEND的实现原理和其原子操作性说明
	
		1) O_APPEND为什么能够将分别写改为接续写？
		
		   关键的核心的东西是文件指针. 分别写的内部原理就是2个 fd拥有不同的文件指针, 并且彼此只考虑
		   自己的位移. 
		   
		   但是O_APPEND标志可以让write()和read()函数内部多做一件事情, 就是移动自己的文件指针的同时也
		   去把别人的文件指针同时移动. (也就是说即使加了O_APPEND, fd1和fd2还是各自拥有一个独立的文件
		   指针.  但是这两个文件指针关联起来了, 一个动了会通知另一个跟着动).
		   
		2) O_APPEND对文件指针的影响, 对文件的读写是原子的.
		
		3) 原子操作的含义是：整个操作一旦开始是'不会被打断'的, 必须直到操作结束其他代码才能得以调度
		   运行, 这就叫原子操作. 非原子操作, 可以被任务调度器打断. 每种操作系统中都有一些机制来实现
		   原子操作, 以保证那些需要原子操作的任务可以运行.

		总结(?????) 
				1) O_APPEND 文件打开时, 使文件指针指向末尾.
				2) (????) 对于多次打开的一个文件, O_APPEND还可以使 fd1和fd2还是各自的文件指针关联起来?

//=======================================================================================================
								3.1.10.文件共享的实现方式
//-------------------------------------------------------------------------------------------------------
	1. 什么是文件共享
	
		1) 文件共享就是'同一个文件'(同一个文件指的是同一个inode, 同一个pathname)被多个独立的读写体(几乎
		   可以理解为多个文件描述符)去同时操作(一个打开尚未关闭的同时另一个去操作）.
		   
		2) 文件共享的意义有很多：譬如我们可以通过文件共享来实现多线程同时操作同一个大文件, 以减少文件
		   读写时间, 提升效率.

		(????) 硬链接, 短链接时. 打开是不是同一个文件????  (需要写程序验证一下).

	2. 文件共享的3种实现方式
	
		1) 文件共享的核心就是怎么弄出来多个文件描述符指向同一个文件.
		
		2) 常见的有3种文件共享的情况：
		
			第一种, 是同一个进程中多次使用open()打开同一个文件.
			第二种, 是在不同进程中去分别使用open()打开同一个文件(这时候因为两个fd在不同的进程中, 所以
			        两个fd的数字可以相同也可以不同).
			第三种, 是后面要学的, linux系统提供了dup和dup2两个API来让进程复制文件描述符.
		
			总结:
					第一种情况, fd1,fd2分别对应一个文件表, 可以是分别写, 或者接续写(O_APPEND).
					第二种情况, fd1,fd2分别对应一个文件表, 可以是分别写, 或者接续写(O_APPEND).
					第三中情况, fd1,fd2对应同一个文件表, 不能分别写, 只能接续写.
		
		3) 我们分析文件共享时的核心关注点在于：分别写/读, 还是接续写/读?

	3. 再论文件描述符
	
		1) 文件描述符的本质是一个数字, 这个数字本质上是进程表中文件描述符表的一个表项, 进程通过文件描
		   述符作为index去索引查表得到文件表指针, 再间接访问得到这个文件对应的文件表.
		   
		2) 文件描述符这个数字是open()系统调用内部由操作系统自动分配的, 操作系统分配这个fd时也不是随意
		   分配, 也是遵照一定的规律的, 我们现在就要研究这个规律.
		   
		3) 操作系统规定, fd从0开始依次增加. fd也是有最大限制的, 在linux的早期版本中(0.11)fd最大是20,
		   所以当时一个进程最多允许打开20个文件. linux中文件描述符表是个数组(不是链表), 所以这个文件
		   描述符表其实就是一个数组, fd是index, 文件表指针是value.
		   
		4) 当我们去open时, 内核会从文件描述符表中挑选一个最小的未被使用的数字给我们返回. 也就是说如果
		   之前fd已经占满了0-9, 那么我们下次open得到的一定是10.(但是如果上一个fd得到的是9, 下一个不一
		   定是10, 这是因为可能前面更小的一个fd已经被close释放掉了).

		5) fd中0、1、2已经默认被系统占用了, 因此用户进程得到的最小的fd就是3了.

		6) linux内核占用了0、1、2这三个fd是有用的, 当我们运行一个程序得到一个进程时, 内部就默认已经打
		   开了3个文件, 这三个文件对应的fd就是0、1、2. 这三个文件分别叫stdin、stdout、stderr. 也就是
		   标准输入、标准输出、标准错误.
		   
		7) 标准输入一般对应的是键盘(可以理解为：0这个fd对应的是键盘的设备文件), 标准输出一般是LCD显示
		   器(可以理解为：1对应LCD的设备文件).
		   
		8) printf函数其实就是默认输出到标准输出stdout上了. stdio中还有一个函数叫fpirntf, 这个函数就
		   可以指定输出到哪个文件描述符中.
		
		总结: (!!!!!)
				printf() 	-> 		输出到 标准输出stdout.
				fpirntf()	-> 		输出到 指定的文件描述符中.

//=======================================================================================================
								3.1.11.文件描述符的复制1
//-------------------------------------------------------------------------------------------------------
	1. dup()和dup2()函数介绍
	
       int dup(int oldfd);					// 返回文件描述符是系统自动分配的
       int dup2(int oldfd, int newfd);		// 正确时, 返回文件描述符就是指定的 newfd; 否则返回 -1.
	
	2. 使用dup进行文件描述符复制
	
		1) dup系统调用对fd进行复制, 会返回一个新的文件描述符(譬如原来的fd是3, 返回的就是4).
		
		2) dup系统调用有一个特点, 就是自己不能指定复制后得到的fd的数字是多少, 而是由操作系统内部自动
		   分配的, 分配的原则遵守fd分配的原则.
		   
		3) dup返回的fd和原来的oldfd都指向oldfd打开的那个动态文件, 操作这两个fd实际操作的都是oldfd打开
		   的那个文件. 实际上构成了文件共享.
		   
		4) dup返回的fd和原来的oldfd同时向一个文件写入时, 结果是分别写还是接续写？

	3. 使用dup的缺陷分析
	
		1) dup并不能指定分配的新的文件描述符的数字, dup2系统调用修复了这个缺陷, 所以平时项目中实际使
		   用时根据具体情况来决定用dup还是dup2.
		   

	4. 练习
	
		1) 之前课程讲过0、1、2这三个fd被标准输入、输出、错误通道占用. 而且我们可以关闭这三个.
		
		2) 我们可以close(1)关闭标准输出, 关闭后我们printf()输出到标准输出的内容就看不到了.
		
		3) 然后我们可以使用dup重新分配得到1这个fd, 这时候就把oldfd打开的这个文件和 1 这个标准输出通道
		   给绑定起来了. 这就叫'标准输出'的'重定位'.
		   
		4) 可以看出, 我们可以使用close()和dup()配合进行文件的重定位.

			#define FILENAME	"1.txt"


			int main(void)
			{
				int fd1 = -1, fd2 = -1;
				
				fd1 = open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (fd1 < 0)				// O_CREAT, 不存在就建立;  O_TRUNC, 文件存在就截断(!!!!!).
				{
					perror("open");
					return -1;
				}
				printf("fd1 = %d.\n", fd1);
				
				close(1);			// 1就是标准输出stdout
				
				
											// 复制文件描述符
				fd2 = dup(fd1);				// fd2一定等于1，因为前面刚刚关闭了1, 这句话就把
											// 1.txt文件和标准输出就绑定起来了, 所以以后输出到标准输出
											// 的信息就可以到1.txt中查看了.
				printf("fd2 = %d.\n", fd2);
				printf("this is for test");
				
				close(fd1);
				return -1;
			}
			
			总结: 标准输出关闭, 可以重定向到一个文件中.  程序中的printf()打印的信息会到文件中.

//=======================================================================================================
								3.1.12.文件描述符的复制2
//-------------------------------------------------------------------------------------------------------
	1. 使用dup2()进行文件描述符复制
	
		1) dup2和dup的作用是一样的, 都是复制一个新的文件描述符. 但是dup2允许用户指定新的文件描述符的
		   数字.
		   
		2) 使用方法看man手册函数原型即可.
		
			int dup2(int oldfd, int newfd);	 
			
			成功时, 返回文件描述符就是指定的 newfd; 否则返回 -1.

	2. dup2共享文件交叉写入测试
	
		1) dup2复制的文件描述符, 和原来的文件描述符虽然数字不一样, 但是这两个指向同一个打开的文件.
		
		2) 交叉写入的时候, 结果是接续写(实验证明).

	3. 命令行中 "重定位命令" ">"
	
		1) linux中的shell命令执行后, printf()打印结果都是默认进入stdout的(本质上是因为这些命令譬如
		   ls、pwd等都是调用printf()进行打印的), 所以我们可以在linux的终端shell中直接看到命令执行的
		   结果.
		   
		2) 能否想办法把ls、pwd等命令的输出给重定位到一个文件中(譬如2.txt)去, 实际上linux终端支持一个
		   重定位的符号 > 很简单可以做到这点.
		   
		3) 这个 '>' 的实现原理, 其实就是利用 open + close + dup, open打开一个文件2.txt，然后close关闭
		   stdout, 然后dup将 '1' 和 2.txt 文件关联起来即可.

		   应用: tree > 2.txt

//=======================================================================================================
								3.1.13.fcntl()函数介绍
//-------------------------------------------------------------------------------------------------------
	1. fcntl()的原型和作用
	
		int fcntl(int fd, int cmd, ... /* arg */ );		/*
	
		1) fcntl函数是一个'多功能文件管理的工具箱', 接收2个参数+1个变参. 第一个参数是fd表示要操作哪个文
		   件, 第二个参数是cmd表示要进行哪个命令操作. 变参是用来传递参数的, 要配合cmd来使用.
		   
		2) cmd的样子类似于F_XXX, 不同的cmd具有不同的功能. 学习时没必要去把所有的cmd的含义都弄清楚(也记
		   不住), 只需要弄明白一个作为案例, 搞清楚它怎么看怎么用就行了, 其他的是类似的. 其他的当我们在
		   使用中碰到了一个fcntl()的不认识的cmd时再去查man手册即可. 

	2. fcntl的常用cmd
	
		1) F_DUPFD 这个cmd的作用是复制文件描述符(作用类似于dup和dup2), 这个命令的功能是从可用的fd数字
		   列表中找一个比arg大或者和arg一样大的数字作为oldfd的一个复制的fd, 和dup2有点像但是不同. 
		   dup2返回的就是我们指定的那个newfd否则就会出错, 但是F_DUPFD命令返回的是>=arg的最小的那一个
		   数字.

	3. 使用fcntl模拟dup2

		close(1);							// 关闭标准输出
		
		fd2 = fcntl(fd1, F_DUPFD, 0);		// >=0的文件描述符
		printf("fd2 = %d.\n", fd2);			// fd2等于1

//=======================================================================================================
								3.1.14.标准IO库介绍
//-------------------------------------------------------------------------------------------------------
	1. "标准IO"和"文件IO"有什么区别
	
		1) 看起来使用时都是函数, 但是：标准IO是C库函数, 而文件IO是linux系统的API.
		
		2) C语言库函数是由API封装而来的. 库函数内部也是通过调用API来完成操作的, 但是库函数因为多了一层
		   封装, 所以比API要更加好用一些.
		   
		3) 库函数比API还有一个优势就是：API在不同的操作系统之间是不能通用的(不如linux和windows), 但是
		   C库函数在不同操作系统中几乎是一样的. 所以C库函数具有可移植性而API不具有可移植性.
		   
		4) 性能上和易用性上看, C库函数一般要好一些. 譬如IO, 文件IO是不带缓存的, 而标准IO是带缓存的, 
		   因此标准IO比文件IO性能要更高。

	2. 常用标准IO函数介绍
		
		1) 常见的标准IO库函数有：fopen、fclose、fwrite、fread、fflush、fseek.
		
		2) fflush, 把缓冲区的内容写一次(即便缓冲区没有满).
		
		3) 
			FILE *fopen(const char *path, const char *mode);	// fopen()返回一个FILE类型的指针.
			
			r+, w+ .... 查阅man手册, 或者网络搜索.
			
			size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
									// writes nmemb elements of data, each size bytes long.
									// 返回值就是写入的数量, 对应nmemb. 
									
			size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

		
	3. 一个简单的标准IO读写文件实例
		
		#define FILENAME	"1.txt"

		int main(void)
		{
			FILE *fp = NULL;
			size_t len = -1;
			//int array[10] = {1, 2, 3, 4, 5};
			char buf[100] = {0};
			
			fp = fopen(FILENAME, "r+");
			if (NULL == fp)
			{
				perror("fopen");
				exit(-1);
			}
			printf("fopen success. fp = %p.\n", fp);
			
			// 在这里去读写文件
			memset(buf, 0, sizeof(buf));
			len = fread(buf, 1, 10, fp);
			printf("len = %d.\n", len);
			printf("buf is: [%s].\n", buf);

			fp = fopen(FILENAME, "w+");
			if (NULL == fp)
			{
				perror("fopen");
				exit(-1);
			}
			printf("fopen success. fp = %p.\n", fp);
			
			// 在这里去读写文件
			//len = fwrite("abcde", 1, 5, fp);
			//len = fwrite(array, sizeof(int), sizeof(array)/sizeof(array[0]), fp);
			len = fwrite(array, 4, 10, fp);
			printf("len = %d.\n", len);
			
			fclose(fp);
			return 0;
		}
		
		1) 打开一个文件
		
			FILE *fp = NULL;				// FILE 类型的指针, 不是文件描述符
			
			fp = fopen(FILENAME, "r+");		// r+  Open  for  reading and writing.  The stream is 
											// positioned at the beginning of the file.
			
			if (NULL == fp)					// 与NULL比较
			{
				perror("fopen");			// perror()
				exit(-1);
			}
			printf("fopen success. fp = %p.\n", fp);
			
		2) 写入数据
		
			len = fwrite(array, 4, 10, fp);	
			len = fwrite(array, sizeof(int), sizeof(array)/sizeof(array[0]), fp);
			
		3) 读出数据
		
			memset(buf, 0, sizeof(buf));
			len = fread(buf, 1, 10, fp);	

//=======================================================================================================












