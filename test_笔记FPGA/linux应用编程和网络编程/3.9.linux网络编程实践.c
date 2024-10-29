/*
//=======================================================================================================
									3.9.linux������ʵ��
//=======================================================================================================
3.9.1.linux�����̿��
3.9.2.TCPЭ���ѧϰ1
3.9.3.TCPЭ���ѧϰ2
3.9.4.socket��̽ӿڽ���
3.9.5.IP��ַ��ʽת������ʵ��
3.9.6.soekctʵ�����1
3.9.7.soekctʵ�����2
3.9.8.socketʵ�����3
3.9.9.socket���ʵ��4
//=======================================================================================================
3.9.1.linux�����̿��
	���ڽ��������̵Ŀ��, �ֲ�˼���TCP/IPЭ��Ľ���, BS�ܹ���CS�ܹ��Ľ��ܵ�.
3.9.2.TCPЭ���ѧϰ1
	������ϸ����TCPЭ����ص�, �����ص㽲����TCPЭ�鱣֤ʵ�ֿɿ�����Ļ���.
3.9.3.TCPЭ���ѧϰ2
	���ڽ��Ͻڼ�������TCPЭ��, ��Ҫ����TCPЭ�齨�����Ӻ͹ر�����ʱ�����ַ���, �����ʹ��TCP��ʵ�ֵ�
	����Ӧ�ò�Э��.
3.9.4.socket��̽ӿڽ���
	���ڽ���linux API������������صĽӿں���, �����ʵս����ж�Ҫ�õ���Щ����.
3.9.5.IP��ַ��ʽת������ʵ��
	����ͨ������ʵ�����������ʾIP��ַ��ʽת���ļ�������.
3.9.6.soekctʵ�����1
	���ڿ�ʼ��д����TCP�Ŀͻ��˺ͷ���������ͨ�ų���.
3.9.7.soekctʵ�����2
	���ڽ��Ͻڼ�����д, �����Ѿ�ʵ�ֿͻ��˺ͷ�����������.
3.9.8.socketʵ�����3
	����ʵ�ֿͻ��˺ͷ�����֮������ⷢ�ͺͽ��ա��������ͽ��յȹ���.
3.9.9.socket���ʵ��4	
	����ͨ������һ���򵥵�Ӧ�ò�Э��, �����ҽ���TCP���ӽ��������ͨ��Ӧ�ò�Э����ʵ��ҵ���߼�.
//=======================================================================================================
									3.9.1.linux�����̿��
//-------------------------------------------------------------------------------------------------------
	1. �����Ƿֲ��
	
		1) OSI 7��ģ��
		
		2) ����ΪʲôҪ�ֲ�
			
			ÿһ��ֻ�ù��ı����ʵ��, ����ȥ��������������ôʵ�ֵ�. ���������㲻�ù��������������
			���ӻ���wifi����; Ҳ�������м�������ֱ��, ���Ǿ����˶��·��.
			
		3) ����ֲ�ľ������
		
	2. TCP/IPЭ������
	
		1) TCP/IPЭ�����õ���������Э��ʵ��.
		
			TCP/IP��������ֲ�ʵ�ֵ�һ��ģ��. ��һ��ģ�͵�ʵ��, ��֤�˵ײ㶼�ܹ���, �û�ֻ��Ҫ��֤
			Ӧ�ò�Ϳ�����. �û�����TCP/IP��һЩϸ��, ��ʵ������ͨ��.
		
		2) TCP/IP��Ϊ4��, ��ӦOSI��7��
		
			Ӧ�ò�, �����, �����, ����ӿڲ�.
				
		3) ���Ǳ��ʱ���עӦ�ò�, �˽⴫���, ���ʻ�������������㲻�ù�
		
	3. BS��CS
	
		1) CS�ܹ�����(client server, �ͻ��˷������ܹ�)
		
			���ǵĵ�����װ��QQ���ǿͻ���, ����Ѷ��QQ������ͨ��.
		
		2) BS�ܹ�����(broswer server, ������������ܹ�)
		
			ԭ������CS�ܹ�, ������ȱ����ÿһ��Ӧ�ö�Ҫװһ���ͻ���. 
			QQ,360,�ſ�ȶ����������������. ��ȻҲ���пͻ��˵�ģʽ.
		
	4. ���γ��漰�Ĳ��.
		
		1) ֻ�漰��APIӦ�ò�ͨ��. ������, ����, ·�����ȶ�����. 
		
		2) ֻҪͨ�ŵ�������pingͨ, ��˵������Ӧ�ò��������㶼ͨ��.

//=======================================================================================================
									3.9.2.TCPЭ���ѧϰ1
//-------------------------------------------------------------------------------------------------------
	1. ����TCP�����ص�
	
		1) TCPЭ�鹤���ڴ����, ���Ϸ���socket�ӿ�, ���µ���IP��.
		
			socket�ӿھ��ǲ���ϵͳ��������ص�API. 
			APP�����ǵ��ò���ϵͳ��API��������; API����TCP������; TCP����IP������.
		
		2) TCPЭ����������(ͨ��ǰ�Ƚ���һ������, û�����ӵ�����²���ͨ��), ͨ��ǰ������3�����ֽ�����
		   �ӹ�ϵ����ܿ�ʼͨ��.
		
		3) TCPЭ���ṩ�ɿ�����, ���¶����������(TCP����Ҫ���ص�).
		
			TCPЭ����ʼ����һ�״���, socket�ӿھ��ǵ�����Щ����ʵ������ͨ�ŵ�.
		
	2. TCP��α�֤�ɿ�����
	
		1) TCP�ڴ�����Ч��ϢǰҪ��ͨ��˫������������, �������Ӳ���ͨ��.
		
		2) TCP�Ľ��շ��յ����ݰ����ack�����ͷ�, �����ͷ�δ�յ�ack�ᶪ���ش�.
	
			ÿ����һ�����ݰ�, ���շ�������һ���ظ�.
	
		3) TCP����Ч�������ݻḽ��У��, �Է�ֹ�����ڴ��ݹ�������.
		
		4) TCP���������������Զ�������������(�������ڼ���).
		
			A,B���ͨ���������Զ�Э�̵�. 
			Ĭ��һ������xx���ֽ�, ÿ�뷢XX����. һ��ʼͨ��ʱ�����������, Ȼ���𲽼ӿ�, ���ݶ������
			�Զ�����.
		
		5) ���ͷ�������ָ�ı��, ���շ���У����, һ��˳����󼴻��ش�.
		
			TCP���Զ��ָ�, �ָ��ÿһ����������. Ӧ�ò㲻�ÿ���, ֻҪ�Ѹ÷�������ֱ�ӷ���ȥ����.

	3. TCP Э��ջ
	
		�Ѿ�����������2�����й���, �û�ʹ��Э��ջ, ֻ��Ҫ֪����ôʹ�����Ϳ�����. ����ϸ��(���缸������,
		����ش���)������ȥ����, ֱ�ӵ�����غ�������.
		
//=======================================================================================================
									3.9.3.TCPЭ���ѧϰ2
//-------------------------------------------------------------------------------------------------------
	1. TCP����������
	
		1) ����������Ҫ��������.
		
		2) �������ӵ�������������listenʱ(���ڼ���״̬),�ͻ�����������connect.
		
		ע����Щ����Э���Ѿ���װ��TCPЭ���ڲ�, socket��̽ӿ�ƽʱ���ù�.

	2. TCP���Ĵ�����
	
		1) �ر�������Ҫ�Ĵ�����.
		
		2) ���������߿ͻ��˶�������������ر�.
		
		ע����Щ����Э���Ѿ���װ��TCPЭ���ڲ�, socket��̽ӿ�ƽʱ���ù�.
		    д��������Ӧ�ò�, ����Щ��������������.
		
	3. ����TCPͨ�ŵķ���ģʽ
	
		1) ���й���IP��ַ�ķ�����(����ʹ�ö�̬IP��ַӳ�似��).
		
			��Ϊ��������Ҫ���Ÿ�������ͬ���û�����, ��Ҫһ��������ַ.
			
			��̬IP��ַӳ�似��: ��������ʦ�ĸ�����վ, ��û��һ���̶��Ĺ�����ַ(��Ϊ������ַ�ܹ�,û��
			��ô���ַ), ������www.zhulaoshi.orgʱ, DSN��������ʱ����һ��������ַ.
		
		2) ��������socket��bind��listen���ڼ���״̬.
		
			����������ֱ��������������. 
		
		3) �ͻ���socket��, ֱ��connectȥ��������.
		
		4) �������յ���ͬ��ͻ��˽����Ὠ��TCP����, Ȼ��˫����ʼ�շ�����, �շ�ʱ��˫���, ����˫��
		   ���ɷ���.
		   
		5) ˫�����ɷ���ر�����
		
			�ͻ��˹ر������, ���Ƿ����˹ر�����.

	4. ������ʹ����TCPЭ�������Ӧ��
	
		1) http��ftp (http��һ�ֳ��ı�Э��,ftp��һ���ı�Э��)
		2) QQ������
		3) mail������

//=======================================================================================================
									3.9.4.socket��̽ӿڽ���
//-------------------------------------------------------------------------------------------------------
	0. socket��ؿ⺯��
		
		1) ��������
		
			socket()
			bind()
			listen()
			connect()
			
			������: socket -> bind -> listen -> accept
			�ͻ���: socket -> connect
			
		2) ���ͺͽ���
		
			send()��write()
			recv()��read()
		
			TCP���涨�ͻ��˺ͷ���������շ�, ����: �ͻ��˹ⷢ,����������; �ͻ��˷�һ��,��������һ��...
			����շ���APP���Լ�������.
		
		3) �����Ժ���

			inet_aton()��inet_addr()��inet_ntoa()
			inet_ntop()��inet_pton()

	1. ��������
	
		socket()������ man 2, man 3 �ж���.
		
		1) socket
			
			#include <sys/socket.h>

			int socket(int domain, int type, int protocol);

			a) socket����������open����, ������һ����������. ����ɹ��򷵻�һ�������ļ�������(int��
			   ��), ֮�����ǲ�������������Ӷ�ͨ�����"�����ļ�������".
			
			b) int domain: Specifies the communications domain in which a socket is to be created.
					�涨ͨ������IPV4, ����IPV6?
					��root@ubuntu:/usr/local/arm/arm-2009q3/arm-none-linux-gnueabi/libc/usr/include
																			/bits/socket2.h �ж���.
					
			c) int type: Specifies the type of socket to be created.
			
				SOCK_STREAM:	TCP����
				SOCK_DGRAM:		UDP����
				SOCK_SEQPACKET: 

			d) int protocol: Specifies a particular protocol to be used with the socket. Specifying 
			        a protocol of 0 causes socket() to use an unspecified default protocol appropriate
					for the requested socket type.

		2) bind
		
			#include <sys/socket.h>

			int bind(int socket, const struct sockaddr *address, socklen_t address_len);

			a) int socket: ͨ��socket������ȡ��"�ļ�������".
			b) const struct sockaddr *address: �������, ����ṹ���������̽ӿ���������ʾһ��IP��ַ
							��, ע�����IP��ַ�ǲ�����IPv4��IPv6��(����˵�Ǽ���IPv4��IPv6��).
							
				struct sockaddr {
					unsigned short sa_family; /* address family, AF_xxx *
					char sa_data[14]; /* 14 bytes of protocol address *
				};
				sa_family: ��2�ֽڵĵ�ַ����, һ�㶼�ǡ�AF_xxx������ʽ, ����ֵ�������֣�AF_INET,
				            AF_INET6��AF_UNSPEC.
			c)  socklen_t address_len:  Specifies the length of the sockaddr structure pointed to by 
			                the address argument.
							// ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
		
		3) listen

			#include <sys/socket.h>

			int listen(int socket, int backlog);

			a) int socket:  ͨ��socket������ȡ��"�ļ�������".
			
			b) int backlog: ���÷������������еĳ���. 

		4) connect

			#include <sys/socket.h>

			int connect(int socket, const struct sockaddr *address, socklen_t address_len);

			a) const struct sockaddr *address: Ҫ���ӵķ�����IP��ַ, ��װ�� sockaddr ���͵�address��.
			
				�Լ���IP��ַ���Զ��ŵ�������.
				
			b) ����ֵ:  Upon successful completion, connect() shall return 0; otherwise, -1 shall be 
			            returned and errno set to indicate  the error. 
		
	2. ���ͺͽ���
	
		1) write
		
			ssize_t write(int fildes, const void *buf, size_t nbyte);
			
			a) int fildes: socket���ļ�������.
			
		2) send
		
			ssize_t send(int sockfd, const void *buf, size_t len, int flags);
			
			a) int sockfd: socket���ļ�������.
			
			b) int flags:  Specifies  the  type  of message transmission. Values of this argument are 
			        formed by logically OR'ing zero or more of the following flags:
				MSG_EOR: Terminates a record (if supported by the protocol).

				MSG_OOB: Sends out-of-band data on sockets that support out-of-band communications.  
				         The significance and semantics of out-of-band data are protocol-specific.	

				flags = 0ʱ, �� write()������ͬ.  ��������ֵʱ,��Ҫ֧������Э��ʱ����.
							 һ���������Ϊ0.
											
		3) recv��read
		
		    ssize_t read(int fildes, void *buf, size_t nbyte);

			ssize_t recv(int socket, void *buffer, size_t length, int flags);

	3. �����Ժ���
	
		1) inet_aton��inet_addr��inet_ntoa(��֧��IPV6, �³����Ƽ�ʹ��)

			in_addr_t inet_addr(const char *cp);		// ����ֵ����32λ.
			
			// ������������������.

		
		2) inet_ntop��inet_pton(�³����Ƽ�ʹ��)

			const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
			int inet_pton(int af, const char *src, void *dst);
			


		
	4. ��ʾIP��ַ������ݽṹ

		1) �������� netinet/in.h (/usr/include/netinet/in.h)
		
		2) struct sockaddr, ����ṹ���������̽ӿ���������ʾһ��IP��ַ��, ע�����IP��ַ�ǲ�����
		   IPv4��IPv6��(����˵�Ǽ���IPv4��IPv6��).
		
		3) typedef uint32_t in_addr_t;		�����ڲ�������ʾIP��ַ������
			
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
		  
			__SOCKADDR_COMMON ��һ����ͨ�� C �꣬�������£�

			#define __SOCKADDR_COMMON(sa_prefix) \
			sa_family_t sa_prefix##family
			��ͨ��Ԥ�����������򵥵�����##����Ĳ������γɱ�������

			������ ����չ���÷�ʱstruct sockaddr_in������õ�������Ϣ��

			sa_family_t sin_family
			����__SOCKADDR_COMMON (sin_);���򵥵��滻Ϊsa_family_t sin_family;		  
		  
		
		6) struct sockaddr	����ṹ����linux�������̽ӿ���������ʾIP��ַ�ı�׼�ṹ��, bind��
		       connect�Ⱥ����ж���Ҫ����ṹ��, ����ṹ���Ǽ���IPV4��IPV6��. ��ʵ�ʱ�������
			   �ṹ��ᱻһ��struct sockaddr_in����һ��struct sockaddr_in6�����.
				
			struct sockaddr {
				unsigned short sa_family; /* address family, AF_xxx *
				char sa_data[14]; /* 14 bytes of protocol address *
			};
		
		(???? )sockaddr��sa_data[]��char , ��Ӧsockaddr_in�ļ���32λ����????

//=======================================================================================================
									3.9.5.IP��ַ��ʽת������ʵ��
//-------------------------------------------------------------------------------------------------------
	1. inet_addr()����
	
		#define IPADDR	"192.168.1.102"

		int main(void)
		{
			in_addr_t addr = 0;
			
			addr = inet_addr(IPADDR);
			
			printf("addr = 0x%x.\n", addr);		// 0x6601a8c0

			return 0;
		}
		
		���: addr = 0x6608A8C0  // 102 1 168 192 ��С��ģʽ

		�ܽ�: 
				1) �����ֽ���, ��ʵ���Ǵ��ģʽ. 
				2) inet_addr()�����ڲ���ת��Ϊ���ģʽ(�����ֽ���).

	2. inet_pton()����
	
		int ret = 0;
		struct in_addr addr = {0};
		
		ret = inet_pton(AF_INET, IPADDR, &addr);
		if (ret != 1)
		{
			printf("inet_pton error\n");
			return -1;
		}
		
		printf("addr = 0x%x.\n", addr.s_addr);
		
	
	3. inet_ntop()����

		struct in_addr addr = {0};
		char buf[50] = {0};
		
		addr.s_addr = 0x6703a8c0;
		
		inet_ntop(AF_INET, &addr, buf, sizeof(buf));

		printf("ip addr = %s.\n", buf);

//=======================================================================================================
									3.9.6-7.soekctʵ�����1,2
//-------------------------------------------------------------------------------------------------------
	1. �������˳����д
	
		1) socket
		2) bind
		3) listen
		4) accept, ����ֵ��һ��fd, accept��ȷ���ؾͱ�ʾ�����Ѿ���ǰ�������ҵĿͻ���֮�佨����һ��TCP
		   ������, �Ժ����Ǿ�Ҫͨ������������Ϳͻ��˽��ж�д����, ��д��������Ҫһ��fd, ���fd����
		   accept��������.

		ע�⣺socket���ص�fd��������fd, �����������ͻ��˵�, �����������κοͻ��˽��ж�д; accept����
		      ��fd��������fd, �����������Ƕ˵Ŀͻ��˳�����ж�д.
			  
			#define SERPORT		9003
			#define SERADDR		"192.168.233.128"		// ifconfig������
			#define BACKLOG		100


			int main(void)
			{
				// ��1������socket���ļ�������
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
				
				// ��2����bind��sockefd�͵�ǰ���Ե�ip��ַ&�˿ں�
				seraddr.sin_family = AF_INET;		// ���õ�ַ��ΪIPv4
				seraddr.sin_port = htons(SERPORT);	// ���õ�ַ�Ķ˿ں���Ϣ
				seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//������IP��ַ
				ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
				if (ret < 0)
				{
					perror("bind");
					return -1;
				}
				printf("bind success.\n");
				
				// ��������listen�����˿�
				ret = listen(sockfd, BACKLOG);		// �����ȴ��ͻ��������ӷ�����
				if (ret < 0)
				{
					perror("listen");
					return -1;
				}
				
				// ���Ĳ���accept�����ȴ��ͻ��˽���
				clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
				printf("�����Ѿ�������client fd = %d.\n", clifd);
				
				return 0;
			}			  
			  
	2. �ͻ��˳����д
	
		1)socket
		2)connect
		
			#define SERADDR		"192.168.233.128"		// ���������Ÿ����ǵ�IP��ַ�Ͷ˿ں�
			#define SERPORT		9003



			int main(void)
			{
				// ��1������socket���ļ�������
				int sockfd = -1, ret = -1;
				struct sockaddr_in seraddr = {0};
				struct sockaddr_in cliaddr = {0};
				
				// ��1����socket
				sockfd = socket(AF_INET, SOCK_STREAM, 0);
				if (-1 == sockfd)
				{
					perror("socket");
					return -1;
				}
				printf("socketfd = %d.\n", sockfd);
				
				// ��2����connect���ӷ�����
				seraddr.sin_family = AF_INET;		// ���õ�ַ��ΪIPv4
				seraddr.sin_port = htons(SERPORT);	// ���õ�ַ�Ķ˿ں���Ϣ
				seraddr.sin_addr.s_addr = inet_addr(SERADDR);	//������IP��ַ
				ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
				if (ret < 0)
				{
					perror("listen");
					return -1;
				}
				printf("connect result, ret = %d.\n", ret);
				
				return 0;
			}		

	3. ����˿ں�, ʵ�ʾ���һ�����ֱ��, ����������һ̨������(�����Ĳ���ϵͳ��)Ψһ�ı�ʶһ��������
	         �Ľ���. �˿ںź�IP��ַһ��ᱻ�������ǰ���̷������߽��յ���ÿһ�����ݰ���. ÿһ�����ݰ�
			 �����������ϴ��ݵ�ʱ��, �ڲ��������˷��ͷ��ͽ��շ�����Ϣ(����IP��ַ�Ͷ˿ں�), ����IP��ַ
			 �Ͷ˿ں������������Ǵ����һ�𲻷ּҵ�.

	4. ע��:
		
		1) #define SERPORT		9003
		   seraddr.sin_port = htons(SERPORT);		// ����ֱ��д, ��Ϊ���ܲ����������ֽ���.
		2) listen, ֻ�Ǽ����涨���Ǹ��˿�. �����͵�������IP��ַ�Ķ˿ں�һ�µ����ݰ����ܽ��뵽������.
		3) accept(sockfd, (struct sockaddr *)&cliaddr, &len);
		   accept()����������.
		4) �������Ķ˿ں���ȷ����, ��Ϊ����Ҫ���ӷ�����, ����ȷ��. ���ͻ��˵Ķ˿ںſ��Բ��涨, ���Զ�
			�����. �ͻ������������ӱ��˵�.
			
		5) ������,������ʹ�õ�IP����ifconfig��ʾ��IP. �ͻ��˽�������Ҳ��ʹ�����IP.
			��������ubuntu��Ŀ¼��make, ����ser,cli�������Ϳͻ���.  Ȼ���������жϷֱ�����,�鿴���.
			
			(?????) ����ķ������Ϳͻ��˲���һ������? һ��IP? ���ͨ�ŵ�?
			(�����γ�˵��: ������һ�����Ժ�����������һ��, ���ڿͻ��˺ͷ�����������˵, ����֪����һ��
			 �������, ������ͨ��, �����������κ���̨����Ҳ����ͨ��.)

//=======================================================================================================
									3.9.8.socketʵ�����3
//-------------------------------------------------------------------------------------------------------
	1. �ͻ��˷���&����������
	
		������һ�����ӽ������Ժ�Ĵ��������.
		
		1) ������
			
			ret = recv(clifd, recvbuf, sizeof(recvbuf), 0);		// ���տ�ͻ��˷��͵����ݰ�
			printf("�ɹ�������%d���ֽ�\n", ret);
			printf("client���͹����������ǣ�%s\n", recvbuf);
			
			
		2) �ͻ���
			
			strcpy(sendbuf, "hello world.");
			ret = send(sockfd, sendbuf, strlen(sendbuf), 0); // 
			printf("������%d���ַ�\n", ret);
			
		�ܽ�:
				1) strlen����ֻͳ�Ʒ��͵��ַ�����, ��ͳ��'\0'. ������sizeof.
				2) ������������ʹ��, recv()����ʹ��clifd
						(clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len)).
		
		ע��:
				1) ����Ϊͨ��һ�ξͽ���, ���Լ�һ��ѭ��, ��������, ����.
				2) ���ϳ���û�������˳�����, ֻ��CTRL+C����. ��������´�����ʱ, ������ܻ᲻����
				   �����޸���������Ķ˿ں�, �����Ϳ������Ͻ�������.
				
	2. ����������&�ͻ��˽���
	
		����������һ��.
		
	3. ̽�֣�����÷������Ϳͻ��˺úù�ͨ
	
		1) �ͻ��˺ͷ�����ԭ���϶���������ķ�����, ����ʵ����˫��������ϣ�client����ʱ��server����, 
		   ��server����ʱ��client����.
		   
		2) �����˽⵽��һ�㣺client��server֮���ͨ�����첽��, ���������ĸ�Դ.
		
		3) �������������Ӧ�ò�Э�������. ˵���˾�������server��client��������һϵ�е�ͨ��Լ��.

//=======================================================================================================
									3.9.9.socket���ʵ��4
//-------------------------------------------------------------------------------------------------------
	1. �Զ���Ӧ�ò�Э���һ�����涨���ͺͽ��շ���
	
		1) �涨���ӽ������ɿͻ������������������1���������ݰ�, Ȼ��������յ����ݰ���, ��ȡ���͵�����,
		   ����ӻָ���Ϣ��, �ظ��ͻ���һ����Ӧ���ݰ�, �����һ��ͨ�Żغ�.
		   
		2) �������ӵ�ͨ�ž�����N����غ���ɵ�.

	2. �������:
	
		// ����������
		while (1)
		{
			info st;
			// �غ��е�1������������
			ret = recv(clifd, &st, sizeof(info), 0);

			// �غ��е�2���������������ͻ������ݰ���Ȼ��ɻ
			if (st.cmd == CMD_REGISTER)
			{
				printf("�û�Ҫע��ѧ����Ϣ\n");
				printf("ѧ��������%s��ѧ�����䣺%d\n", st.name, st.age);
				// �����������Ҫ����������ע�ᶯ����һ���ǲ������ݿ�һ����Ϣ
				
				// �غ��е�3�����ظ��ͻ���
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

		// �ͻ��˷���
		while (1)
		{
			// �غ��е�1�����ͻ��˸�������������Ϣ
			info st1;
			printf("������ѧ������\n");
			scanf("%s", st1.name);
			printf("������ѧ������");
			scanf("%d", &st1.age);
			st1.cmd = CMD_REGISTER;
			//printf("�ղ�������ǣ�%s\n", sendbuf);
			ret = send(sockfd, &st1, sizeof(info), 0);
			printf("������1��ѧ����Ϣ\n");
			
			// �غ��е�2�����ͻ��˽��շ������Ļظ�
			memset(&st1, 0, sizeof(st1));
			ret = recv(sockfd, &st1, sizeof(st1), 0);
			
			// �غ��е�3�����ͻ��˽����������Ļظ���������һ������
			if (st1.stat == STAT_OK)
			{
				printf("ע��ѧ����Ϣ�ɹ�\n");
			}
			else
			{
				printf("ע��ѧ����Ϣʧ��\n");
			}
		}	
	
	3. ����Ӧ�ò�Э�飺
	
		http��ftp...
	
	4. UDP���

		�����ӵ�, ���ɿ���.

//=======================================================================================================


		

