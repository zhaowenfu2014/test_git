/*
//=======================================================================================================
										3.2.�ļ�����
//=======================================================================================================
3.2.1.linux�и����ļ�����
3.2.2.�����ļ����Ի�ȡ
3.2.3.stat������Ӧ�ð���
3.2.4.�ļ�Ȩ�޹���1
3.2.5.�ļ�Ȩ�޹���2
3.2.6.��ȡĿ¼�ļ�
//=======================================================================================================
3.2.1.linux�и����ļ�����
	���ڽ���linux�и����ļ�����, �����ص㽲�����ı��ļ��Ͷ������ļ���������ͨ�ļ�.
3.2.2.�����ļ����Ի�ȡ
	���ڽ���stat�����弰����λ�ȡ�ļ����Խṹ��, ������һ����ʵ����ȡ��һЩ�ļ�������Ϊ��֤.
3.2.3.stat������Ӧ�ð���
	����ʹ��stat������ȡ�ļ��ļ����Ժ�, ʹ��linuxϵͳ�ĺ�����ȡ�ļ����ͺ��ļ���дȨ����Ϣ.
3.2.4.�ļ�Ȩ�޹���1
	�����ص㽲���ļ�����ʱȨ�޼����ж��Ĺ���, Ȼ��������access����������ļ��Ƿ����ĳ�ֿɷ���Ȩ��.
3.2.5.�ļ�Ȩ�޹���2
	���ڽ���chmod�ӿ��������ļ�Ȩ�ޡ�chown�ӿ��������ļ�������umask�ӿ����޸�ϵͳĬ��Ȩ������.
3.2.6.��ȡĿ¼�ļ�
	����Ϊʵս��, д����ʵ�ֶ�ȡ�ļ�Ŀ¼, ���ҽ�Ŀ¼�е��ļ����Ժ��ļ����г���, �Ժ�ĺܶ���Ŀ�ж�����
	���������.
//=======================================================================================================

	(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
		����ʵ���漰���ļ�Ȩ��, �����ڹ����ļ�����ʵ��. Ҫ��ubuntu�н���һ��ԭ��Ŀ¼.
	(!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
//=======================================================================================================
								3.2.1.linux�и����ļ�����
//-------------------------------------------------------------------------------------------------------
	1. ��ͨ�ļ� ( -	regular file)
		
		1) �ı��ļ�. �ļ��е����������ı����ɵ�, �ı�ָ����ASCII���ַ�. �ļ�������ݱ����϶�������(����
		   ʲô�ļ����ݱ����϶�������, ��Ϊ������б����ֻ��1��0), ���ı��ļ��е����ֱ���Ӧ�ñ����Ϊ
		   ������ֶ�Ӧ��ASCII��. ������.c�ļ�, .h�ļ�, .txt�ļ��ȶ����ı��ļ�. �ı��ļ��ĺô����ǿ���
		   �������ɶ����ͱ�д. ����˵�ı��ļ���������Ϊ���෢����.
		   
		2) �������ļ�. �������ļ��д洢�ı�����Ҳ������, ֻ������Щ���ֲ��������ֵı�������, ���Ǿ�����
		   ��������. �����Ŀ�ִ�г����ļ�(gcc�������ɵ�a.out, arm-linux-gcc�����������ɵ�.bin)���Ƕ���
		   ���ļ�.
		
		3) �Աȣ��ӱ���������(�����ٳ��ļ����Ժ����ݵ����)�ı��ļ��Ͷ������ļ���û���κ�����. ����һ��
		   �ļ�������������. ��������ⷽʽ��ͬ, �������Щ���־͵������ִ�������Ƕ������ļ�, �����
		   ��Щ���ְ���ĳ�ֱ����ʽȥ������ı��ַ�, ������ı��ļ�.
		   
		4) �������֪��һ���ļ����ļ��ļ����Ƕ������ļ��� ��linuxϵͳ�����ǲ�������������(Ʃ��֮ǰѧ��
		   ��open��read��write�ȷ��������ļ��ļ��Ͷ������ļ�ʱһ������û��), ���������޷����ļ�����
		   ׼ȷ֪���ļ���������, ����ֻ�ܱ�����֪������ļ�������Ȼ�����������͵��÷�ȥ����. ��ʱ���
		   ��һЩ��׺������Ϊ�ı���ļ�������.
		   
		5) ʹ���ı��ļ�ʱ, �����÷��������ı��ļ��༭��ȥ�������༭��. �������ı��ļ��༭����vim��
		   gedit��notepad++��SourceInsight��, ��������Щ�ı��ļ��༭��ȥ���ļ���ʱ��, �༭����read
		   �����ļ���������������, Ȼ���ձ����ʽȥ���뽫�仹ԭ������չ�ָ�����. ������ı��ļ��༭
		   ��ȥ��һ���������ļ�����Σ� ��ʱ��༭������Ϊ����������ļ������ı��ļ�Ȼ����ͼȥ�����
		   �������, ���ǽ�����̺ܶ����ֲ�����Ӧ��������������Գ�������.
		   
		6) �������ö������Ķ�����ȥ��ȡ�ı��ļ�����ô�����ó��ľ����ı���������Ӧ�Ķ����Ƶı���.

	2. Ŀ¼�ļ�( d	directory)

		1) Ŀ¼�����ļ���, �ļ�����linux��Ҳ��һ���ļ�, �����������ļ�. ��vi��һ���ļ��о��ܿ���, 
		   �ļ�����ʵҲ��һ�������ļ�, ���������ݰ�������ļ���·��, �����ļ���������ļ��б�.
		   
		2) �����ļ��������ļ��Ƚ�����, �������ʺ�����ͨ�ķ�ʽ����д. linux����ʹ�������һЩAPI��
		   ר�Ŷ�д�ļ��е�.
		
		3) vim 3.1.9  // ��һ��Ŀ¼�ļ�:
		
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
		
	3. �ַ��豸�ļ�( c	character)
	4. ���豸�ļ�  ( b	block)
	
		1) �豸�ļ���Ӧ����Ӳ���豸, Ҳ����˵����ļ���Ȼ���ļ�ϵͳ�д���, ���ǲ���������������Ӳ����
		   ��һ���ļ�, �����ļ�ϵͳ�������������(�������ļ�ϵͳ, ��/dev /sys /proc��).
		   
		2) �����ļ�ϵͳ�е��ļ���������ܻ���˵����ֱ�Ӷ�д��, ������һЩ�����API��������ʹ�õ�, ����
		   �������׶λ����.

	5. �ܵ��ļ�( p 	pipe)
	
		linux�е�һ��ͨ���ֶ�, ����ùܵ�ͨ��, ����Ҫ����һ���ܵ��ļ�.
	
	6. �׽����ļ�( s	socket)
	7. ���������ļ�( l	link)

//=======================================================================================================
								3.2.2.�����ļ����Ի�ȡ
//-------------------------------------------------------------------------------------------------------
	1. stat()��fstat()��lstat()�������
	
		1) ÿ���ļ��ж�����������ļ���һЩ����(������Ϣ�Ǵ������ļ������е�, �����������ļ�������һ��
		   ���Ա�vi�򿪿���, ������Ϣֻ�ܱ�ר�õ�API�򿪿���).
		   
		2) �ļ�������Ϣ�鿴��API��������stat()��fstat()��lstat(), ��������һ��, ������ͬ, ϸ�����в�ͬ.
		
		3) linux�������»�����ȥ��stat����ȥ�鿴�ļ�������Ϣ, ʵ����stat�����ڲ�����ʹ��stat()ϵͳ����
		   API��ʵ�ֵ�.
		   
		4) stat���API�����þ������ں˽�����Ҫ�������Ե��ļ���������Ϣ�ṹ���ֵ�������Ǵ��ݸ�stat()��
		   ����buf��, ��stat���API���ô��ں˷��ص�ʱ��buf�оͱ�������ļ�����ȷ��������Ϣ, Ȼ������ͨ
		   ���鿴buf���ֽṹ�������Ԫ�ؾͿ��Ե�֪����ļ��ĸ���������.
		   
		5) fstat��stat�������ǣ�stat�Ǵ��ļ��������õ��ļ�������Ϣ�ṹ��, ��fstat�Ǵ�һ���Ѿ��򿪵��ļ�
		   fd�����õ�һ���ļ���������Ϣ. �����õ�ʱ������ļ�û�д�(���ǲ�������ļ�������ֻ��ϣ��
		   �õ��ļ�����)�Ǿ���stat, ����ļ��Ѿ�������Ȼ��Ҫ�����Ǿ���fstatЧ�ʻ����(stat�ǴӴ���ȥ
		   ��ȡ�ļ���, ��fstat�Ǵ��ڴ��ȡ��̬�ļ���).
		   
		6) lstat��stat/fstat�Ĳ�����ڣ����ڷ��������ļ�, stat��fstat���ĵ��Ƿ��������ļ�ָ����ļ���
		   ����, ��lstat���ĵ��Ƿ��������ļ����������.

		�ܽ�:
				1) linux��������stat����, �鿴�÷�: man 1 stat. 
				
					stat - display file or file system status
					
				2) �������в鿴a.out�ļ���Ϣ: stat a.out
					
					  File: ��a.out��
					  Size: 7295      	Blocks: 0          IO Block: 1024   regular file
					Device: 1ah/26d	Inode: 132         Links: 1
					Access: (0777/-rwxrwxrwx)  Uid: (    0/    root)   Gid: (    0/    root)
					Access: 2023-07-18 08:25:36.207199400 +0800
					Modify: 2023-07-18 08:25:36.207199400 +0800
					Change: 2023-07-18 08:25:36.207199400 +0800
					 Birth: -
					 
				3) 	ʹ��ϵͳ����API stat()����, �鿴�÷�: man 2 stat
				
				
				   #include <sys/types.h>
				   #include <sys/stat.h>
				   #include <unistd.h>

				   int stat(const char *path, struct stat *buf);
				   int fstat(int fd, struct stat *buf);
				   int lstat(const char *path, struct stat *buf);
				   
				   a) const char *path; ˵�����ָ��ִ�е����ݲ���Ҫ�ı�.
				   b) struct stat *buf; û�м�const , ˵��ָ��ָ���������Ҫ���ı�, ��������Ͳ���.
			
	2. struct stat�ṹ����
	
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

	
		1) struct stat���ں˶����һ���ṹ�壬��<sys/stat.h>���������������ǿ����á�����ṹ���е�����Ԫ�ؼ������������ǵ��ļ�������Ϣ��

		2) st_uid, st_gid ��������. ��һ�ڵ��ļ���Ϣ:
			Access: (0777/-rwxrwxrwx)  Uid: (    0/    root)   Gid: (    0/    root)
			/root �û���ID����0.
		3) st_rdev: �����ļ���ʹ��, ��ͨ�ļ��ò���.
		4) st_mtime: modification, ���ݵ��޸�.
		   st_ctime: status change, �ı����ļ�������, ����ɶ���д��ִ�е�.
			
	3. д���������鿴һЩ����������Ϣ
		
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
			
			memset(&buf, 0, sizeof(buf));		// memset��buf��ȫ��0
			ret = stat(NAME, &buf);				// stat��buf����������
			if (ret < 0)
			{
				perror("stat");
				exit(-1);
			}
			// �ɹ���ȡ��stat�ṹ�壬���п��Եõ�����������Ϣ��
			printf("inode = %d.\n", buf.st_ino);
			printf("size = %d bytes.\n", buf.st_size);
			printf("st_blksize = %d.\n", buf.st_blksize);
			
			return 0;
		}		
		
		�ܽ�: 
				1) ������һ���ṹ�����buf, ��ʼ��Ϊ0�����ַ���:
					a) struct stat buf = {0};
									// �γ�˵"����GCC��һ�������ַ�...."
					b) memset(&buf, 0, sizeof(buf));
					
				2) ����ͨ������ʹ�õĺ�����man�ֲ�鵽������Ҫ������ͷ�ļ�.	

//=======================================================================================================
								3.2.3.stat������Ӧ�ð���
//-------------------------------------------------------------------------------------------------------
	1. �ô����ж��ļ�����
	
		1) �ļ����;���-��d��l������
		
		2) �ļ������е��ļ����ͱ�־��struct stat�ṹ��� mode_t  st_modeԪ����, ���Ԫ����ʵ��һ����λ
		   �������һ��λ��־(�е�������ARM CPU��CPSR�Ĵ�����ģʽλ����). ��������кܶ����־λ��ͬ��
		   ��, ��¼�˺ܶ���Ϣ, ���Ҫ����ʱ��λ&������֪�������, ������Ϊ��Щλ���岻���׼�ס, ���
		   linuxϵͳ��������ȶ�����˺ܶ����������Ӧ����.
		   
		3) Ʃ�� S_ISREG �귵��ֵ��1��ʾ����ļ���һ����ͨ�ļ�, ����ļ�������ͨ�ļ��򷵻�ֵ��0.

           S_ISREG(m)  is it a regular file?
           S_ISDIR(m)  directory?
           S_ISCHR(m)  character device?
           S_ISBLK(m)  block device?
           S_ISFIFO(m) FIFO (named pipe)?
           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

		4) �����ж�:
		
			result = S_ISREG(buf.st_mode);			// result=1, ˵������ͨ�ļ�.
			
			
	2. �ô����ж��ļ�Ȩ������
	
		1) st_mode�г��˼�¼���ļ�����֮��, ����¼��һ����Ҫ��Ϣ���ļ�Ȩ��.
		
		2) linux��û�и��ļ�Ȩ�޲����ṩ�����, ��ֻ���ṩ��λ����. ��������ֻ����λ�������Լ��ж��Ƿ�
		   ������ӦȨ��.
	
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
		
		3) �ж��ļ��Ƿ�ɶ�
		
			unsigned int result = ((buf.st_mode & S_IRUSR)? 1: 0);
			printf("file owner: %u.\n", result);

			�ܽ�:
					�����е�ls -l ����, Ҳ��ͨ�����ַ�ʽͨ��ϵͳ����APIʵ�ֵ�.
					
//=======================================================================================================
								3.2.4.�ļ�Ȩ�޹���1
//-------------------------------------------------------------------------------------------------------
	1. st_mode�м�¼���ļ�Ȩ��λ
	
		1) st_mode��������һ��32λ����(���;���unsinged int), ��������ÿһ��λ��ʾһ������.
		
		2) �ļ����ͺ��ļ���Ȩ�޶���¼��st_mode��. �����õ�ʱ��ʹ��ר�ŵ�����ȥȡ����Ӧ��λ���ɵ�֪��Ӧ
		   ����Ϣ��
		   
           S_IFMT     0170000   bit mask for the file type bit fields	// 4��biteλ��ʾ�ļ�����.
           S_IFSOCK   0140000   socket									// �ļ�����-socket
           S_IFLNK    0120000   symbolic link
           S_IFREG    0100000   regular file
           S_IFBLK    0060000   block device
           S_IFDIR    0040000   directory
           S_IFCHR    0020000   character device
           S_IFIFO    0010000   FIFO
		   
	2. ls -l��ӡ����Ȩ���б�
	
		-rwxrwxrwx 1 root root   21 Mar  2  2016 1.txt

		1) 123456789 һ��9λ, 3��һ��. 
			��һ��������ʾ�ļ�������(owner��user)�Ը��ļ��Ŀɶ�����д����ִ��Ȩ��.
			�ڶ�������λ��ʾ�ļ����������ڵ���(group)�Ը��ļ���Ȩ��.
			����������λ��ʾ�����û�(others)�Ը��ļ���Ȩ��.
			
		2) ������������ļ�����˭, һ����˵�ļ�����ʱ�������Ǵ�������ļ����Ǹ��û�. ��������һ���ļ�
		   ����֮�󻹿�����"chown����"ȥ�޸�һ���ļ�������, ��������"chgrp����"ȥ�޸�һ���ļ����ڵ���.
		   
		   
		3) ��һ��root��ʾ��ǰ����, �ڶ����û���ʾ������.  ?????? 

	3. �ļ�����ʱ��Ȩ�޼�����
	
		1) һ������a.out��ִ��, a.out����ͼȥ����һ���ļ�1.txt, ��ʱ������ж�a.out�Ƿ���ж�1.txt��
		   ĳ�ֲ���Ȩ���أ�
		   
		2) �ж������ǣ����� 1.txt����9��Ȩ��λ, �涨��3����(user��group��others)�Ը��ļ��Ĳ���Ȩ��. 
		               ���������ж� 1.txt �Ƿ��ܱ�a.out������, �ؼ��ȸ���� a.out �� 1.txt������������.
					   ׼ȷ��˵�ǿ� a.out ��˭ִ��(���ǿ�a.out����), Ҳ���ǵ�ǰ����(����)���ĸ��û���
					   ����.
			�ܽ�:
					1) ��aston�û���, ����һ���ļ� /home/aston/test.c
						ls -l �鿴:
						
						-rw-rw-r--  1 aston aston     0 Jul 18 20:58 test.c
						
					2) 	��root�û���, cp /home/aston/test.c ~/
						Ȼ��ls -l �鿴:
						
						-rw-r--r-- 1 root root         0 Jul 18 20:59 test.c

					3) 	��root�û���, cp -p /home/aston/test.c ~/ 
					
						(!!!!!) -p     same as --preserve=mode,ownership,timestamps

						����ls -l �鿴:
						
						-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 test.c
						
					4) (!!!!!!??????) �γ���˵��:
					
						-rw-r--r-- 1 root  root          0 Jul 18 20:59 1.txt
						-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 2.txt

						-rwxr-xr-x 1 root  root       5733 Apr 25 12:30 a.out
						
						����root�û�ȥִ��a.out����, Ȼ�����2.txt. Ȼ��2.txt�ļ����û��������鶼��aston,
						�Ƕ���2.txt��˵, root�û����������û�(others), ��û��Ȩ�޿�2.txt�����������λ.
						
						(��)����root�û�ȥִ��a.out����, Ȼ�����1.txt. ִ�г����root�û������������û�
						(user), ��û�в���Ȩ��, ��1.txt��һ�������λ.
						
						(!!!???) root �û�ʱ��Ȩ�û�, �����������. 
						         ����½�һ���û� addusr tempusr.  �������1.txt���������û�.
								 
				(?????) �û�, �û���ȸ�����⻹������, ��ʱ����Ҫ�����˽�.
						
		3) �ղ�����˵�����ҵķ���, ���׶Բ��Ի�����֤.
		
			#define NAME "1.txt"

			int main(void)
			{
				int ret = -1;
				
				ret = open(NAME, O_RDONLY);
				if (ret > 0)
				{
					printf("�ɶ�  	");
					close(ret);
					
				}
				else
				{
					perror("read");
				}
				

				ret = open(NAME, O_WRONLY);
				if (ret > 0)
				{
					printf("��д  	");
					close(ret);
				}
				else
					perror("write");
				
				return 0;
			}

//=======================================================================================================
								3.2.5.�ļ�Ȩ�޹���2
//-------------------------------------------------------------------------------------------------------
	1. access()�������Ȩ������
	
		1) �ı�Ȩ�޹ܿ���ʵ������, һ����Ѻ����׵�ȷ����һ���ļ��Ƿ����ĳ��Ȩ��(��û��Ȩ�޳��˸��ļ�
		   �����й�ϵ, ����˭ȥִ���й�ϵ). �����������Ӧ���ǣ��ڲ���ĳ���ļ�֮ǰ���жϵ�ǰ�Ƿ���
		   Ȩ�����������, ������������û�����ṩ������Ϣ���û�.
		   
		2) access()�������Բ��Եõ���ǰִ�г�����Ǹ��û��ڵ�ǰ�Ǹ������¶�Ŀ���ļ��Ƿ����ĳ�ֲ���
		   Ȩ��.

			int access(const char *pathname, int mode);
		
			F_OK tests for the existence of the file. R_OK, W_OK, and X_OK test whether the file exists 
			and grants read, write, and execute  permissions.
			
			int fchmod(int fd, mode_t mode);


		3) ����:
		
			#define NAME 	"3.txt"
			
			ret = access(NAME, F_OK);
			if (ret < 0)
			{
				printf("�ļ������� \n");
				return -1;
			}
			else
			{
				printf("�ļ�����	");
			}

			ret = access(NAME, R_OK);
			if (ret < 0)
			{
				printf("���ɶ� ");
			}
			else
			{
				printf("�ɶ� ");
			}			
		
		�ܽ�: �����в���һ���ļ�ʱ, һ��Ҫ��acess()����ȥ����һ���Ƿ����, �Ƿ���Ȩ��.

	2. chmod/fchmod��Ȩ���޸�
	
		1) chmod��һ��linux����, �����޸��ļ��ĸ���Ȩ������. chmod����ֻ��root�û�����Ȩ��ȥִ���޸�.
		
			(!!!!!!)����һ���ļ�, ��user�û�����ʹ��chmod����.
			root�û������޸����е��ļ�. �����û�ֻ���޸��Լ����ļ�.
			
		2) chmod������ʵ�ڲ�����linux��һ����chmod��APIʵ�ֵ�.
		
			man 1 chmod			// ���ĵ�������������
			man 2 chmod			// ���ĵ���ϵͳ����API��chmod()����.

		3) Ӧ��:
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
			
			S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWOTH	// user�û��ɶ���д��ִ��, ���û��ɶ�, 
															// �����û���д
															
		4) 	fchmod(): ����һ���򿪵��ļ�, ����ͨ��fdʹ���������.
		
	3. chown/fchown/lchown�������޸�
	
		1) linux���и�chown�������޸��ļ�����.
		
		2) chown��������chown() APIʵ�ֵ�.
		
		3) chown()ʹ��: ��
		
		4) ������chown����:
			����һ���ļ�
			-rw-rw-r-- 1 aston aston         0 Jul 18 20:58 test.c
			chown root test.c
			-rw-rw-r-- 1 root aston         0 Jul 18 20:58 test.c
			chgrp root test.c
			-rw-rw-r-- 1 root root         0 Jul 18 20:58 test.c
		5) 	fchown, ����ļ���, ����ʹ��fdִ�к���.

	4. umask���ļ�Ȩ������
	
		1) �ļ�������linuxϵͳ��ά����һ��ȫ������, umask�������������趨����ϵͳ���´������ļ���Ĭ��
		   Ȩ�޵�.
		   
		2) umask���������umask() APIʵ�ֵ�.
		
		3) man 2 umask
		
			 mode_t umask(mode_t mask);
		4) man 1 umask (û�и�����??????)
		
		5) ��������, umask���Բ鿴�ļ�ģʽ����mask.
		   ���� umask 0044
		   
		   (?????) �������ļ���û�п�ִ��Ȩ��? ���0044,0066����ζ�Ӧ��?

//=======================================================================================================
								3.2.6.��ȡĿ¼�ļ�
//-------------------------------------------------------------------------------------------------------
3.2.6.��ȡĿ¼�ļ�


	1. opendir()��readdir()����
	
		1) opendir()��һ��Ŀ¼��õ�һ��DIR���͵�ָ���readdir()ʹ��.
		
			DIR *opendir(const char *name);
			DIR *fdopendir(int fd);
			
			The  opendir()  function opens a directory stream corresponding to the directory name, 
			and returns a pointer to the directory stream.  The stream is positioned at the first 
			entry in the directory.
		
		2) readdir()��������һ�ξͻ᷵��һ��struct dirent���͵�ָ��, ���ָ��ָ��һ���ṹ�����, 
		   ����ṹ����������¼��һ��Ŀ¼��(��νĿ¼�����Ŀ¼�е�һ�����ļ�).
		   
			struct dirent *readdir(DIR *dirp);
			int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

			The  readdir() function returns a pointer to a dirent structure representing the next 
			directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching 
			the end of the directory stream or  if  an error occurred.
		   
		3) readdir()����һ��ֻ�ܶ���һ��Ŀ¼��, Ҫ�����Ŀ¼�����е�Ŀ¼������ε���readdir����.
		   readdir()�����ڲ����ס�ĸ�Ŀ¼���Ѿ����������ĸ���û��, ���Զ�ε��ú󲻻��ظ������Ѿ�
		   ���ع���Ŀ¼��. ��readdir��������NULLʱ�ͱ�ʾĿ¼�����е�Ŀ¼���Ѿ�������.

	2. dirent�ṹ��

           struct dirent {
               ino_t          d_ino;       /* inode number */
               off_t          d_off;       /* not an offset; see NOTES */
               unsigned short d_reclen;    /* length of this record */
               unsigned char  d_type;      /* type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* filename */
           };		/*
		1) �ļ���Ҳ��һ��������ļ�, Ҳ��inode.
		
		2) d_type      
		
		   DT_BLK      This is a block device.
		   DT_CHR      This is a character device.
		   DT_DIR      This is a directory.
		   DT_FIFO     This is a named pipe (FIFO).
		   DT_LNK      This is a symbolic link.
		   DT_REG      This is a regular file.
		   DT_SOCK     This is a UNIX domain socket.
		   DT_UNKNOWN  The file type is unknown.

	3. ��ȡĿ¼ʵս����
		
		int main(int argc, char **argv)
		{
			DIR *pDir = NULL;					// DIR ָ��
			struct dirent * pEnt = NULL;		// dirent ָ��
			unsigned int cnt = 0;
			
			if (argc != 2)
			{
				printf("usage: %s dirname\n", argv[0]);
				return -1;
			}
			
			pDir = opendir(argv[1]);
			if (NULL == pDir)					// �鿴man�ֲ�, ����֪������ֵΪNULLʱ��ʧ��. 
			{
				perror("opendir");
				return -1;
			}
			
			while (1)
			{
				pEnt = readdir(pDir);			// !!!!!
				if(pEnt != NULL)
				{
					// �������ļ����ڴ˴������ļ�
					printf("name��[%s]	,", pEnt->d_name);
					cnt++;
					if (pEnt->d_type == DT_REG)
					{
						printf("����ͨ�ļ�\n");
					}
					else
					{
						printf("������ͨ�ļ�\n");
					}
				}
				else
				{
					break;
				}
			};
			printf("���ļ���Ϊ��%d\n", cnt);
			
			return 0;
		}		

	4. �����뺯������
	
		1) ��Щ�����ǿ��������Щ�ǲ��������, ����������ȥ�ٶ�.
		
		2) readdir()����������ǰ��Ӵ���һЩ�����ǲ�ͬ��, ����readdir����ֱ�ӷ�����һ���ṹ�����ָ��,
		   ��Ϊreaddir�ڲ��������ڴ沢�Ҹ����Ƿ����˵�ַ. ��ε���readdir��ʵreadir�ڲ��������ظ�����
		   �ڴ����ʹ�õ�һ�ε���readdirʱ������Ǹ��ڴ�. �����Ʒ�����readdir��������Ĺؼ�.
		   
		3) readdir�ڶ�ε���ʱ���й�����, �������Ҳ����readdir�����ǲ��������.
		
		4) �⺯������һЩ��������տ�ʼ�ṩʱ���ǲ��������, ������ʶ�����ַ�ʽ����ȫ, �������·�װ��
		   C��, �ṩ�˶�Ӧ�Ŀ��ظ��汾(һ���ǲ�������汾������_r).
		   
		(?????) readdir_r()�����Ĳ���û�н�, �ȱ���.

//=======================================================================================================

















