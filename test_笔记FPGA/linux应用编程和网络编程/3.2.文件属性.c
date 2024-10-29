/*
//=======================================================================================================
										3.2.文件属性
//=======================================================================================================
3.2.1.linux中各种文件类型
3.2.2.常用文件属性获取
3.2.3.stat函数的应用案例
3.2.4.文件权限管理1
3.2.5.文件权限管理2
3.2.6.读取目录文件
//=======================================================================================================
3.2.1.linux中各种文件类型
	本节介绍linux中各种文件类型, 其中重点讲解了文本文件和二进制文件这两种普通文件.
3.2.2.常用文件属性获取
	本节介绍stat函数族及其如何获取文件属性结构体, 并且用一个简单实例获取了一些文件属性作为验证.
3.2.3.stat函数的应用案例
	本节使用stat函数获取文件文件属性后, 使用linux系统的宏来获取文件类型和文件读写权限信息.
3.2.4.文件权限管理1
	本节重点讲解文件操作时权限检查和判定的规则, 然后引入了access函数来检测文件是否具有某种可访问权限.
3.2.5.文件权限管理2
	本节介绍chmod接口来更改文件权限、chown接口来更改文件属主、umask接口来修改系统默认权限掩码.
3.2.6.读取目录文件
	本节为实战课, 写代码实现读取文件目录, 并且将目录中的文件属性和文件名列出来, 以后的很多项目中都会用
	到这个功能.
//=======================================================================================================

	(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
		本节实验涉及到文件权限, 不能在共享文件夹中实验. 要在ubuntu中建立一个原生目录.
	(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//=======================================================================================================
								3.2.1.linux中各种文件类型
//-------------------------------------------------------------------------------------------------------
	1. 普通文件 ( -	regular file)
		
		1) 文本文件. 文件中的内容是由文本构成的, 文本指的是ASCII码字符. 文件里的内容本质上都是数字(不管
		   什么文件内容本质上都是数字, 因为计算机中本身就只有1和0), 而文本文件中的数字本身应该被理解为
		   这个数字对应的ASCII码. 常见的.c文件, .h文件, .txt文件等都是文本文件. 文本文件的好处就是可以
		   被人轻松读懂和编写. 所以说文本文件天生就是为人类发明的.
		   
		2) 二进制文件. 二进制文件中存储的本质上也是数字, 只不过这些数字并不是文字的编码数字, 而是就是真
		   正的数字. 常见的可执行程序文件(gcc编译生成的a.out, arm-linux-gcc编译连接生成的.bin)都是二进
		   制文件.
		
		3) 对比：从本质上来看(就是刨除文件属性和内容的理解)文本文件和二进制文件并没有任何区别. 都是一个
		   文件里面存放了数字. 区别是理解方式不同, 如果把这些数字就当作数字处理则就是二进制文件, 如果把
		   这些数字按照某种编码格式去解码成文本字符, 则就是文本文件.
		   
		4) 我们如何知道一个文件是文件文件还是二进制文件？ 在linux系统层面是不区分这两个的(譬如之前学过
		   的open、read、write等方法操作文件文件和二进制文件时一点区别都没有), 所以我们无法从文件本身
		   准确知道文件属于哪种, 我们只能本来就知道这个文件的类型然后用这种类型的用法去用他. 有时候会
		   用一些后缀名来人为的标记文件的类型.
		   
		5) 使用文本文件时, 常规用法就是用文本文件编辑器去打开它、编辑它. 常见的文本文件编辑器如vim、
		   gedit、notepad++、SourceInsight等, 我们用这些文本文件编辑器去打开文件的时候, 编辑器会read
		   读出文件二进制数字内容, 然后按照编码格式去解码将其还原成文字展现给我们. 如果用文本文件编辑
		   器去打开一个二进制文件会如何？ 这时候编辑器就以为这个二进制文件还是文本文件然后试图去将其解
		   码成文字, 但是解码过程很多数字并不对应有意义的文字所以成了乱码.
		   
		6) 反过来用二进制阅读工具去读取文本文件会怎么样？得出的就是文本文字所对应的二进制的编码.

	2. 目录文件( d	directory)

		1) 目录就是文件夹, 文件夹在linux中也是一种文件, 不过是特殊文件. 用vi打开一个文件夹就能看到, 
		   文件夹其实也是一种特殊文件, 里面存的内容包括这个文件的路径, 还有文件夹里面的文件列表.
		   
		2) 但是文件夹这种文件比较特殊, 本身并不适合用普通的方式来读写. linux中是使用特殊的一些API来
		   专门读写文件夹的.
		
		3) vim 3.1.9  // 打开一个目录文件:
		
			" ============================================================================                                        
			" Netrw Directory Listing                                        (netrw v149)
			"   /mnt/hgfs/win_share/software/3/1.fileio/3.1.9
			"   Sorted by      name
			"   Sort sequence: [\/]$,\<core\%(\.\d\+\)\=\>,\.h$,\.c$,\.cpp$,\~\=\*$,*,\.o$,\.obj$,
																\.info$,\.swp$,\.bak$,\~$
			"   Quick Help: <F1>:help  -:go up dir  D:delete  R:rename  s:sort-by  x:exec
			" ============================================================================
			../
			./
			.swp*
			a.out*
			a.txt*
			file.c*
			file2.c*
		
	3. 字符设备文件( c	character)
	4. 块设备文件  ( b	block)
	
		1) 设备文件对应的是硬件设备, 也就是说这个文件虽然在文件系统中存在, 但是并不是真正存在于硬盘上
		   的一个文件, 而是文件系统虚拟制造出来的(叫虚拟文件系统, 如/dev /sys /proc等).
		   
		2) 虚拟文件系统中的文件大多数不能或者说不用直接读写的, 而是用一些特殊的API产生或者使用的, 具体
		   在驱动阶段会详解.

	5. 管道文件( p 	pipe)
	
		linux中的一种通信手段, 如果用管道通信, 就需要创建一个管道文件.
	
	6. 套接字文件( s	socket)
	7. 符号链接文件( l	link)

//=======================================================================================================
								3.2.2.常用文件属性获取
//-------------------------------------------------------------------------------------------------------
	1. stat()、fstat()、lstat()函数简介
	
		1) 每个文件中都附带了这个文件的一些属性(属性信息是存在于文件本身中的, 但是它不像文件的内容一样
		   可以被vi打开看到, 属性信息只能被专用的API打开看到).
		   
		2) 文件属性信息查看的API有三个：stat()、fstat()、lstat(), 三个作用一样, 参数不同, 细节略有不同.
		
		3) linux命令行下还可以去用stat命令去查看文件属性信息, 实际上stat命令内部就是使用stat()系统调用
		   API来实现的.
		   
		4) stat这个API的作用就是让内核将我们要查找属性的文件的属性信息结构体的值放入我们传递给stat()函
		   数的buf中, 当stat这个API调用从内核返回的时候buf中就被填充了文件的正确的属性信息, 然后我们通
		   过查看buf这种结构体变量的元素就可以得知这个文件的各种属性了.
		   
		5) fstat和stat的区别是：stat是从文件名出发得到文件属性信息结构体, 而fstat是从一个已经打开的文件
		   fd出发得到一个文件的属性信息. 所以用的时候如果文件没有打开(我们并不想打开文件操作而只是希望
		   得到文件属性)那就用stat, 如果文件已经被打开了然后要属性那就用fstat效率会更高(stat是从磁盘去
		   读取文件的, 而fstat是从内存读取动态文件的).
		   
		6) lstat和stat/fstat的差别在于：对于符号链接文件, stat和fstat查阅的是符号链接文件指向的文件的
		   属性, 而lstat查阅的是符号链接文件本身的属性.

		总结:
				1) linux命令行有stat命令, 查看用法: man 1 stat. 
				
					stat - display file or file system status
					
				2) 命令行中查看a.out文件信息: stat a.out
					
					  File: ‘a.out’
					  Size: 7295      	Blocks: 0          IO Block: 1024   regular file
					Device: 1ah/26d	Inode: 132         Links: 1
					Access: (0777/-rwxrwxrwx)  Uid: (    0/    root)   Gid: (    0/    root)
					Access: 2023-07-18 08:25:36.207199400 +0800
					Modify: 2023-07-18 08:25:36.207199400 +0800
					Change: 2023-07-18 08:25:36.207199400 +0800
					 Birth: -
					 
				3) 	使用系统调用API stat()函数, 查看用法: man 2 stat
				
				
				   #include <sys/types.h>
				   #include <sys/stat.h>
				   #include <unistd.h>

				   int stat(const char *path, struct stat *buf);
				   int fstat(int fd, struct stat *buf);
				   int lstat(const char *path, struct stat *buf);
				   
				   a) const char *path; 说明这个指针执行的内容不需要改变.
				   b) struct stat *buf; 没有加const , 说明指针指向的内容需要做改变, 即是输出型参数.
			
	2. struct stat结构体简介
	
	        struct stat {
               dev_t     st_dev;     /* ID of device containing file */
               ino_t     st_ino;     /* inode number */
               mode_t    st_mode;    /* protection */
               nlink_t   st_nlink;   /* number of hard links */
               uid_t     st_uid;     /* user ID of owner */
               gid_t     st_gid;     /* group ID of owner */
               dev_t     st_rdev;    /* device ID (if special file) */
               off_t     st_size;    /* total size, in bytes */
               blksize_t st_blksize; /* blocksize for filesystem I/O */
               blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
               time_t    st_atime;   /* time of last access */
               time_t    st_mtime;   /* time of last modification */
               time_t    st_ctime;   /* time of last status change */
           };	/*

	
		1) struct stat是内核定义的一个结构体，在<sys/stat.h>中声明，所以我们可以用。这个结构体中的所有元素加起来就是我们的文件属性信息。

		2) st_uid, st_gid 都是数字. 上一节的文件信息:
			Access: (0777/-rwxrwxrwx)  Uid: (    0/    root)   Gid: (    0/    root)
			/root 用户的ID就是0.
		3) st_rdev: 特殊文件才使用, 普通文件用不到.
		4) st_mtime: modification, 内容的修改.
		   st_ctime: status change, 改变了文件的属性, 比如可读可写可执行等.
			
	3. 写个程序来查看一些常见属性信息
		
		#include <stdio.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <unistd.h>
		#include <string.h>
		#include <stdlib.h>


		#define NAME "1.txt"

		int main(void)
		{
			int ret = -1;
			struct stat buf;
			
			memset(&buf, 0, sizeof(buf));		// memset后buf中全是0
			ret = stat(NAME, &buf);				// stat后buf中有内容了
			if (ret < 0)
			{
				perror("stat");
				exit(-1);
			}
			// 成功获取了stat结构体，从中可以得到各种属性信息了
			printf("inode = %d.\n", buf.st_ino);
			printf("size = %d bytes.\n", buf.st_size);
			printf("st_blksize = %d.\n", buf.st_blksize);
			
			return 0;
		}		
		
		总结: 
				1) 定义了一个结构体变量buf, 初始化为0有两种方法:
					a) struct stat buf = {0};
									// 课程说"利用GCC的一种特殊手法...."
					b) memset(&buf, 0, sizeof(buf));
					
				2) 可以通过查阅使用的函数的man手册查到所有需要包含的头文件.	

//=======================================================================================================
								3.2.3.stat函数的应用案例
//-------------------------------------------------------------------------------------------------------
	1. 用代码判断文件类型
	
		1) 文件类型就是-、d、l···
		
		2) 文件属性中的文件类型标志在struct stat结构体的 mode_t  st_mode元素中, 这个元素其实是一个按位
		   来定义的一个位标志(有点类似于ARM CPU的CPSR寄存器的模式位定义). 这个东西有很多个标志位共同构
		   成, 记录了很多信息, 如果要查找时按位&操作就知道结果了, 但是因为这些位定义不容易记住, 因此
		   linux系统给大家事先定义好了很多宏来进行相应操作.
		   
		3) 譬如 S_ISREG 宏返回值是1表示这个文件是一个普通文件, 如果文件不是普通文件则返回值是0.

           S_ISREG(m)  is it a regular file?
           S_ISDIR(m)  directory?
           S_ISCHR(m)  character device?
           S_ISBLK(m)  block device?
           S_ISFIFO(m) FIFO (named pipe)?
           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

		4) 程序判断:
		
			result = S_ISREG(buf.st_mode);			// result=1, 说明是普通文件.
			
			
	2. 用代码判断文件权限设置
	
		1) st_mode中除了记录了文件类型之外, 还记录了一个重要信息：文件权限.
		
		2) linux并没有给文件权限测试提供宏操作, 而只是提供了位掩码. 所以我们只能用位掩码来自己判断是否
		   具有相应权限.
	
           S_IRUSR    00400     owner has read permission			// 
           S_IWUSR    00200     owner has write permission
           S_IXUSR    00100     owner has execute permission		
           S_IRWXG    00070     mask for group permissions
           S_IRGRP    00040     group has read permission
           S_IWGRP    00020     group has write permission
           S_IXGRP    00010     group has execute permission
           S_IRWXO    00007     mask for permissions for others (not in group)
           S_IROTH    00004     others have read permission
           S_IWOTH    00002     others have write permission
           S_IXOTH    00001     others have execute permission
		
		3) 判断文件是否可读
		
			unsigned int result = ((buf.st_mode & S_IRUSR)? 1: 0);
			printf("file owner: %u.\n", result);

			总结:
					命令行的ls -l 命令, 也是通过这种方式通过系统调用API实现的.
					
//=======================================================================================================
								3.2.4.文件权限管理1
//-------------------------------------------------------------------------------------------------------
	1. st_mode中记录的文件权限位
	
		1) st_mode本质上是一个32位的数(类型就是unsinged int), 这个数里的每一个位表示一个含义.
		
		2) 文件类型和文件的权限都记录在st_mode中. 我们用的时候使用专门的掩码去取出相应的位即可得知相应
		   的信息。
		   
           S_IFMT     0170000   bit mask for the file type bit fields	// 4个bite位表示文件类型.
           S_IFSOCK   0140000   socket									// 文件类型-socket
           S_IFLNK    0120000   symbolic link
           S_IFREG    0100000   regular file
           S_IFBLK    0060000   block device
           S_IFDIR    0040000   directory
           S_IFCHR    0020000   character device
           S_IFIFO    0010000   FIFO
		   
	2. ls -l打印出的权限列表
	
		-rwxrwxrwx 1 root root   21 Mar  2  2016 1.txt

		1) 123456789 一共9位, 3个一组. 
			第一组三个表示文件的属主(owner或user)对该文件的可读、可写、可执行权限.
			第二组三个位表示文件的属主所在的组(group)对该文件的权限.
			第三组三个位表示其他用户(others)对该文件的权限.
			
		2) 属主就是这个文件属于谁, 一般来说文件创建时属主就是创建这个文件的那个用户. 但是我们一个文件
		   创建之后还可以用"chown命令"去修改一个文件的属主, 还可以用"chgrp命令"去修改一个文件所在的组.
		   
		   
		3) 第一个root表示当前用于, 第二个用户表示所在组.  ?????? 

	3. 文件操作时的权限检查规则
	
		1) 一个程序a.out被执行, a.out中试图去操作一个文件1.txt, 这时候如何判定a.out是否具有对1.txt的
		   某种操作权限呢？
		   
		2) 判定方法是：首先 1.txt具有9个权限位, 规定了3种人(user、group、others)对该文件的操作权限. 
		               所以我们判定 1.txt 是否能被a.out来操作, 关键先搞清楚 a.out 对 1.txt到底算哪种人.
					   准确的说是看 a.out 被谁执行(不是看a.out本身), 也就是当前程序(进程)是哪个用户的
					   进程.
			总结:
					1) 在aston用户下, 创建一个文件 /home/aston/test.c
						ls -l 查看:
						
						-rw-rw-r--  1 aston aston     0 Jul 18 20:58 test.c
						
					2) 	在root用户下, cp /home/aston/test.c ~/
						然后ls -l 查看:
						
						-rw-r--r-- 1 root root         0 Jul 18 20:59 test.c

					3) 	在root用户下, cp -p /home/aston/test.c ~/ 
					
						(!!!!!) -p     same as --preserve=mode,ownership,timestamps

						这样ls -l 查看:
						
						-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 test.c
						
					4) (!!!!!!??????) 课程中说道:
					
						-rw-r--r-- 1 root  root          0 Jul 18 20:59 1.txt
						-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 2.txt

						-rwxr-xr-x 1 root  root       5733 Apr 25 12:30 a.out
						
						假如root用户去执行a.out程序, 然后操作2.txt. 然后2.txt文件的用户和所在组都是aston,
						那对于2.txt来说, root用户就是其他用户(others), 有没有权限看2.txt第三组的三个位.
						
						(×)假如root用户去执行a.out程序, 然后操作1.txt. 执行程序的root用户就是其属主用户
						(user), 有没有操作权限, 看1.txt第一组的三个位.
						
						(!!!???) root 用户时特权用户, 这里表述不对. 
						         如果新建一个用户 addusr tempusr.  这相对于1.txt就是其他用户.
								 
				(?????) 用户, 用户组等概念理解还有问题, 有时间需要深入了解.
						
		3) 刚才上面说的是我的分析, 到底对不对还得验证.
		
			#define NAME "1.txt"

			int main(void)
			{
				int ret = -1;
				
				ret = open(NAME, O_RDONLY);
				if (ret > 0)
				{
					printf("可读  	");
					close(ret);
					
				}
				else
				{
					perror("read");
				}
				

				ret = open(NAME, O_WRONLY);
				if (ret > 0)
				{
					printf("可写  	");
					close(ret);
				}
				else
					perror("write");
				
				return 0;
			}

//=======================================================================================================
								3.2.5.文件权限管理2
//-------------------------------------------------------------------------------------------------------
	1. access()函数检查权限设置
	
		1) 文本权限管控其实蛮复杂, 一般很难很容易的确定对一个文件是否具有某种权限(有没有权限除了跟文件
		   本身有关系, 还与谁去执行有关系). 设计优秀的软件应该是：在操作某个文件之前先判断当前是否有
		   权限做这个操作, 如果有再做如果没有则提供错误信息给用户.
		   
		2) access()函数可以测试得到当前执行程序的那个用户在当前那个环境下对目标文件是否具有某种操作
		   权限.

			int access(const char *pathname, int mode);
		
			F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists 
			and grants read, write, and execute  permissions.
			
			int fchmod(int fd, mode_t mode);


		3) 测试:
		
			#define NAME 	"3.txt"
			
			ret = access(NAME, F_OK);
			if (ret < 0)
			{
				printf("文件不存在 \n");
				return -1;
			}
			else
			{
				printf("文件存在	");
			}

			ret = access(NAME, R_OK);
			if (ret < 0)
			{
				printf("不可读 ");
			}
			else
			{
				printf("可读 ");
			}			
		
		总结: 程序中操作一个文件时, 一定要用acess()函数去测试一下是否存在, 是否有权限.

	2. chmod/fchmod与权限修改
	
		1) chmod是一个linux命令, 用来修改文件的各种权限属性. chmod命令只有root用户才有权利去执行修改.
		
			(!!!!!!)对于一个文件, 其user用户可以使用chmod命令.
			root用户可以修改所有的文件. 其他用户只能修改自己的文件.
			
		2) chmod命令其实内部是用linux的一个叫chmod的API实现的.
		
			man 1 chmod			// 查阅的是命令行命令
			man 2 chmod			// 查阅的是系统调用API的chmod()函数.

		3) 应用:
			int main(int argc, char **argv)
			{
				int ret = -1;
				
				
				if (argc != 2)
				{
					printf("usage: %s filename\n", argv[0]);
					return -1;
				}
				
				ret = chmod(argv[1], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWOTH);
				if (ret < 0)
				{
					perror("chmod");
					return -1;
				}
				
				return 0;
			}
			
			S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWOTH	// user用户可读可写可执行, 组用户可读, 
															// 其他用户可写
															
		4) 	fchmod(): 对于一个打开的文件, 可以通过fd使用这个函数.
		
	3. chown/fchown/lchown与属主修改
	
		1) linux中有个chown命令来修改文件属主.
		
		2) chown命令是用chown() API实现的.
		
		3) chown()使用: 略
		
		4) 命令行chown命令:
			对于一个文件
			-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 test.c
			chown root test.c
			-rw-rw-r-- 1 root aston         0 Jul 18 20:58 test.c
			chgrp root test.c
			-rw-rw-r-- 1 root root         0 Jul 18 20:58 test.c
		5) 	fchown, 如果文件打开, 可以使用fd执行函数.

	4. umask与文件权限掩码
	
		1) 文件掩码是linux系统中维护的一个全局设置, umask的作用是用来设定我们系统中新创建的文件的默认
		   权限的.
		   
		2) umask命令就是用umask() API实现的.
		
		3) man 2 umask
		
			 mode_t umask(mode_t mask);
		4) man 1 umask (没有该命令??????)
		
		5) 命令行中, umask可以查看文件模式创建mask.
		   设置 umask 0044
		   
		   (?????) 创建的文件都没有可执行权限? 如何0044,0066是如何对应的?

//=======================================================================================================
								3.2.6.读取目录文件
//-------------------------------------------------------------------------------------------------------
3.2.6.读取目录文件


	1. opendir()与readdir()函数
	
		1) opendir()打开一个目录后得到一个DIR类型的指针给readdir()使用.
		
			DIR *opendir(const char *name);
			DIR *fdopendir(int fd);
			
			The  opendir()  function opens a directory stream corresponding to the directory name, 
			and returns a pointer to the directory stream.  The stream is positioned at the first 
			entry in the directory.
		
		2) readdir()函数调用一次就会返回一个struct dirent类型的指针, 这个指针指向一个结构体变量, 
		   这个结构体变量里面记录了一个目录项(所谓目录项就是目录中的一个子文件).
		   
			struct dirent *readdir(DIR *dirp);
			int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

			The  readdir() function returns a pointer to a dirent structure representing the next 
			directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching 
			the end of the directory stream or  if  an error occurred.
		   
		3) readdir()调用一次只能读出一个目录项, 要想读出目录中所有的目录项必须多次调用readdir函数.
		   readdir()函数内部会记住哪个目录项已经被读过了哪个还没读, 所以多次调用后不会重复返回已经
		   返回过的目录项. 当readdir函数返回NULL时就表示目录中所有的目录项已经读完了.

	2. dirent结构体

           struct dirent {
               ino_t          d_ino;       /* inode number */
               off_t          d_off;       /* not an offset; see NOTES */
               unsigned short d_reclen;    /* length of this record */
               unsigned char  d_type;      /* type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* filename */
           };		/*
		1) 文件夹也是一种特殊的文件, 也有inode.
		
		2) d_type      
		
		   DT_BLK      This is a block device.
		   DT_CHR      This is a character device.
		   DT_DIR      This is a directory.
		   DT_FIFO     This is a named pipe (FIFO).
		   DT_LNK      This is a symbolic link.
		   DT_REG      This is a regular file.
		   DT_SOCK     This is a UNIX domain socket.
		   DT_UNKNOWN  The file type is unknown.

	3. 读取目录实战演练
		
		int main(int argc, char **argv)
		{
			DIR *pDir = NULL;					// DIR 指针
			struct dirent * pEnt = NULL;		// dirent 指针
			unsigned int cnt = 0;
			
			if (argc != 2)
			{
				printf("usage: %s dirname\n", argv[0]);
				return -1;
			}
			
			pDir = opendir(argv[1]);
			if (NULL == pDir)					// 查看man手册, 可以知道返回值为NULL时打开失败. 
			{
				perror("opendir");
				return -1;
			}
			
			while (1)
			{
				pEnt = readdir(pDir);			// !!!!!
				if(pEnt != NULL)
				{
					// 还有子文件，在此处理子文件
					printf("name：[%s]	,", pEnt->d_name);
					cnt++;
					if (pEnt->d_type == DT_REG)
					{
						printf("是普通文件\n");
					}
					else
					{
						printf("不是普通文件\n");
					}
				}
				else
				{
					break;
				}
			};
			printf("总文件数为：%d\n", cnt);
			
			return 0;
		}		

	4. 可重入函数介绍
	
		1) 有些函数是可重入的有些是不可重入的, 具体概念可以去百度.
		
		2) readdir()函数和我们前面接触的一些函数是不同的, 首先readdir函数直接返回了一个结构体变量指针,
		   因为readdir内部申请了内存并且给我们返回了地址. 多次调用readdir其实readir内部并不会重复申请
		   内存而是使用第一次调用readdir时分配的那个内存. 这个设计方法是readdir不可重入的关键.
		   
		3) readdir在多次调用时是有关联的, 这个关联也标明readdir函数是不可重入的.
		
		4) 库函数中有一些函数当年刚开始提供时都是不可重入的, 后来意识到这种方式不安全, 所以重新封装了
		   C库, 提供了对应的可重复版本(一般是不可重入版本函数名_r).
		   
		(?????) readdir_r()函数的参数没有讲, 先保留.

//=======================================================================================================

















