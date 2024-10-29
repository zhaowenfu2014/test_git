/*
//=======================================================================================================
										3.3.��ȡϵͳ��Ϣ
//=======================================================================================================
3.3.1.����ʱ��ĸ���
3.3.2.linuxϵͳ�е�ʱ��
3.3.3.ʱ�����APIʵս1
3.3.4.ʱ�����APIʵս2
3.3.5.linux��ʹ�������
3.3.6.proc�ļ�ϵͳ����
3.3.7.proc�ļ�ϵͳ��ʹ��
//=======================================================================================================
3.3.1.����ʱ��ĸ���
	���ڽ����й�ʱ���һЩ����, ����GMTʱ�䡢UTCʱ��ͼ��������ʱ���йصĲ���������ԭ��.
3.3.2.linuxϵͳ�е�ʱ��
	���ڽ���linuxϵͳ����μ�¼ʱ��, �Լ�linux API����ʱ������йصĲ���.
3.3.3.ʱ�����APIʵս1
	����ͨ��ʵ����д������Եķ�ʽ����һ����ʹ��linux��ʱ�����API����.
3.3.4.ʱ�����APIʵս2
	����ͨ��ʵ����д������Եķ�ʽ����һ����ʹ��linux��ʱ�����API����.
3.3.5.linux��ʹ�������
	���ڽ����������α������ĸ���, ���ҽ���linux�»�ȡ�������API��д����ʵ�ʲ���.
3.3.6.proc�ļ�ϵͳ����
	���ڽ���linux��/procĿ¼�����proc�����ļ�ϵͳ����ԭ�������, ��������proc�г����ļ����ļ�������.
3.3.7.proc�ļ�ϵͳ��ʹ��
	���ڽ���proc�ļ�ϵͳ��ʹ�÷�����д�������ʵ������.
//=======================================================================================================
									3.3.1.����ʱ��ĸ���
//-------------------------------------------------------------------------------------------------------
	1. GMTʱ��
	
		1) GMT�Ǹ�������ʱ��, Ҳ���Ǹ������ε����ĵ���֮��. ��ͨ�����Ĺ۲�ȷ����ʱ��.
		2) GMTʱ������壿�ø������εĵ���ʱ����Ϊȫ�����ʱ��, ��������ȫ���Ե��¼���ʱ��, ������
		   ����.
		3) һ��Ϊ�˷���, һ�����Ҷ�ͳһʹ��һ������ʱ��.

	2. UTCʱ��
	
		1) GMTʱ������ǰʹ�õ�, ��Щ����Խ��Խ���ʹ��UTCʱ��.
		2) ���ڱ���ʱ�䣬���Բο���http://www.cnblogs.com/qiuyi21/archive/2008/03/04/1089456.html

		�ܽ�:
				���������Ϊ��ʮ��ʱ��, ÿ��ʱ�������Լ��ı���ʱ��. �ڹ������ߵ�ͨ�ų���, Ϊ��ͳһ���,
				ʹ��һ��ͳһ��ʱ��, ��Ϊͨ��Э��ʱ(UTC, Universal Time Coordinated). 
				UTC���������ƽ��ʱ(GMT, Greenwich Mean Time)һ��, ����Ӣ���׶صı���ʱ��ͬ. 
				�ڱ�����, UTC��GMT������ȫ��ͬ.

				����ʱ���Ƕ�����, ����UTC�˸�Сʱ, �ڵ����ʼ���ͷ��Date���Ϊ+0800. ����ڵ����ʼ�����
				ͷ������ôһ�У�Date: Fri, 08 Nov 2002 09:42:22 +0800
				˵���ż��ķ��͵صĵط�ʱ���Ƕ�������ʮһ�°˺�, ������, ���Ͼŵ���ʮ����(��ʮ����), ��
				���ط��ı���ʱ����UTC�˸�Сʱ(+0800, ���Ƕ�����ʱ��).

	3. ���������ʱ���йصĲ���
	
		1) ��ʱ��Ͷ�ʱ��: ��ʱ�� = ��ʱ�� - ��ʱ��.
		
		2) ��ʱ����ʵʱʱ��. ��ʱ��(timer)����ʱ����Ƕ�ʱ��, ʵʱʱ��(RTC)���Ǻ͵�ʱ���йص�һ������.

//=======================================================================================================
									3.3.2.linuxϵͳ�е�ʱ��
//-------------------------------------------------------------------------------------------------------
	1. jiffies������
	
		1) jiffies��linux�ں��е�һ��ȫ�ֱ���, �������������¼���ں˵Ľ���ʱ��Ϊ��λʱ�䳤�ȵ�һ����ֵ.
		
		2) �ں����õ�ʱ������һ������ʱ��, ʵ����linux�ں˵ĵ���ϵͳ����ʱ�������������ʱ��Ϊʱ��
		   Ƭ��.
		   
		3) jiffies��������ʱ��һ����׼ֵ, Ȼ���ں�ÿ��һ������ʱ��jiffies�ͻ��1, Ȼ����ϵͳ������
		   һ��ʱ�����ǵ�ǰʱ��ͱ�jiffies�����������ע.

	2. linuxϵͳ��μ�¼ʱ��
	
		1) �ں��ڿ���������ʱ����ȡRTCӲ����ȡһ��ʱ����Ϊ��ʼ��׼ʱ��, �����׼ʱ���Ӧһ��jiffiesֵ
		   (�����׼ʱ�任���jiffiesֵ�ķ����ǣ������ʱ���ȥ1970-01-01 00:00:00 +0000(UTC), Ȼ�����
		   ��ʱ��λ����jiffies��ֵ), ���jiffiesֵ��Ϊ���ǿ���ʱ�Ļ�׼jiffiesֵ����. Ȼ��ϵͳ����ʱ
		   ÿ��ʱ�ӽ��ĵ�ĩβ�����jiffies���ȫ�ֱ�����1, ��˲���ϵͳ��ʹ��jiffies���ȫ�ֱ�����¼��
		   ������ǰ��ʱ��. ��������Ҫ��ǰʱ���ʱ, ����jiffies���ʱ���ȥ����(���㷽�������Ȱ����
		   jiffiesֵ��Ӧ��ʱ��������, Ȼ�����1970-01-01 00:00:00 +0000(UTC)���ɵõ����ʱ���).
		   
		2) ��ʵ����ϵͳֻ�ڿ���ʱ��һ��RTC, ����ϵͳ���й�����RTC�������õ�. RTC������������ʵ����OS��
		   2�ο���֮�����ʱ��ı���.
		   
		3) ���ʱһ��Ҫ��ʱ��Ͷ�ʱ�����������. jiffies���������¼����ʵ�Ƕ�ʱ��(��ʵ���ǵ�ǰʱ��
		   ��1970-01-01 00:00:00 +0000(UTC)���ʱ��Ĳ�ֵ).
		   
		4) һ��ʱ����ĵ�ʱ��ȡ���ڲ���ϵͳ������, �ִ�linuxϵͳһ����10ms����1ms. ���ʱ����ʵ���ǵ�
		   ��ʱ��, ���ں�����HZ����¼�ͱ�ʾ. ���HZ�����1000��ôʱ�ӽ��ľ���1/HZ, Ҳ����1ms. ��Щ��
		   ѧϰ����ʱ���õ�.

	3. linux��ʱ����ص�ϵͳ����
	
		1) ���õ�ʱ����ص�'API'��'C��'������9����time/ctime/localtime/gmtime/mktime/asctime/strftime/
		   gettimeofday/settimeofday.

		2) time()ϵͳ���÷��ص�ǰʱ������Ϊ��λ�ľ���1970-01-01 00:00:00 +0000(UTC)��ȥ������. ���
		   time�ڲ�������jiffies����õ�������. ����������������Χ����time��������.

			time_t time(time_t *t);				// man 2 time
			
			On success, the value of time in seconds since the Epoch is returned.  On
			error, ((time_t) -1) is returned, and errno is set appropriately.

		3) gmtime()��localtime()���time�õ����������һ��struct tm�ṹ���ʾ��ʱ��. ������gmtime()�õ�
		   ���ǹ���ʱ��, ��localtime�õ����Ǳ���(ָ����������localtime()�����ĳ������ڵļ���������õ�
		   ʱ����Ӧ�ı���ʱ��)ʱ��. mktime()��������෴�����ת��(struct tm��time_t).

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
		
		4) �����struct tm������õ��ַ�����ʽ��ʱ��, ������asctime()����strftime()������. (�����
		   time_t������õ��ַ�����ʽ��ʱ����ctime����).

		5) gettimeofday()���ص�ʱ������struct timeval��struct timezone�������ṹ������ͬ��ʾ��, ����
		   timeval��ʾʱ��, ��timezone��ʾʱ��. settimeofday()���������õ�ǰ��ʱ���ʱ����.

			   struct timeval {
				   time_t      tv_sec;     /* seconds */
				   suseconds_t tv_usec;    /* microseconds */
			   };

			   struct timezone {
				   int tz_minuteswest;     /* minutes west of Greenwich */
				   int tz_dsttime;         /* type of DST correction */
			   };						  /*

		6) �ܽ᣺�������ĸ�ϵͳ����, ���յõ���ʱ�䱾���϶���һ��ʱ��(���ʱ�����ն��Ǵ�kernel�м�¼��
		         jiffies�м��������), ֻ������ͬ�ĺ������ص�ʱ��ĸ�ʽ��ͬ, ���Ȳ�ͬ.

//=======================================================================================================
									3.3.3.ʱ�����APIʵս1
//-------------------------------------------------------------------------------------------------------
	1. time()
	
		1) time�ܵõ�һ����ǰʱ������׼���ʱ��1970-01-01 00:00:00 +0000(UTC)��ȥ�˶�����.
		
		2) man 2 time:
		
			time_t time(time_t *t);				// man 2 time
			
			On success, the value of time in seconds since the Epoch is returned.  On
			error, ((time_t) -1) is returned, and errno is set appropriately.
		
		3) ����:
		
			time_t tNow = -1;

			tNow = time(NULL);		// ����ֵ
			if (tNow < 0)
			{
				perror("time");
				return -1;
			}
			printf("time: %ld.\n", tNow);
				

	2. ctime()
	
		1) ctime()���Դ�time_t�����õ�һ�����׹۲���ַ�����ʽ�ĵ�ǰʱ��.

		2) man 3 ctime
		
			char *ctime(const time_t *timep);

		3) ctime�ô��Ǻܼ򵥺���, ����ֱ�ӵõ���ǰʱ����ַ�����ʽ, ֱ�Ӵ�ӡ����. ������ctime�Ĵ�ӡ
		   ʱ���ʽ�ǹ̶���, û���������ǵ��뷨ȥ��.
		   
		4) ����:
		
			time_t tNow = -1;
			
			// time
			time(&tNow);				// ָ��������Ͳ���
			if (tNow < 0)
			{
				perror("time");
				return -1;
			}
			printf("time: %ld.\n", tNow);
			
			// ctime
			printf("ctime: %s.\n", ctime(&tNow));
			
			���н��:
			time: 1689750605.
			ctime: Wed Jul 19 15:10:05 2023

			ʵ�������Կ���, ctime�����õ���ʱ���ǿ����˼�����еı���ʱ���(������е�ʱ������).
			
	3. gmtime()��localtime()
	
		1) gmtime()��ȡ��ʱ���У��������1970Ϊ��׼�Ĳ�ֵ, �·���0��ʾ1��, Сʱ������UTCʱ���0ʱ��Ϊ
		   ��׼��Сʱ��(�����Ƕ�8��, ��˱���ʱ������ʱ���8)

		2) �²�localtime()��gmtime()��Ψһ�������localtime�Ե�ǰ����������õ�ʱ��ΪСʱ��ʱ���׼,
		   ����һ��. ʵ��֤�����ǵĲ²�����ȷ��.
		
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
					 at  the time described.  The value is positive if daylight sav�\
					 ing time is in effect, zero if it is not, and negative  if  the
					 information is not available.
		   
		4) ����:

			time_t tNow = -1;
			struct tm tmNow;

			time(&tNow);				// ָ��������Ͳ���
			...
			memset(&tmNow, 0, sizeof(tmNow));
			gmtime_r(&tNow, &tmNow);					// ���ÿ�����汾�ĺ���(!!!!)
			printf("��%d��%d��%dʱ%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
			
			memset(&tmNow, 0, sizeof(tmNow));
			localtime_r(&tNow, &tmNow);
			printf("��%d��%d��%dʱ%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
			
			���н��: (��ʱʱ��Ϊ2023��7��19��15��)
				��123��6��19ʱ7.
				��123��6��19ʱ15.			
			
			(�õ����겢����ʵ�ʵ�2023��, ����2023-1900. ��Ϊ tm_year   The number of years since 1900)

//=======================================================================================================
									3.3.4.ʱ�����APIʵս2
//-------------------------------------------------------------------------------------------------------
	1. mktime()
	
		1) ��OS�ж�ȡʱ��ʱ�ò���mktime()��, ���mktime()�����������ϵͳ����ʱ��ʱ�õ�.
		
		2) man mktime
		
			time_t mktime(struct tm *tm);
			 
			��tm�ṹ�����, �õ�time_t. �õ�һ����ǰʱ������׼����ȥ�˶�����.
			
	2. asctime()
	
		1) asctime()�õ�һ���̶���ʽ���ַ�����ʽ�ĵ�ǰʱ��, Ч���Ϻ�ctimeһ����. ������ctime()��time_t
		   ����, ��asctime()��struct tm����.

	3. strftime()
	
		1) asctime()��ctime()�õ���ʱ���ַ������ǹ̶���ʽ��, û���û��Զ����ʽ.
		
		2) �����Ҫ�û��Զ���ʱ��ĸ�ʽ, ����Ҫ��strftime().
			
			size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);
			
				// ������tm������, ���Ϊ�ַ���char *s, ��ʽ����׼Ϊconst char *format, ����ַ�����
				// ��СΪmax.

			%Y     The year as a decimal number including the century.
		    %m     The month as a decimal number (range 01 to 12).
		    %d     The day of the month as a decimal number (range 01 to 31).
			%H     The hour as a decimal number using a 24-hour clock  (range  00  to
			%M     The minute as a decimal number (range 00 to 59).
			%S     The second as a decimal number (range 00 to 60).  (The range is up
				    to 60 to allow for occasional leap seconds.)
			...		

		3) ����:
			
			time_t tNow = -1;
			struct tm tmNow;
			char buf[100];
					
			memset(buf, 0, sizeof(buf));
			strftime(buf, sizeof(buf), "%Y * %m * %d, %H-%M-%S.", &tmNow);
			printf("ʱ��Ϊ��[%s].\n", buf);

			���н��: ʱ��Ϊ��[2023 * 07 * 19, 15-46-06.].

	4. gettimeofday()��settimeofday()
	
		1) ǰ�潲���Ļ���time()�������Ǹ�ϵ�ж�������Ϊ��λ����ȡʱ���, û�б������ȷ��ʱ��.
		
		2) ��ʱ�����ǳ���ϣ���õ��ǳ���ȷ��ʱ��(Ʃ����usΪ��λ), ��ʱ���ֻ��ͨ��gettimeofday()��ʵ����.
		   gettimeofday()���ص�ʱ������struct timeval��struct timezone�������ṹ������ͬ��ʾ��, ����
		   timeval��ʾʱ��, ��timezone��ʾʱ��. settimeofday()���������õ�ǰ��ʱ���ʱ����.
		3) man 2 gettimeofday
		
			int gettimeofday(struct timeval *tv, struct timezone *tz);
			int settimeofday(const struct timeval *tv, const struct timezone *tz);

			gettimeofday() and settimeofday() return 0 for success, or -1 for failure
			(in which case errno is set appropriately).

			   struct timeval {
				   time_t      tv_sec;     /* seconds */					(!!!!) ��
				   suseconds_t tv_usec;    /* microseconds */				(!!!!) ΢��
			   };

			   struct timezone {
				   int tz_minuteswest;     /* minutes west of Greenwich */	(???) �����������ε�ʱ��
				   int tz_dsttime;         /* type of DST correction */
			   };						  /*	


		4) ���ԣ�

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

			���н��:
				seconde: 1689752766.				// ����1970�������.
				timezone:-480.						// 480����, 8Сʱ. ��8��

//=======================================================================================================
									3.3.5.linux��ʹ�������
//-------------------------------------------------------------------------------------------------------
	1. �������α�����
	
		1) ��������������, û���κι��ɵ�һ������.
		2) ��������ȫ����������ǲ����ڵ�, ֻ��һ���������. ����ƽʱҪ�õ������ʱһ��ֻ��ͨ��һЩ�㷨
		   �õ�һ��α���������.
		3) ����ƽʱ˵�������, ������ָ����α�����.

	2. linux����������API
	
		1) ������ε���rand()�������Է���һ��α���������.
		2) srand()������������rand()��ȡ��α������е�����.
		3) rand��һ���⺯��, û��API. ���� man 2 rand �����Բ鿴�÷�.
		
		int rand(void);
		int rand_r(unsigned int *seedp);
		void srand(unsigned int seed);		

		The  rand()  function  returns  a pseudo-random integer in the range 0 to
		RAND_MAX inclusive (i.e., the mathematical range [0, RAND_MAX]). 
		
		RAND_MAX = 2147483647.

	3. ʵս��ʾ
	
		1) ����ʹ��rand�ظ�����n��, �ͻ�õ�һ��0-RAND_MAX֮���α�����, �����Ҫ������Χ, ���Եõ�
		   ��������к��ٽ��м���(���%N, N������Ҫ����������).
		   
		2) ����ʹ��rand���õ�α�����������ȱ��, ÿ��ִ�г���õ���α���������ͬһ������, û���õ���
		   ������.
		   
		3) ԭ������Ϊrand�ڲ����㷨��ʵ��ͨ��һ������(seed, ��ʵ����һ��ԭʼ����, int����), rand()��
		   ��Ĭ����ʹ��1��Ϊseed��, ����һ�����㷨Ҳ��һ����, ��ôÿ�εõ���α������п϶���ͬһ��.
		   
		4) ����Ҫ��ÿ��ִ����������ȡ��α������в�ͬ, ��ÿ�ζ�Ҫ����ͬ������. ��srand()����������
		   ����.

			srand(time(NULL));					// srand()��ȡһ������.
			
			for (i=0; i<6; i++)					//
			{
				val = rand();					// ����һ�������.
				printf("%d ", (val % 6));		// �����������0-5.
			}

	4. �ܽ��˵��
	
		1) ��ÿ��ִ�г���ʱ, ����srand()����һ����ͬ������, Ȼ���ٶ�ε���rand()��ȡһ��α�������,
		   �����Ϳ���ÿ�ζ��õ�һ����ͬ��α�������.
		2) һ�㳣����������time()�����ķ���ֵ����srand�Ĳ���.

	5. ��linuxϵͳ�л�ȡ�����������
	
		1) linuxϵͳ�ռ�ϵͳ�е�һЩ����������¼���ʱ��(Ʃ�����˶����, Ʃ�紥�����Ĳ����������)��
		   Ϊ�������ȥ�������������.

//=======================================================================================================
									3.3.6.proc�ļ�ϵͳ����
//-------------------------------------------------------------------------------------------------------
	1. ����ϵͳ����ĵ���
	
		1) �򵥳��򵥲�����.
			���������кܶ�����: ��Ҫ��һ���Ļ���֧�ֵ�������; ���̵߳ĳ���,Ҳ���ʺϵ�������.
		2) ���ӳ���printf��ӡ��Ϣ����.
		3) �����ϵ��־��¼��Ϣ����.
			�ʺϳ�ʱ����, ��һЩ��Ϣ�������־�ļ���.
		4) �ں˵��Ե�����
			�������еķ���, �����ں˳����ṩ�ķ���. �ں˳���������ʱ, ���ϵ����ֶο��ܶ�������.
		
	2. proc�����ļ�ϵͳ�Ĺ���ԭ��
	
		1) linux�ں���һ���ǳ��Ӵ󡢷ǳ����ӵ�һ�������ĳ���, ����������һ��������˵�����Ƿǳ����ӵ�.
		2) ��kernel�����Ӵ����Ŀ, ���������/����һ�������Ƿǳ��鷳��, ��Ϊ������ӵ�һ�����ܿ��ܻ�
		   Ӱ�������Ѿ��е�.
		3) �����ں˰汾�о��ܵ��Ժ��鷳, ���Ǹ����ǻ�����ƾ����˳������׵�����ȥ��Ԧ. ���ǵ���2.4����
		   �İ汾��ʱ��, ����Ѷ��Ѿ��ǳ�����.
		4) Ϊ�˽����ں˵��Ժ�ѧϰ���Ѷ�, �ں˿����������ں��������һЩ'����'ר�����ڵ����ں�, proc�ļ�
		   ϵͳ����һ������.
		5) proc�ļ�ϵͳ��˼·�ǣ����ں��й���һ�������ļ�ϵͳ/proc, �ں�����ʱ���ں���һЩ�ؼ�������
		   �ṹ���ļ��ķ�ʽ������/procĿ¼�е�һЩ�ض��ļ���, �����൱�ڽ����ɼ����ں��е����ݽṹ��
		   ���ӻ��ķ�ʽ���ָ��ں˵Ŀ�����.
		   
		   ����: һ�����̰������̽ṹPCB, ������һ���ļ���, ������ǰ���̴�˵�����е��ļ���Ϣ. �����
		         �ں˵�һ�����ݽṹ. ���ں�����ͨ��������ʽ���ڵ�, �����ǿ�������.  �����ں���һ������:
				 ����ʵʱ�İ���Щ���ݰ����ļ�����ʽд��/procĿ¼, ���ǾͿ���ͨ�����Ŀ¼�µ��ض����ļ�,
				 ʵʱ�Ŀ����ں��е����ݽṹ��ֵ. ���൱�ڿ����߿��Կ����ں˵ı�����.
		   
		6) proc�ļ�ϵͳ���˿�����һ�ֵ����ں˵ķ���������ͨ��ʵʱ�Ĺ۲�/proc/xxx�ļ�, ���ۿ��ں����ض�
		   ���ݽṹ��ֵ. ���������һ���¹��ܵ�ǰ�����Ա�, �Ϳ���֪������¹��ܲ�����Ӱ��Ի��ǲ���.
		   
		7) procĿ¼�µ��ļ���С����0, ��Ϊ��Щ�ļ�������������Ӳ����, ��Ҳ����һ����ʵ�ļ�, ��ֻ��
		   һ���ӿ�, ������ȥ��ȡ����ļ�ʱ, ��ʵ�ں˲�����ȥӲ����������ļ�, ����ӳ��Ϊ�ں��ڲ�һ��
		   '���ݽṹ'����ȡ����'��ʽ�����ַ���'���ظ�����. ���Ծ������ǿ����Ļ���һ���ļ������ַ���,
		   ����ͨ�ļ�һ����; ����ʵ��������֪�����������ʵʱ�Ĵ��ں������ݽṹ����, ������Ӳ��������.
		   
		8) (!!!!!) ��Щ�ļ�����ֻ�ܿ�, �����޸�.

	3. ����proc�е��ļ�����
	
		1) /proc/cmdline
		
			a) ����ļ�������ں˱�ʵʱ����, �������������в���. ubuntu�в鿴: cat /proc/cmdline
			
			   BOOT_IMAGE=/boot/vmlinuz-3.13.0-32-generic root=UUID=e46e78eb-87b1-4f25-b758-19649125d60a 
			           ro find_preseed=/preseed.cfg auto noprompt priority=critical locale=en_US quiet
			b) vi /proc/cmdline Ҳ���Կ�������.
			c) ls -l /proc/cmdline 
				-r--r--r-- 1 root root 0 Jul 19 17:25 cmdline		// ��С��0, ����ͨ�ļ���ͬ.

		2) /proc/cpuinfo
		
			�鿴CPU��������Ϣ. �����ں������һЩ�ṹ�����������, ͨ����ʽ���������.	
		
		3) /proc/devices
		
			�鿴�ں��а�װ�����е�����.
		
		4) /proc/interrupts

//=======================================================================================================
									3.3.7.proc�ļ�ϵͳ��ʹ��
//-------------------------------------------------------------------------------------------------------
	1. proc�ļ�ϵͳ��ʹ��
	
		1) cat���ֹ��鿴.
		
		2) �����п����ļ�IO����.
		
			open()���ļ�, read()��ȡ�ļ�����.
		
		3) ��shell��������cat������������ʽ����ȡ�������ں���Ϣ.
		
	2. �����ж�ȡ/proc�����ļ�����

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
				printf("����ǣ�%s.\n", buf);
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
				printf("����ǣ�%s.\n", buf);
			}
			return 0;
		}

	2. ��չ��sys�ļ�ϵͳ
	
		1) sys�ļ�ϵͳ�����Ϻ�proc�ļ�ϵͳ��һ����, ���������ļ�ϵͳ, ���ڸ�Ŀ¼���и�Ŀ¼(һ����/proc
		   Ŀ¼, ��һ����/sysĿ¼), ��˶�����Ӳ���е��ļ�, �����ں��е����ݽṹ�Ŀ��ӻ��ӿ�.
		   
		2) ��ͬ����/proc�е��ļ�ֻ�ܶ�, ����/sys�е��ļ����Զ�д. 
		
		3) ��/sys�е��ļ����ǻ�ȡ�ں������ݽṹ��ֵ, ��д��/sys�е��ļ����������ں��е����ݽṹ��Ԫ��
		   ��ֵ.
		   
		4) ��ʷ�ϸտ�ʼ����/proc�ļ�ϵͳ, ����ϣ��ͨ�����ּ����������ں�. ʵ����������ȷʵ������, ����
		   �ܶ��ں˿����߶�ȥ�ں˵��۴�����/procĿ¼��д�ļ�, ���Ҹտ�ʼ��ʱ���ں˹����߶�procĿ¼��
		   ʹ��Ҳû��ʲô����Ҳûʲôͳһ�滮, �����Ľ������proc����Ķ����ֶ�������.
		   
		5) ��������proc�е�����̫��̫��ȱ��ͳһ�滮, ���Ǻ��������sysĿ¼. sys�ļ�ϵͳһ��ʼ�����˺�
		   �õĹ滮��Լ��, ���Ժ���ʹ��sysĿ¼ʱ���˹��.

		�ܽ�: /sys Ŀ¼���ļ�Ҳ�������ļ�, �����ں������ݽṹ�Ŀ��ӻ��ӿ�. ���ǿ��Զ�, д. 
		
			(?????) �γ���˵/proc Ŀ¼���ļ�������д, �ǲ�������????

//=======================================================================================================








