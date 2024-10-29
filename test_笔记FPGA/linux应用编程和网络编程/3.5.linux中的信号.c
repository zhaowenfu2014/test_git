/*
//=======================================================================================================
									3.5.linux�е��ź�
//=======================================================================================================
3.5.1.ʲô���ź�
3.5.2.�����źŽ���
3.5.3.���̶��źŵĴ���
3.5.4.alarm��pause����
//=======================================================================================================
3.5.1.ʲô���ź�
	���ڽ���ʲô���ź�, �Լ��ź���˭���͡���˭����, ��ô���������, Ŀ����վ��һ���߶�����ʶ�źŵ�����
	������.
3.5.2.�����źŽ���
	���ڶԳ�����Ҫע��ļ����źŽ��н���, �����������źſ�����ʱ����, ����ʱ��ȥ���ĵ�����.
3.5.3.���̶��źŵĴ���
	���ڽ��ܽ��̶��źŵ����ִ�����, signal������sigaction�������������ź�ʱ�Ĳ���.
3.5.4.alarm��pause����
	���ڶ�alarm������pause�������н����ʵս���, ������������ʵ�ֶ����ź��й�.
//=======================================================================================================
									3.5.1.ʲô���ź�
//-------------------------------------------------------------------------------------------------------
	1. �ź����������޵�һ���첽ͨ�Ż��� (����ϵͳ�����, ���������)
	
		1) �źŵ�Ŀ�ģ�����ͨ��.
		2) �ź����첽��(�Ա�Ӳ���ж�), ����������ж�.
		3) �źű�������int�����ֱ��(���ȶ���õ�).
		
	2. �ź���˭����
	
		1) �û����ն˰��°���.
		2) Ӳ���쳣���ɲ���ϵͳ�ں˷����ź�.
		3) �û�ʹ��kill�������������̷����ź�.
		4) ĳ��������������Ҳ�ᷢ���ź�, ��alarm����ʱ�䵽�����SIGALARM�ź�; ����һ�������Ѿ��رյ�
		   �ܵ�writeʱ�����SIGPIPE�ź�(�����̽�������ź�, ��֪���Է��޷����յ���).
		   
	3. �ź���˭������δ���
	
		1) �����ź�.
		2) �����ź�(�źŰ���һ������).
		3) Ĭ�ϴ���(��ǰ����û�����ԵĹ�����ź�, ���ղ���ϵͳĬ�ϵĴ������Ի���ֹ����).
		
			�����ȷ�˺��Ի��ǲ����ź�, ��Ĭ�ϵĴ���ͻ�ʧЧ.

//=======================================================================================================
									3.5.2.�����źŽ���
//-------------------------------------------------------------------------------------------------------
	1. �����źŽ���
	
		1) SIGINT			2		Ctrl+CʱOS�͸�ǰ̨��������ÿ������
		2) SIGABRT			6		����abort�����������쳣��ֹ
		3) SIGPOLL	SIGIO	8		ָʾһ���첽IO�¼����ڸ߼�IO���ἰ
		4) SIGKILL			9		ɱ�����̵��ռ��취
		5) SIGSEGV			11		��Ч�洢����ʱOS�������ź�
		6) SIGPIPE			13		�漰�ܵ���socket
		7) SIGALARM			14		�漰alarm������ʵ��
		8) SIGTERM			15		kill����͵�OSĬ����ֹ�ź�
		9) SIGCHLD			17		�ӽ�����ֹ��ֹͣʱOS���丸���̷����ź�
		10)
		   SIGUSR1			10		�û��Զ����źţ����ú�������Ӧ���Լ�����
		   SIGUSR2			12		�û��Զ����źţ����ú�������Ӧ���Լ�����

	2. ����:
	
		1) CTRL+C, ����SIGINT�źŸ�ǰ̨����.  ���ᷢ����̨����.
		2) abort()�������ú�ᷢ��SIGABRT�ź�. (???? ���̵��øú�����ֹ�Լ�???)
		3) �߼�IO, ��˵�첽ͨ��IO, ���߶�·����IO. �����������¼�.
		   ����IO, ��˵���ļ�IO.
		4) SIGKILL�ź�, �ǲ��ܱ����ص�. ����ϵͳ��Ƴ���, ����Ϊ�˿��Դ��������û�����.
			kill -9 pid  (��Ȼ�����漰��Ȩ������).
		5) SIGSEGV, �δ�����Ϣ�����������ź�. ϵͳ���ͳ���.
		6) SIGPIPE, ���ڶԷ��Ѿ��رյĹܵ�ʱ, �ᷢ������ź�.
		7) SIGTERM, Ҳ��������ֹ���̵��ź�.

//=======================================================================================================
									3.5.3.���̶��źŵĴ���
//-------------------------------------------------------------------------------------------------------
	1. signal��������
	
		#include <signal.h>

		typedef void (*sighandler_t)(int);

		sighandler_t signal(int signum, sighandler_t handler);

		1) sighandler_t ��һ������ָ��.
		2) signal()����������: �����ϵͳע��һ���źŵĴ�����. sighandler_t handlerָ��ָ��ĺ�������
		   �ô�����.
		3) ����ֵ(????)
			signal()  returns  the previous value of the signal handler, or SIG_ERR
			on error.  In the event of an error,  errno  is  set  to  indicate  the
			cause.

	2. ��signal��������SIGINT�ź�

		1) Ĭ�ϴ���
		
			Ĭ�ϴ�����ǲ�����, ֮ǰ�ĳ����ǲ��ܵ�. 
			�ж�����CTRL+C, ����SIGINT�ź�, ��ֹ��ǰ����.
		
		2) ���Դ���
		
		3) ������
		
			void func(int sig)
			{
				if (SIGINT != sig)
					return;
				
				printf("func for signal: %d.\n", sig);
			}

			int main(void)
			{
				signal(SIGINT, func);					// ע��һ���źŴ�����.

				printf("before while(1)\n");
				while(1);
				printf("after while(1)\n");
				
				return 0;
			}		
			
			a) ���к�, CTRL+C������ֹ����.
			b) CTRL+C, ����func����.
			c) ��ιر�?  ����������һ���ж���, ps -ajx ��ѯPID, Ȼ�� kill -9 pid.		

	3. ϸ�ڣ�
	
		1) signal������һ�����������źŷ�������Զ�ִ�а󶨵Ĳ����������Ұ��źű����Ϊ���δ���
		   ������.
		   
		2) signal�ķ���ֵ�ڳ���ʱΪSIG_ERR, �󶨳ɹ�ʱ���ؾɵĲ�����.
			
			a) SIG_ERR �� /usr/include/i386-linux-gnu/bits/signum.h ���ж���:
			
				/* Fake signal functions.  *
				#define SIG_ERR ((__sighandler_t) -1)           /* Error return.  *
				#define SIG_DFL ((__sighandler_t) 0)            /* Default action.  *
				#define SIG_IGN ((__sighandler_t) 1)            /* Ignore signal.  *

				__sighandler_t ���ں�ʹ�õ�, sighandler_t��Ӧ�ò�ʹ�õ�. 
			
			b) SIG_DFL��Ĭ�ϴ���:
			
				signal(SIGINT, SIG_DFL);		// ָ���ź�SIGINTΪĬ�ϴ���
				
			c) SIG_IGN �Ǻ��Դ���:
				
				signal(SIGINT, SIG_IGN);		// ָ���ź�SIGINTΪ���Դ���
				
	4. signal�������ŵ��ȱ��
	
		1) �ŵ㣺�򵥺���, �����źų���.
		
		2) ȱ�㣺�޷���ֱ�ӵ�֪֮ǰ���õĶ��źŵĴ�����.
		
		    The behavior of signal() varies across UNIX versions, and has also var�\
		    ied historically across different versions of Linux.   Avoid  its  use:
            use sigaction(2) instead.  See Portability below.
			
		Portability
		    The  only  portable use of signal() is to set a signal's disposition to
		    SIG_DFL or SIG_IGN.  The semantics when using signal() to  establish  a
		    signal handler vary across systems (and POSIX.1 explicitly permits this
		    variation); do not use it for this purpose.
		   
		    ʹ��SIG_DFL, SIG_IGNʱ, ��ͬLINUX���а汾�ĳ������ֲ. ���ڽ���һ����������ʱ��, 
			�ڲ�ͬ�汾��ͬ.


	5. sigaction����

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

		1) һ�㶼��ʹ�õ�һ������, �����������ÿ���.
		2) sigaction()����, �ڶ���������const, �Ǹ��������ε�. ����������û��const, �Ǻ�������ߴ��ε�.
		3) oldact, ��һ�����õ�ָ��.
		4) �ڶ�����������ΪNULLʱ, ���ڶ�ȡ������ָ��, ���������µĲ�����.
		   ��������������ΪNULLʱ, ��ʾ����ȡ�ϵĲ�����.
		
	6. sigaction����˵��:
	
		1) ��������API, ����sigaction��signal�����п���ֲ��.
		
		2) �÷��ؼ�������sigactionָ��

		3) sigaction��signal�õ�һ�㣺sigaction����һ�εõ������²������ͻ�ȡ�ɵĲ�����.
		   (��ʵ�����Ե��������µĲ�����ߵ���ֻ��ȡ�ɵĲ�����), ��signal�������ܵ�����ȡ�ɵĲ���
		   �����������������µĲ�������ͬʱ�Ż�ȡ�ɵĲ�����.
		   
		   ���������signal()������ȡ��ǰ�Ĳ�����, �����������µĲ�����. ��Ҫ: �ȵ��øú���, ����
		   һ���µĺ���; �ٰѻ�ȡ�ľɵĺ���ָ���ٴε����µĺ���ָ��, �ٴε���һ��signal()����.

		�ܽ�: 
				1) signal����Ҫ��֪���ɵĲ�����, ����������һ���µĲ�����.
				2) sigaction���������֪���ɵĲ�����, ��ѵڶ�����������ΪNULL����.

		(?????)������ʲô�������Ҫ����???

//=======================================================================================================
									3.5.4.alarm��pause����
//-------------------------------------------------------------------------------------------------------
	1. alarm����

		unsigned int alarm(unsigned int seconds);

		alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds 
		seconds.
		

		1) �ں���API��ʽ�ṩ������.
		
		2) ʱ�䵽���Ժ�, �ں˷���һ��SIGALRM������, ���̿��Բ�����ź�(��һ��������).
		
		3) ��һ�ε��ú����ķ���ֵ��0, ֮������Ƕ�ʱʣ�������.
		
		4) ϵͳΪÿһ������ֻ�ṩ��һ����ʱ����, ÿ�ε��ö���ˢ������ֵ.

	2. alarm�������ʵ��
	
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
			
			// ʹ��signal()����ʵ��
			//signal(SIGALRM, func);					// ע��һ���źŴ�����.
			
			// ʹ��sigaction()����ʵ��
			struct sigaction act = {0};
			act.sa_handler = func;
			sigaction(SIGALRM, &act, NULL);

			ret = alarm(5);
			printf("1st, ret = %d.\n", ret);
			
			while (1);									// �ȴ�SIGALRM
			return 0;
		}		
		
		���н��:
			1st, ret = 0.
			alarm happened.


	3. pause����

		#include <unistd.h>

		int pause(void);

		pause()  causes  the  calling  process  (or  thread) to sleep until a signal is delivered that either terminates the
		process or causes the invocation of a signal-catching function.

		pause() returns only when a signal was caught and the signal-catching  function  returned.   In  this  case  pause()
		returns -1, and errno is set to EINTR.

	
		1) �ں˹���
		
			a) pause���������þ����õ�ǰ������ͣ����, ����CPU����������ȥִ��. ����ǰ���̽���pause״̬
			   ��ǰ���̻����Ϊ����ס������ס��, Ҫ�˳�pause״̬��ǰ������Ҫ���źŻ���.
			
			b) ��while(1) ��ͬ, ��ռ��CPU��ʱ��.
			
	4. ʹ��alarm��pause��ģ��sleep

		void func(int sig)
		{												// �պ���

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

		���н��:
			before mysleep.
			after mysleep.

//=======================================================================================================





















