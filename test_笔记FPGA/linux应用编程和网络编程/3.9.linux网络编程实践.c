/*
//=======================================================================================================
									3.9.linux网络编程实践
//=======================================================================================================
3.9.1.linux网络编程框架
3.9.2.TCP协议的学习1
3.9.3.TCP协议的学习2
3.9.4.socket编程接口介绍
3.9.5.IP地址格式转换函数实践
3.9.6.soekct实践编程1
3.9.7.soekct实践编程2
3.9.8.socket实践编程3
3.9.9.socket编程实践4
//=======================================================================================================
3.9.1.linux网络编程框架
	本节讲述网络编程的框架, 分层思想和TCP/IP协议的介绍, BS架构和CS架构的介绍等.
3.9.2.TCP协议的学习1
	本节详细介绍TCP协议的特点, 其中重点讲述了TCP协议保证实现可靠传输的机制.
3.9.3.TCP协议的学习2
	本节接上节继续讲解TCP协议, 主要讲了TCP协议建立连接和关闭连接时的握手方法, 最后讲了使用TCP来实现的
	常见应用层协议.
3.9.4.socket编程接口介绍
	本节介绍linux API中与网络编程相关的接口函数, 后面的实战编程中都要用到这些函数.
3.9.5.IP地址格式转换函数实践
	本节通过代码实践来给大家演示IP地址格式转换的几个函数.
3.9.6.soekct实践编程1
	本节开始编写基于TCP的客户端和服务器连接通信程序.
3.9.7.soekct实践编程2
	本节接上节继续编写, 并且已经实现客户端和服务器的连接.
3.9.8.socket实践编程3
	本节实现客户端和服务器之间的任意发送和接收、反复发送接收等功能.
3.9.9.socket编程实践4	
	本节通过定义一个简单的应用层协议, 来向大家介绍TCP连接建立后如何通过应用层协议来实现业务逻辑.
//=======================================================================================================
									3.9.1.linux网络编程框架
//-------------------------------------------------------------------------------------------------------
	1. 网络是分层的
	
		1) OSI 7层模型
		
		2) 网络为什么要分层
			
			每一层只用关心本层的实现, 不用去关心其它层是怎么实现的. 比如其他层不用关心物理层是有线
			连接还是wifi连接; 也不关心中间是网线直连, 还是经过了多个路由.
			
		3) 网络分层的具体表现
		
	2. TCP/IP协议引入
	
		1) TCP/IP协议是用的最多的网络协议实现.
		
			TCP/IP就是网络分层实现的一种模型. 这一套模型的实现, 保证了底层都能工作, 用户只需要保证
			应用层就可以了. 用户调用TCP/IP的一些细节, 来实现网络通信.
		
		2) TCP/IP分为4层, 对应OSI的7层
		
			应用层, 传输层, 网络层, 网络接口层.
				
		3) 我们编程时最关注应用层, 了解传输层, 网际互联层和网络接入层不用管
		
	3. BS和CS
	
		1) CS架构介绍(client server, 客户端服务器架构)
		
			我们的电脑上装的QQ就是客户端, 与腾讯的QQ服务器通信.
		
		2) BS架构介绍(broswer server, 浏览器服务器架构)
		
			原来都是CS架构, 这样的缺点是每一个应用都要装一个客户端. 
			QQ,360,优酷等都可以用浏览器访问. 当然也都有客户端的模式.
		
	4. 本课程涉及的层次.
		
		1) 只涉及到API应用层通信. 驱动层, 网卡, 路由器等都不管. 
		
		2) 只要通信的两端能ping通, 就说明除了应用层外其他层都通了.

//=======================================================================================================
									3.9.2.TCP协议的学习1
//-------------------------------------------------------------------------------------------------------
	1. 关于TCP理解的重点
	
		1) TCP协议工作在传输层, 对上服务socket接口, 对下调用IP层.
		
			socket接口就是操作系统与网络相关的API. 
			APP程序都是调用操作系统的API来工作的; API调用TCP来工作; TCP调用IP来工作.
		
		2) TCP协议面向连接(通信前先建立一个连接, 没有连接的情况下不能通信), 通信前必须先3次握手建立连
		   接关系后才能开始通信.
		
		3) TCP协议提供可靠传输, 不怕丢包、乱序等(TCP最重要的特点).
		
			TCP协议起始就是一套代码, socket接口就是调用这些代码实现网络通信的.
		
	2. TCP如何保证可靠传输
	
		1) TCP在传输有效信息前要求通信双方必须先握手, 建立连接才能通信.
		
		2) TCP的接收方收到数据包后会ack给发送方, 若发送方未收到ack会丢包重传.
	
			每发送一次数据包, 接收方都会有一个回复.
	
		3) TCP的有效数据内容会附带校验, 以防止内容在传递过程中损坏.
		
		4) TCP会根据网络带宽来自动调节适配速率(滑动窗口技术).
		
			A,B间的通信速率是自动协商的. 
			默认一个包是xx个字节, 每秒发XX个包. 一开始通信时就是这个速率, 然后逐步加快, 根据丢包情况
			自动调整.
		
		5) 发送方会给各分割报文编号, 接收方会校验编号, 一旦顺序错误即会重传.
		
			TCP会自动分割, 分割后每一个包添加序号. 应用层不用考虑, 只要把该发的数据直接发出去即可.

	3. TCP 协议栈
	
		已经包含了上述2的所有功能, 用户使用协议栈, 只需要知道怎么使用它就可以了. 其中细节(比如几次握手,
		如何重传等)都不用去关心, 直接调用相关函数即可.
		
//=======================================================================================================
									3.9.3.TCP协议的学习2
//-------------------------------------------------------------------------------------------------------
	1. TCP的三次握手
	
		1) 建立连接需要三次握手.
		
		2) 建立连接的条件：服务器listen时(处于监听状态),客户端主动发起connect.
		
		注：这些握手协议已经封装在TCP协议内部, socket编程接口平时不用管.

	2. TCP的四次握手
	
		1) 关闭连接需要四次握手.
		
		2) 服务器或者客户端都可以主动发起关闭.
		
		注：这些握手协议已经封装在TCP协议内部, socket编程接口平时不用管.
		    写程序是在应用层, 而这些握手是在其他层.
		
	3. 基于TCP通信的服务模式
	
		1) 具有公网IP地址的服务器(或者使用动态IP地址映射技术).
		
			因为服务器需要开放给其他不同的用户访问, 需要一个公网地址.
			
			动态IP地址映射技术: 比如朱老师的个人网站, 并没有一个固定的公网地址(因为公网地址很贵,没有
			那么多地址), 当输入www.zhulaoshi.org时, DSN服务器临时分配一个公网地址.
		
		2) 服务器端socket、bind、listen后处于监听状态.
		
			服务器程序分别调用这三个函数. 
		
		3) 客户端socket后, 直接connect去发起连接.
		
		4) 服务器收到并同意客户端接入后会建立TCP连接, 然后双方开始收发数据, 收发时是双向的, 而且双方
		   均可发起.
		   
		5) 双方均可发起关闭连接
		
			客户端关闭浏览器, 就是发起了关闭连接.

	4. 常见的使用了TCP协议的网络应用
	
		1) http、ftp (http是一种超文本协议,ftp是一种文本协议)
		2) QQ服务器
		3) mail服务器

//=======================================================================================================
									3.9.4.socket编程接口介绍
//-------------------------------------------------------------------------------------------------------
	0. socket相关库函数
		
		1) 建立连接
		
			socket()
			bind()
			listen()
			connect()
			
			服务器: socket -> bind -> listen -> accept
			客户端: socket -> connect
			
		2) 发送和接收
		
			send()和write()
			recv()和read()
		
			TCP不规定客户端和服务器如何收发, 可以: 客户端光发,服务器光收; 客户端发一句,服务器回一句...
			如何收发是APP层自己的事情.
		
		3) 辅助性函数

			inet_aton()、inet_addr()、inet_ntoa()
			inet_ntop()、inet_pton()

	1. 建立连接
	
		socket()函数在 man 2, man 3 中都有.
		
		1) socket
			
			#include <sys/socket.h>

			int socket(int domain, int type, int protocol);

			a) socket函数类似于open函数, 用来打开一个网络连接. 如果成功则返回一个网络文件描述符(int类
			   型), 之后我们操作这个网络连接都通过这个"网络文件描述符".
			
			b) int domain: Specifies the communications domain in which a socket is to be created.
					规定通信域是IPV4, 还是IPV6?
					在root@ubuntu:/usr/local/arm/arm-2009q3/arm-none-linux-gnueabi/libc/usr/include
																			/bits/socket2.h 中定义.
					
			c) int type: Specifies the type of socket to be created.
			
				SOCK_STREAM:	TCP连接
				SOCK_DGRAM:		UDP连接
				SOCK_SEQPACKET: 

			d) int protocol: Specifies a particular protocol to be used with the socket. Specifying 
			        a protocol of 0 causes socket() to use an unspecified default protocol appropriate
					for the requested socket type.

		2) bind
		
			#include <sys/socket.h>

			int bind(int socket, const struct sockaddr *address, socklen_t address_len);

			a) int socket: 通过socket函数获取的"文件描述符".
			b) const struct sockaddr *address: 输入参数, 这个结构体是网络编程接口中用来表示一个IP地址
							的, 注意这个IP地址是不区分IPv4和IPv6的(或者说是兼容IPv4和IPv6的).
							
				struct sockaddr {
					unsigned short sa_family; /* address family, AF_xxx *
					char sa_data[14]; /* 14 bytes of protocol address *
				};
				sa_family: 是2字节的地址家族, 一般都是“AF_xxx”的形式, 它的值包括三种：AF_INET,
				            AF_INET6和AF_UNSPEC.
			c)  socklen_t address_len:  Specifies the length of the sockaddr structure pointed to by 
			                the address argument.
							// ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
		
		3) listen

			#include <sys/socket.h>

			int listen(int socket, int backlog);

			a) int socket:  通过socket函数获取的"文件描述符".
			
			b) int backlog: 设置服务器监听队列的长度. 

		4) connect

			#include <sys/socket.h>

			int connect(int socket, const struct sockaddr *address, socklen_t address_len);

			a) const struct sockaddr *address: 要连接的服务器IP地址, 封装到 sockaddr 类型的address中.
			
				自己的IP地址会自动放到报文中.
				
			b) 返回值:  Upon successful completion, connect() shall return 0; otherwise, -1 shall be 
			            returned and errno set to indicate  the error. 
		
	2. 发送和接收
	
		1) write
		
			ssize_t write(int fildes, const void *buf, size_t nbyte);
			
			a) int fildes: socket的文件描述符.
			
		2) send
		
			ssize_t send(int sockfd, const void *buf, size_t len, int flags);
			
			a) int sockfd: socket的文件描述符.
			
			b) int flags:  Specifies  the  type  of message transmission. Values of this argument are 
			        formed by logically OR'ing zero or more of the following flags:
				MSG_EOR: Terminates a record (if supported by the protocol).

				MSG_OOB: Sends out-of-band data on sockets that support out-of-band communications.  
				         The significance and semantics of out-of-band data are protocol-specific.	

				flags = 0时, 与 write()函数相同.  设置其他值时,需要支持特殊协议时采用.
							 一般就是设置为0.
											
		3) recv和read
		
		    ssize_t read(int fildes, void *buf, size_t nbyte);

			ssize_t recv(int socket, void *buffer, size_t length, int flags);

	3. 辅助性函数
	
		1) inet_aton、inet_addr、inet_ntoa(不支持IPV6, 新程序不推荐使用)

			in_addr_t inet_addr(const char *cp);		// 返回值就是32位.
			
			// 另外两个函数不常用.

		
		2) inet_ntop、inet_pton(新程序推荐使用)

			const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
			int inet_pton(int af, const char *src, void *dst);
			


		
	4. 表示IP地址相关数据结构

		1) 都定义在 netinet/in.h (/usr/include/netinet/in.h)
		
		2) struct sockaddr, 这个结构体是网络编程接口中用来表示一个IP地址的, 注意这个IP地址是不区分
		   IPv4和IPv6的(或者说是兼容IPv4和IPv6的).
		
		3) typedef uint32_t in_addr_t;		网络内部用来表示IP地址的类型
			
		4) struct in_addr
		  {
			in_addr_t s_addr;
		  };
		
		5) struct sockaddr_in
		  {
			__SOCKADDR_COMMON (sin_);
			in_port_t sin_port;                 /* Port number.  *
			struct in_addr sin_addr;            /* Internet address.  *

			/* Pad to size of `struct sockaddr'.  *
			unsigned char sin_zero[sizeof (struct sockaddr) -
								   __SOCKADDR_COMMON_SIZE -
								   sizeof (in_port_t) -
								   sizeof (struct in_addr)];
		  };
		  
			__SOCKADDR_COMMON 是一个普通的 C 宏，定义如下：

			#define __SOCKADDR_COMMON(sa_prefix) \
			sa_family_t sa_prefix##family
			它通过预处理器操作简单地连接##传入的参数以形成变量名。

			当您在 中扩展该用法时struct sockaddr_in，您会得到以下信息：

			sa_family_t sin_family
			所以__SOCKADDR_COMMON (sin_);将简单地替换为sa_family_t sin_family;		  
		  
		
		6) struct sockaddr	这个结构体是linux的网络编程接口中用来表示IP地址的标准结构体, bind、
		       connect等函数中都需要这个结构体, 这个结构体是兼容IPV4和IPV6的. 在实际编程中这个
			   结构体会被一个struct sockaddr_in或者一个struct sockaddr_in6所填充.
				
			struct sockaddr {
				unsigned short sa_family; /* address family, AF_xxx *
				char sa_data[14]; /* 14 bytes of protocol address *
			};
		
		(???? )sockaddr中sa_data[]是char , 对应sockaddr_in的几个32位变量????

//=======================================================================================================
									3.9.5.IP地址格式转换函数实践
//-------------------------------------------------------------------------------------------------------
	1. inet_addr()函数
	
		#define IPADDR	"192.168.1.102"

		int main(void)
		{
			in_addr_t addr = 0;
			
			addr = inet_addr(IPADDR);
			
			printf("addr = 0x%x.\n", addr);		// 0x6601a8c0

			return 0;
		}
		
		输出: addr = 0x6608A8C0  // 102 1 168 192 大小端模式

		总结: 
				1) 网络字节序, 其实就是大端模式. 
				2) inet_addr()函数内部会转化为大端模式(网络字节序).

	2. inet_pton()函数
	
		int ret = 0;
		struct in_addr addr = {0};
		
		ret = inet_pton(AF_INET, IPADDR, &addr);
		if (ret != 1)
		{
			printf("inet_pton error\n");
			return -1;
		}
		
		printf("addr = 0x%x.\n", addr.s_addr);
		
	
	3. inet_ntop()函数

		struct in_addr addr = {0};
		char buf[50] = {0};
		
		addr.s_addr = 0x6703a8c0;
		
		inet_ntop(AF_INET, &addr, buf, sizeof(buf));

		printf("ip addr = %s.\n", buf);

//=======================================================================================================
									3.9.6-7.soekct实践编程1,2
//-------------------------------------------------------------------------------------------------------
	1. 服务器端程序编写
	
		1) socket
		2) bind
		3) listen
		4) accept, 返回值是一个fd, accept正确返回就表示我们已经和前来连接我的客户端之间建立了一个TCP
		   连接了, 以后我们就要通过这个连接来和客户端进行读写操作, 读写操作就需要一个fd, 这个fd就由
		   accept来返回了.

		注意：socket返回的fd叫做监听fd, 是用来监听客户端的, 不能用来和任何客户端进行读写; accept返回
		      的fd叫做连接fd, 用来和连接那端的客户端程序进行读写.
			  
			#define SERPORT		9003
			#define SERADDR		"192.168.233.128"		// ifconfig看到的
			#define BACKLOG		100


			int main(void)
			{
				// 第1步：先socket打开文件描述符
				int sockfd = -1, ret = -1, clifd = -1;
				socklen_t len = 0;
				struct sockaddr_in seraddr = {0};
				struct sockaddr_in cliaddr = {0};
				
				char ipbuf[30] = {0};
				
				
				sockfd = socket(AF_INET, SOCK_STREAM, 0);
				if (-1 == sockfd)
				{
					perror("socket");
					return -1;
				}
				printf("socketfd = %d.\n", sockfd);
				
				// 第2步：bind绑定sockefd和当前电脑的ip地址&端口号
				seraddr.sin_family = AF_INET;		// 设置地址族为IPv4
				seraddr.sin_port = htons(SERPORT);	// 设置地址的端口号信息
				seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//　设置IP地址
				ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
				if (ret < 0)
				{
					perror("bind");
					return -1;
				}
				printf("bind success.\n");
				
				// 第三步：listen监听端口
				ret = listen(sockfd, BACKLOG);		// 阻塞等待客户端来连接服务器
				if (ret < 0)
				{
					perror("listen");
					return -1;
				}
				
				// 第四步：accept阻塞等待客户端接入
				clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
				printf("连接已经建立，client fd = %d.\n", clifd);
				
				return 0;
			}			  
			  
	2. 客户端程序编写
	
		1)socket
		2)connect
		
			#define SERADDR		"192.168.233.128"		// 服务器开放给我们的IP地址和端口号
			#define SERPORT		9003



			int main(void)
			{
				// 第1步：先socket打开文件描述符
				int sockfd = -1, ret = -1;
				struct sockaddr_in seraddr = {0};
				struct sockaddr_in cliaddr = {0};
				
				// 第1步：socket
				sockfd = socket(AF_INET, SOCK_STREAM, 0);
				if (-1 == sockfd)
				{
					perror("socket");
					return -1;
				}
				printf("socketfd = %d.\n", sockfd);
				
				// 第2步：connect链接服务器
				seraddr.sin_family = AF_INET;		// 设置地址族为IPv4
				seraddr.sin_port = htons(SERPORT);	// 设置地址的端口号信息
				seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//　设置IP地址
				ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
				if (ret < 0)
				{
					perror("listen");
					return -1;
				}
				printf("connect result, ret = %d.\n", ret);
				
				return 0;
			}		

	3. 概念：端口号, 实质就是一个数字编号, 用来在我们一台主机中(主机的操作系统中)唯一的标识一个能上网
	         的进程. 端口号和IP地址一起会被打包到当前进程发出或者接收到的每一个数据包中. 每一个数据包
			 将来在网络上传递的时候, 内部都包含了发送方和接收方的信息(就是IP地址和端口号), 所以IP地址
			 和端口号这两个往往是打包在一起不分家的.

	4. 注意:
		
		1) #define SERPORT		9003
		   seraddr.sin_port = htons(SERPORT);		// 不能直接写, 因为可能不符合网络字节序.
		2) listen, 只是监听规定的那个端口. 即发送到服务器IP地址的端口号一致的数据包才能进入到进程中.
		3) accept(sockfd, (struct sockaddr *)&cliaddr, &len);
		   accept()函数会阻塞.
		4) 服务器的端口号是确定的, 因为别人要链接服务器, 必须确定. 而客户端的端口号可以不规定, 是自动
			分配的. 客户端是主动链接别人的.
			
		5) 本程序,服务器使用的IP就是ifconfig显示的IP. 客户端建立链接也是使用这个IP.
			测试是在ubuntu该目录下make, 生成ser,cli服务器和客户端.  然后再两个中断分别运行,查看结果.
			
			(?????) 这里的服务器和客户端不是一个机器? 一个IP? 如何通信的?
			(后来课程说道: 这里用一个电脑和用两个电脑一样, 对于客户端和服务器进程来说, 并不知道在一个
			 计算机上, 这里能通信, 换到世界上任何两台机器也可以通信.)

//=======================================================================================================
									3.9.8.socket实践编程3
//-------------------------------------------------------------------------------------------------------
	1. 客户端发送&服务器接收
	
		基于上一节连接建立好以后的代码基础上.
		
		1) 服务器
			
			ret = recv(clifd, recvbuf, sizeof(recvbuf), 0);		// 接收库客户端发送的数据包
			printf("成功接收了%d个字节\n", ret);
			printf("client发送过来的内容是：%s\n", recvbuf);
			
			
		2) 客户端
			
			strcpy(sendbuf, "hello world.");
			ret = send(sockfd, sendbuf, strlen(sendbuf), 0); // 
			printf("发送了%d个字符\n", ret);
			
		总结:
				1) strlen函数只统计发送的字符数量, 不统计'\0'. 不能用sizeof.
				2) 服务器程序中使用, recv()函数使用clifd
						(clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)).
		
		注意:
				1) 以上为通信一次就结束, 可以加一个循环, 反复发送, 接收.
				2) 以上程序没有正常退出机制, 只能CTRL+C结束. 但是如果下次连接时, 程序可能会不发绑定
				   可以修改两个程序的端口号, 这样就可以马上建立连接.
				
	2. 服务器发送&客户端接收
	
		与上例几乎一样.
		
	3. 探讨：如何让服务器和客户端好好沟通
	
		1) 客户端和服务器原则上都可以任意的发和收, 但是实际上双方必须配合：client发的时候server就收, 
		   而server发的时候client就收.
		   
		2) 必须了解到的一点：client和server之间的通信是异步的, 这就是问题的根源.
		
		3) 解决方案：依靠应用层协议来解决. 说白了就是我们server和client事先做好一系列的通信约定.

//=======================================================================================================
									3.9.9.socket编程实践4
//-------------------------------------------------------------------------------------------------------
	1. 自定义应用层协议第一步：规定发送和接收方法
	
		1) 规定连接建立后由客户端主动向服务器发出1个请求数据包, 然后服务器收到数据包后, 读取发送的数据,
		   并添加恢复信息后, 回复客户端一个回应数据包, 这就是一个通信回合.
		   
		2) 整个连接的通信就是由N多个回合组成的.

	2. 程序测试:
	
		// 服务器处理
		while (1)
		{
			info st;
			// 回合中第1步：服务器收
			ret = recv(clifd, &st, sizeof(info), 0);

			// 回合中第2步：服务器解析客户端数据包，然后干活，
			if (st.cmd == CMD_REGISTER)
			{
				printf("用户要注册学生信息\n");
				printf("学生姓名：%s，学生年龄：%d\n", st.name, st.age);
				// 在这里服务器要进行真正的注册动作，一般是插入数据库一条信息
				
				// 回合中第3步：回复客户端
				st.stat = STAT_OK;
				ret = send(clifd, &st, sizeof(info), 0);
			}
			
			if (st.cmd == CMD_CHECK)
			{
				
			}
			
			if (st.cmd == CMD_GETINFO)
			{
				
			}

		}

		// 客户端发送
		while (1)
		{
			// 回合中第1步：客户端给服务器发送信息
			info st1;
			printf("请输入学生姓名\n");
			scanf("%s", st1.name);
			printf("请输入学生年龄");
			scanf("%d", &st1.age);
			st1.cmd = CMD_REGISTER;
			//printf("刚才输入的是：%s\n", sendbuf);
			ret = send(sockfd, &st1, sizeof(info), 0);
			printf("发送了1个学生信息\n");
			
			// 回合中第2步：客户端接收服务器的回复
			memset(&st1, 0, sizeof(st1));
			ret = recv(sockfd, &st1, sizeof(st1), 0);
			
			// 回合中第3步：客户端解析服务器的回复，再做下一步定夺
			if (st1.stat == STAT_OK)
			{
				printf("注册学生信息成功\n");
			}
			else
			{
				printf("注册学生信息失败\n");
			}
		}	
	
	3. 常用应用层协议：
	
		http、ftp...
	
	4. UDP简介

		非连接的, 不可靠的.

//=======================================================================================================


		

