/*
//=======================================================================================================
									3.7.linux�߳�ȫ��
//=======================================================================================================
3.7.1.���۽���
3.7.2.�̵߳�����
3.7.3.�̳߳�������
3.7.4.�߳�ͬ��֮�ź���1
3.7.5.�߳�ͬ��֮�ź���2
3.7.6.�߳�ͬ��֮������ 
3.7.7.�߳�ͬ��֮��������
//=======================================================================================================
3.7.1.���۽���
	�����ٴλع˽���, ʹ�ö���̵ķ�ʽ���ͬʱ��ȡ���̺���������, �Ӷ��ô�������̵ĵ������Դ�����
	IO�����������.
3.7.2.�̵߳�����
	����ʹ���߳��ٴ���д���ͬʱ��ȡ���̺���������, �ô�������̺��̵߳���֮ͬ��, Ȼ���ٽ����̻߳�
	�Ƶ�����.
3.7.3.�̳߳�������
	���ڶ��̱߳���г��õ�һЩ��Ҫ�������н���, ��ʵΧ���Ž����̱߳�̵�ϸ��Ҳ�ͳ�����.
3.7.4.�߳�ͬ��֮�ź���1
	���ڿ�ʼ�����߳�ͬ��, ��Ҫ���߳�ͬ���ĸ����ԭ��, Ȼ��ʼ���߳�ͬ���ĵ�һ�ַ����ź���.
3.7.5.�߳�ͬ��֮�ź���2
	���ڽ��Ͻڽ����ź��������߳�ͬ��, ���Ҵ��㿪ʼд��һ����������ʾ�ź������ʵ���߳�ͬ��,
3.7.6.�߳�ͬ��֮������ 
	�������뻥����, ����ʹ�û�����������ʵ���߳�ͬ��, �ٽ��д���ʵ��.
3.7.7.�߳�ͬ��֮��������
	���ڽ����߳�ͬ���ĵ����ְ취��������, ���ҽ��д�����ʵ��ʹ����������������Ͻڿε�����.
//=======================================================================================================
									3.7.1.���۽���
//-------------------------------------------------------------------------------------------------------
	1. �����ʵ��ͬʱ��ȡ���̺����
		
		1) ˼·: �����ӽ���, Ȼ���ӽ����зֱ���ж����̺����Ĺ���.

		2) �������:
		
			int main(void)
			{
				// ˼·���Ǵ����ӽ��̣�Ȼ���ӽ����зֱ���ж����̺����Ĺ���
				int ret = -1;
				int fd = -1;
				char buf[200];
				
				ret = fork();										// �����ӽ���
				if (ret == 0)
				{
					// �ӽ���
					fd = open("/dev/input/mouse1", O_RDONLY);		// ��������Ϊ������
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
						printf("�������������ǣ�[%s].\n", buf);
					}	
				}
				else if (ret > 0)
				{
					// ������
					while (1)
					{
						memset(buf, 0, sizeof(buf));
						printf("before read.\n");
						read(0, buf, 5);
						printf("�������̵������ǣ�[%s].\n", buf);			
					}
				}
				else
				{
					perror("fork:");
				}
				return 0;
			}
			
	

	2. ʹ�ý��̼���������
	
		1) CPUʱ�ָ���, ������CPU����ʵ�ֺ���ϵĲ���.
		2) ʵ�ֶ�����ϵͳ����(������������ǿ͹۵�).
		
	3. ���̼���������
	
		1) ���̼��л�������.
		2) ���̼�ͨ���鷳����Ч�ʵ�.
		
			�������������Ȼ�����. �кõķ���Ҳ�в��õķ���, ͨ�ž��ǲ��õ�һ����, ͨ�ź��鷳Ч�ʵ�.
		
	4. ������������̼߳���
	
		1) �̼߳��������˽��̼���ʵ�ֶ����������. (�߳�Ҳ������ϵͳ����)
		2) �̵߳ĸĽ��������̼߳��л����̼߳�ͨ����������Ч��.
		3) ���߳��ڶ����CPU�����������.

//=======================================================================================================
									3.7.2.�̵߳�����
//-------------------------------------------------------------------------------------------------------
	1. �̵߳�����
		
		���ڻ�û���̵߳�һЩ����, ��ʹ��ʵ����һ�ڵļ������ͬʱ��ȡ�Ĺ���.
	
	2. ʹ���̼߳���ͬʱ��ȡ���̺����
	
		void *func(void *arg)
		{
			while (1)
			{
				memset(buf, 0, sizeof(buf));
				printf("before read.\n");
				read(0, buf, 5);
				printf("�������̵������ǣ�[%s].\n", buf);			
			}	
			
		}

		int main(void)
		{
			// ˼·���Ǵ����ӽ��̣�Ȼ���ӽ����зֱ���ж����̺����Ĺ���
			int ret = -1;
			int fd = -1;
			pthread_t th = -1;									// ���ڽ����´������̵߳ı�ʶ��
			
			ret = pthread_create(&th, NULL, func, NULL);		// �����߳�
			
			if (ret != 0)
			{
				printf("pthread_create error.\n");
				return -1;
			}
			// ������
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
				printf("�������������ǣ�[%s].\n", buf);
			}	
			return 0;
		}		
	
		(!!!!!!) ע������ʱ��������̬���ӿ�: gcc xxx.c -lpthread
	
	3. linux�е��̼߳��
	
		1) һ������������.
		2) �߳��ǲ����ں˵��ȵ���С��Ԫ.
		3) һ�������п����ж���߳�.
		
	4. �̼߳���������
	
		1) �����һ���ɱ�OS����.
		2) ͬһ���̵Ķ���߳�֮������׸�Ч��ͨ��.
			�൱��������������ͨ��, ����ʹ��ȫ�ֱ���.
		3) �ڶ����CPU(�Գƶദ�����ܹ�SMP)�ܹ���Ч�����.

//=======================================================================================================
									3.7.3.�̳߳�������
//-------------------------------------------------------------------------------------------------------
	1. �̳߳�������

		1) �̴߳��������
		
			pthread_create			���߳������������̵߳�
			pthread_join			���߳������ȴ�(����)�������߳�
			pthread_detach			���߳������������߳�, ��������̲߳�����ȥ�������߳�
			
			�ܽ�: 
				��һ�ڳ���û�п������̻߳�������. ��Ϊ���߳�����ѭ��, Ӧ����pthread_detach()����.

		2) �߳�ȡ��
		
			pthread_cancel			һ�㶼�����̵߳��øú���ȥȡ��(�����Ͻ���)���߳�
			pthread_setcancelstate	���߳������Լ��Ƿ�����ȡ��
			pthread_setcanceltype

		3) �̺߳����˳����(���߳��Լ��˳�)
		
			pthread_exit��return	�˳�
			pthread_cleanup_push
			pthread_cleanup_pop

		4) ��ȡ�߳�id

			pthread_self			
	
	2. pthread_create �̴߳�������
		
       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

       Compile and link with -pthread.	
	   
		1) (!!!!!!) ����ʱҪ�� -lpthread

		2) pthread_create�������ڴ���һ�����̲߳�ʹ������ָ���ĺ���. ������ÿ����������ϸ���ͣ�

			a) pthread_t *thread���˲�����һ��ָ��pthread_t���͵�ָ��, ���ڽ����´������̵߳ı�ʶ��.
			   pthread_t������һ���޷��ų�����(unsigned long int).
			b) const pthread_attr_t *attr���˲�����һ��ָ��pthread_attr_t���͵�ָ��, �����������߳�
			   ������. �������NULL, ��ô��ʹ��Ĭ�ϵ��߳�����. Ҫ�Զ����߳�����, ��ʹ��
			   pthread_attr_init��pthread_attr_setdetachstate�Ⱥ���.
			c) void *(*start_routine) (void *)���˲�����һ��ָ������ָ��. �ú����������߳�������,
			   �����ķ���ֵ����Ϊvoid *, ������һ��void *���͵Ĳ���.
			d) void *arg���˲�����һ��ָ��void��ָ��, �������ݸ�start_routine����.
			e) pthread_create������ԭ��ͨ��λ��glibc����.
			f) On  success, pthread_create() returns 0; on error, it returns an error number, and 
			   the contents of *thread are unde�\fined.
			   
	3. pthread_join (���߳������ȴ�(����)�������߳�)
	
       int pthread_join(pthread_t thread, void **retval);

       Compile and link with -pthread.
	
	4. pthread_detach (���߳������������߳�, ��������̲߳�����ȥ�������߳�)
	
       int pthread_detach(pthread_t thread);

       Compile and link with -pthread.

	5. 	pthread_cancel	(һ�㶼�����̵߳��øú���ȥȡ�����߳�)

	    int pthread_cancel(pthread_t thread);

		Compile and link with -pthread.
		
		�Ƿ���Խ������߳�, ���ÿ����߳��Ƿ�����ȡ��.

	6.	pthread_setcancelstate,pthread_setcanceltype	
	
       int pthread_setcancelstate(int state, int *oldstate);
       int pthread_setcanceltype(int type, int *oldtype);
	
	7. pthread_exit (���߳��Լ��˳�)

		void pthread_exit(void *retval);

		retval�ᱻ���ظ����̵߳�pthread_join()����. pthread_join()�����ĵڶ��������Ƕ���ָ��.
		
		(!!!!!!) ���߳��еķ��ؿ���ʹ��return����, ���ǲ�����exit()����������, ��Ϊexit����ʱ,
		          ��ѽ��̽���.

	8. 	pthread_cleanup_push(),	pthread_cleanup_pop()
	
       void pthread_cleanup_push(void (*routine)(void *), void *arg);
       void pthread_cleanup_pop(int execute);

		(?????) һЩ���������ܲ���ȷ, �������Կγ̵ľ���.
		
		1) ���߳̿���ͨ�� pthread_cancel ������ֹ���߳�, �������߳��п��ܻ���δ���ͷŵ���Դ, ����
		    ��ȡ�˻���������Դ. ��Ҫ����.
			
		2) pthread_cleanup_push �������Ǵ���ջ֡, ���ûص�����, �ù����൱����ջ. �൱��ѹ����һ��
		   �ص�����, �ڳɶԳ��ֵ�pthread_cleanup_pop()��������ʱ��ִ��(�ú�������Ϊ��0ʱ, Ϊ0ʱ����
		   ����).
		   
		3) ������������ɶ�ʹ��.
		
		4) ���߳���, cnt��ʾ��Դ������.
			
			if(cnt==0)
			{
				cnt++;					// ����
				
				pthread_cleanup_push(func, arg);
				
				// ��Դxxʹ����
				
				pthread_cleanup_pop(0);				// 
				
				cnt--;					// ����
			}

			void func(void)
			{
				cnt--					// ����
			}

			a) ������߳�ȡ��ʱ�ӽ���������������, ����ǰ�ĳ����, ���������.
			b) pthread_cleanup_push(func, arg), ѹջһ���ص�����.
			c) pthread_cleanup_pop(0), 0��ʾִ�лص�����. ��0��ʾ��ִ��.

	9. pthread_self ��ȡ�߳�ID
	
		pthread_t pthread_self(void);

//=======================================================================================================
									3.7.4-5.�߳�ͬ��֮�ź���1,2
//-------------------------------------------------------------------------------------------------------
	1. �����û����ն����������ַ�Ȼ��ͳ�Ƹ�����ʾ, ����end�����.
	
		while(1)
		{
			scanf("%s",buf);
			printf("����������%d���ַ�.\n", strlen(buf));
			memset(buf,0,sizeof(buf));
		}
		
		while(scanf("%s",buf))
		{
			printf("����������%d���ַ�.\n", strlen(buf));
			memset(buf,0,sizeof(buf));
		}
		
		(!!!!!) ����д����һ����. 
		(!!!!!) while(scanf("%s",buf))��Զ������ѭ����, ��Ϊscanf()��������, �������ؿ϶��Ƿ�0, ��Զ
		        �����˳�ѭ����.
	
	
	2. ʹ�ö��߳�ʵ�֣����̻߳�ȡ�û����벢�ж��Ƿ��˳�, ���̼߳���.
	
		1) Ϊʲô��Ҫ���߳�ʵ��
		2) ��������ѵ��ǣ�
		3) ���ʲô���߳�ͬ��
		
	3. �ź����Ľ��ܺ�ʹ��
	
		1) �ź�������:
		
			sem_t sem;			// �����߳�, ������һ��ȫ�ֱ���.
			
		2) �ź�����ʼ��:
		
		    int sem_init(sem_t *sem, int pshared, unsigned int value);
			
			a) The pshared argument indicates whether this semaphore is to be shared between the 
			   threads of a process,  or  between processes.

			   If  pshared has the value 0, then the semaphore is shared between the threads of a 
			   process, and should be located at some address that is visible to all threads (e.g., 
			   a global variable, or a variable  allocated  dynamically  on  the heap).

			   If  pshared  is nonzero, then the semaphore is shared between processes, and should 
			   be located in a region of shared  memory. 
				
			   (!!!!!) һ������Ϊ0.	
			
			b) int value, ���ó�ֵ.

		3) �ź�������
		
			int sem_post(sem_t *sem);

		4) �ź�����ȡ

			int sem_wait(sem_t *sem);

		5) �ź�������
		
			int sem_destroy(sem_t *sem);

	4. ����ʵ��:

		// ���̳߳���������ͳ��buf�е��ַ���������ӡ
		void *func(void *arg)
		{
			// ���߳�����Ӧ���и�ѭ��
			// ѭ���������ڵȴ����̼߳����ʱ�����̱߳�������ȥ��ȡbuf�е��ַ�
			// ���ȣ�Ȼ���ӡ����ɺ��ٴα�����
			sem_wait(&sem);
			while (strncmp(buf, "end", 3) != 0)
			{	
				printf("����������%d���ַ�\n", strlen(buf));
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
			
			printf("����һ���ַ������Իس�����\n");
			while (scanf("%s", buf))
			{
				// ȥ�Ƚ��û�������ǲ���end����������˳���������������		
				if (!strncmp(buf, "end", 3))
				{
					printf("�������\n");
					sem_post(&sem);	
					break;
				}
				sem_post(&sem);	
			}
			// �������߳�
			printf("�ȴ��������߳�\n");
			ret = pthread_join(th, NULL);
			if (ret != 0)
			{
				printf("pthread_join error.\n");
				exit(-1);
			}
			printf("���̻߳��ճɹ�\n");
			
			sem_destroy(&sem);
			
			return 0;
		}


	5. ע������:
	
		1) 
			a) ���߳���, ����end���˳�, �������߳�.
		
				// �������߳�
				printf("�ȴ��������߳�\n");
				ret = pthread_join(th, NULL);
				if (ret != 0)
				{
					printf("pthread_join error.\n");
					exit(-1);
				}
				printf("���̻߳��ճɹ�\n");
		
			b) �������߳���, �����while(1)���Ƶ���ѭ��, �����̻߳�һ�»��ղ��ɹ�.
			
				while (1)
				{	
					printf("����������%d���ַ�\n", strlen(buf));
					memset(buf, 0, sizeof(buf));
					sem_wait(&sem);
				}
			
			�ܽ�: ���������ջسɹ�, ��Ϊ���߳�����ѭ��.

//=======================================================================================================
									3.7.6.�߳�ͬ��֮������ 
//-------------------------------------------------------------------------------------------------------
	1. ʲô�ǻ�����
	
		1) �������ֽл�����(mutex)
		
		2) ��غ�����pthread_mutex_init, pthread_mutex_destroy
					 pthread_mutex_lock, pthread_mutex_unlock
					 
			pthread_mutex_lock() ����ʱ, ����Ѿ�����, ������.		 
					 
		3) ���������ź����Ĺ�ϵ��������Ϊ��������һ��������ź���.
		
		4) ��������Ҫ����ʵ��"�ؼ��α���".
		
	2. �û�������ʵ���ϽڵĴ���(���ʵ���û�������̫����)
	
		pthread_mutex_t mutex;

		pthread_mutex_lock(&mutex);
		
		// �ٽ����.
		
		pthread_mutex_unlock(&mutex);

		pthread_mutex_destroy(&mutex);

	ע�⣺
			man 3 pthread_mutex_initʱ��ʾ�Ҳ�������, ˵����û�а�װpthread��ص�man�ֲ�(ϵͳĬ��û��װ).
			��װ������1�����������; 2��sudo apt-get install manpages-posix-dev

//=======================================================================================================
									3.7.7.�߳�ͬ��֮��������
//-------------------------------------------------------------------------------------------------------
	1. ʲô����������
	
	2.��غ���
	
		pthread_cond_init		pthread_cond_destroy
		pthread_cond_wait		pthread_cond_signal/pthread_cond_broadcast

	3. ʹ������������ʵ���Ͻڴ���
		
		1) ���廥����,��������
		
			pthread_mutex_t mutex;
			pthread_cond_t cond;

		2) ���߳������ʻ�, ������������	

			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);

			pthread_cond_signal(&cond);
			
			pthread_mutex_destroy(&mutex);
			pthread_cond_destroy(&cond);

			
		3) ���߳��л�ȡ��������
		
			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);
			printf("����������%d���ַ�\n", strlen(buf));
			memset(buf, 0, sizeof(buf));
			pthread_mutex_unlock(&mutex);
			

	4. �߳�ͬ���ܽ�
		
		1) ��������ʹ��ʱ, ��Ҫһ��������.
		
			pthread_cond_wait(&cond, &mutex);
		
		2) �ȴ���������ʱ, ǰ�������������.

			pthread_mutex_lock(&mutex);
			pthread_cond_wait(&cond, &mutex);
			//---------------------
			// ��������, ִ�в���.
			//---------------------
			pthread_mutex_unlock(&mutex);

//=======================================================================================================






