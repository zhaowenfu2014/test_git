/*
//=======================================================================================================
								4.5.数组&字符串&结构体&共用体&枚举
//=======================================================================================================
4.5.1.程序中内存从哪里来1
4.5.2.程序中内存从哪里来2
4.5.3.程序中内存从哪里来2
4.5.4.程序中内存从哪里来4
4.5.5.C语言的字符串类型
4.5.6.字符串和字符数组的细节
4.5.7.C语言之结构体概述
4.5.8.结构体的对齐访问1
4.5.9.结构体的对齐访问2
4.5.10.结构体的对齐访问3
4.5.11.offsetof宏与container_of宏
4.5.12.共用体union
4.5.13.大小端模式1
4.5.14.大小端模式2
4.5.15.枚举
//=======================================================================================================
									4.5.1.程序中内存从哪里来1
//-------------------------------------------------------------------------------------------------------
	1. 程序执行需要内存支持
		对程序来说, 内存就是程序的立足之地(程序是被放在内存中运行的); 程序运行时需要内存来存储一些
		临时变量.
		
	2. 内存管理最终是由操作系统完成的
		1) 内存本身在物理上是一个硬件器件, 由硬件系统提供.
		2) 内存是由操作系统统一管理. 为了内存管理方便又合理. 操作系统提供了多种机制来让我们应用程序
		   使用内存. 这些机制彼此不同, 各自有各自的特点, 我们程序根据自己的实际情况来选择某种方式获
		   取内存(在操作系统处登记这块内存的临时使用权限)、使用内存、释放内存(向操作系统归还这块内存
		   的使用权限).
		   
	3. 三种内存来源：栈(stack)、堆(heap)、数据区(.data)
	
		在一个C语言程序中, 能够获取的内存就是三种情况：栈(stack)、堆(heap)、数据区(.data)
		
		1) 栈, 操作系统为每一个进程分配一个栈空间.
		2) 堆, 所有的进程公用一个堆空间.
		
	4. 栈的详解
	
		1) 运行时自动分配&自动回收：栈是自动管理的, 程序员不需要手工干预. 方便简单.
		2) 反复使用：栈内存在程序中其实就是那一块空间, 程序反复使用这一块空间.
		3) 脏内存：栈内存由于反复使用, 每次使用后程序不会去清理, 因此分配到时保留原来的值.
		4) 临时性：(函数不能返回栈变量的指针, 因为这个空间是临时的).
		5) 栈会溢出：因为操作系统事先给定了栈的大小, 如果在函数中无穷尽的分配栈内存总能用完.
	
	5. 测试
		
		1) 函数不能返回栈变量的指针, 因为这个空间是临时的.  这个函数中的临时变量a, 与这个地址绑定. 
		   另一个函数中, 就会放了刚才变量a的地址. 而返回的函数,是不能使用的, 当使用的时候,可能其他
		   的地方又使用了这个栈地址, 使用已经没有任何意义.

			// 函数不能返回函数内部局部变量的地址, 因为这个函数执行完返回后这个局部变量已经不在了
			// 这个局部变量是分配在栈上的, 虽然不在了但是栈内存还在还可以访问，但是访问时实际上这个
			// 内存地址已经和当时那个变量无关了.
			int *func(void)
			{
				int a = 4;			// a是局部变量，分配在栈上又叫栈变量，又叫临时变量
				printf("&a = %p\n", &a);
				return &a;
			}
				int *p = NULL;
				p = func();
				func2();
				func2();
				printf("p = %p\n", p);
				
				
				报警告: warning: function returns address of local variable [-Wreturn-local-addr]

		2) 栈空间溢出
		
			void stack_overflow2(void)
			{
				int a = 2;
				stack_overflow2();
			}

	        (!!!!!!!)运行a.out, 堆栈溢出.Segmentation fault (core dumped). 编译时不会报错.

//=======================================================================================================
									4.5.2-3.程序中内存从哪里来2-3
//-------------------------------------------------------------------------------------------------------
	1. 堆内存详解
	
		操作系统堆管理器管理：堆管理器是操作系统的一个模块, 堆管理内存分配灵活, 按需分配.
	
		1) 大块内存：堆内存管理者总量很大的操作系统内存块, 各进程可以按需申请使用, 使用完释放.
		2) 程序手动申请&释放：手工意思是需要写代码去申请malloc和释放free.
		3) 脏内存：堆内存也是反复使用的, 而且使用者用完释放前不会清除, 因此也是脏的.
		4) 临时性：堆内存只在malloc和free之间属于我这个进程, 而可以访问. 在malloc之前和free之后
		   都不能再访问, 否则会有不可预料的后果.
		
		总结: 1) 栈是每个进程都分配一个. 堆是所有进程公用的.
			  2) 栈空间比较小, 堆空间比较大.
			  3) 进程中如果需要大的内存, 则需要在堆中手动申请. 注意不能使用栈太多空间(临时变量大小
			     需要控制)
	2. 实验
		
		1) 查看malloc()函数原型,包含的文件
		
			输入 man malloc (man 3 malloc)查看:
			
				#include <stdlib.h>

				void *malloc(size_t size);					// 单位 字节.
				void *calloc(size_t nmemb, size_t size);	// nmemb个单元，每个单元size字节
				void *realloc(void *ptr, size_t size);		// 改变原来申请的空间的大小的
		
		2) 申请, 绑定
			void *malloc(size_t size) 函数返回值是一个void * 类型.
			用户可以强制转化为任何想用的类型.

				int *p = (int *)malloc(20);
		
		3) 检验申请是否成功.
			(需要检查是否申请失败, 如果太大分配不了返回NULL)
				if (NULL == p)
				{
					printf("malloc error.\n");
					return -1;
				}
		
		4) 释放
				
			free(p);
			p = NULL;
			
	3. malloc函数说明
	
		1) void *是个指针类型, malloc返回的是一个void *类型的指针. 实质上malloc返回的是堆管理器分配
		   给本次申请的那段内存空间的首地址(malloc返回的值其实是一个数字, 这个数字表示一个内存地址).
		   为什么要使用void *作为类型? 主要原因是malloc帮我们分配内存时只是分配了内存空间, 至于这段
		   空间将来用来存储什么类型的元素malloc是不关心的, 由我们程序自己来决定.
		   
		2) 什么是void类型. 早期被翻译成空型, 这个翻译非常不好, 会误导人. void类型不表示没有类型, 而
		   表示万能类型. void的意思就是说这个数据的类型当前是不确定的, 在需要的时候可以再去指定它的
		   具体类型. void *类型是一个指针类型, 这个指针本身占4个字节, 但是指针指向的类型是不确定的,
		   换句话说这个指针在需要的时候可以被强制转化成其他任何一种确定类型的指针, 也就是说这个指针
		   可以指向任何类型的元素.
		   
		3) malloc的返回值：成功申请空间后返回这个内存空间的指针, 申请失败时返回NULL. 所以malloc获取
		   的内存指针使用前一定要先检验是否为NULL.
		   
		4) malloc申请的内存时用完后要free释放. free(p) 会告诉堆管理器这段内存我用完了你可以回收了.
		   堆管理器回收了这段内存后这段内存当前进程就不应该再使用了. 因为释放后堆管理器就可能把这段
		   内存再次分配给别的进程.
		   
		5) 再调用free归还这段内存之前, 指向这段内存的指针p一定不能丢(也就是不能给p另外赋值). 因为p
		   一旦丢失这段malloc来的内存就永远的丢失了(内存泄漏, 堆管理器中这段内存是被进程一直占用着),
		   直到当前程序结束时操作系统才会回收这段内存.

	4. malloc的一些细节表现
	
		1) malloc(0)
		
			malloc申请0字节内存本身就是一件无厘头事情, 一般不会碰到这个需要.
			如果真的malloc(0)返回的是NULL还是一个有效指针? 答案是：实际分配了16Byte的一段内存并且返
			回了这段内存的地址. 这个答案不是确定的, 因为C语言并没有明确规定malloc(0)时的表现, 由各
			malloc函数库的实现者来定义.

				int *p1 = (int *)malloc(0);		
				int *p2 = (int *)malloc(0);

				printf("p1 = %p.\n", p1);		
				printf("p2 = %p.\n", p2);	// 结果: p2-p1 = 0x10 = 16Byte

		2) malloc(4)
		
			gcc中的malloc默认最小是以16B为分配单位的, 如果malloc小于16B的大小时都会返回一个16字节的
			大小的内存. malloc实现时没有实现任意自己的分配而是允许一些大小的块内存的分配.

				int *p1 = (int *)malloc(4);		
				int *p2 = (int *)malloc(4);

				printf("p1 = %p.\n", p1);		
				printf("p2 = %p.\n", p2);	// 结果: p2-p1 = 0x10 = 16Byte
	
		3) malloc(20)去访问第25、第250、第2500····会怎么样
		
			实战中：120字节处正确，1200字节处正确····终于继续往后访问总有一个数字处开始段错误了.

//=======================================================================================================
									4.5.4.程序中内存从哪里来4
//-------------------------------------------------------------------------------------------------------
	1. 代码段、数据段、bss段
	
		1) 编译器在编译程序的时候, 将程序中的所有的元素分成了一些组成部分, 各部分构成一个段, 所以说段
		   是可执行程序的组成部分. 
		2) 代码段: 代码段就是程序中的可执行部分, 直观理解代码段就是函数堆叠组成的.
		3) 数据段(也被称为数据区、静态数据区、静态区）：数据段就是程序中的数据, 直观理解就是C语言程序
		   中的全局变量. (注意：全局变量才算是程序的数据, 局部变量不算程序的数据, 只能算是函数的数据).
		4) bss段(又叫ZI(zero initial)段): bss段的特点就是被初始化为0, bss段本质上也是属于数据段, bss段
		   就是被初始化为0的数据段.

		注意区分：数据段(.data)和bss段的区别和联系：二者本来没有本质区别, 都是用来存放C程序中的全局变
		          量的. 区别在于把显示初始化为非零的全局变量存在.data段中, 而把显式初始化为0或者并未
				  显式初始化(C语言规定未显式初始化的全局变量值默认为0)的全局变量存在bss段.
				  
		总结: 1) 没有显示初始化的全局变量, 放在BSS段, 就默认是0.
			  2) BSS段本质上属于数据段.

	2. 有些特殊数据会被放到代码段
	
		1) C语言中使用char *p = "linux";定义字符串时, 字符串"linux"实际被分配在代码段, 也就是说这个
		   "linux"字符串实际上是一个常量字符串而不是变量字符串.
		   
		2) const型常量：C语言中const关键字用来定义常量, 常量就是不能被改变的量. 
		   const的实现方法至少有2种：
		   
		   a) 第一种就是编译将const修饰的变量放在代码段去以实现不能修改(普遍见于各种单片机的编译器); 
		   b) 第二种就是由编译器来检查以确保const型的常量不会被修改, 实际上const型的常量还是和普通变
		      量一样放在数据段的(gcc中就是这样实现的).

	3. 显式初始化为非零的全局变量和静态局部变量放在数据段

		放在.data段的变量有2种：
			
			第一种是显式初始化为非零的全局变量.
			第二种是静态局部变量, 也就是static修饰的局部变量.
			
			(普通局部变量分配在栈上, 静态局部变量分配在.data段)

	4. 未初始化或显式初始化为0的全局变量放在bss段

		bss段和.data段并没有本质区别, 几乎可以不用明确去区分这两种.


	5. C语言中所有变量和常量所使用的内存无非以上三种情况.

		1) 相同点：三种获取内存的方法, 都可以给程序提供可用内存, 都可以用来定义变量给程序用.
		2) 不同点：
				a) 栈内存对应C中的普通局部变量(别的变量还用不了栈, 而且栈是自动的, 由编译器和运行时
		           环境共同来提供服务的, 程序员无法手工控制); 
				b) 堆内存完全是独立于我们的程序存在和管理的, 程序需要内存时可以去手工申请malloc, 使
				   用完成后必须尽快free释放. 
				c) 数据段对于程序来说对应C程序中的全局变量和静态局部变量.
				
	6. 如果我需要一段内存来存储数据, 究竟应该把这个数据存储在哪里? (或者说要定义一个变量, 我究竟应该
	   定义为局部变量,还是全局变量,还是用malloc来实现). 不同的存储方式有不同的特点, 简单总结如下：
	   
		1) 函数内部临时使用, 出了函数不会用到, 就定义局部变量. 使用栈. 
		2) 堆内存和数据段几乎拥有完全相同的属性, 大部分时候是可以完全替换的. 但是生命周期不同:
			堆内存的生命周期是从malloc开始到free结束.
			而全局变量是从整个程序一开始执行就开始, 直到整个程序结束才会消灭, 伴随程序运行的一生.
			
		因此：如果你这个变量只是在程序的一个阶段有用, 用完就不用了, 就适合用堆内存.
		      如果这个变量本身和程序是一生相伴的, 那就适合用全局变量.

			char str[] = "linux";		// 第二种方法：定义成全局变量，放在数据段

			int main(void)
			{
				char a[] = "linux";		// 第一种方法：定义成局部变量，放在栈上
				char *p = (char *)malloc(10);	

				if (NULL == p)
				{
					printf("malloc error.\n");
					return -1;
				}
				memset(p, 0, 10);		// 第三种方法： 放在malloc申请的堆内存中
				strcpy(p, "linux");

				return 0;
			}

//=======================================================================================================
									4.5.5.C语言的字符串类型
//-------------------------------------------------------------------------------------------------------
	1. C语言没有原生字符串类型
		1) 很多高级语言像java、C#等就有字符串类型, 有个String来表示字符串, 用法和int这些很像,可以
		   String s1 = "linux"; 来定义字符串类型的变量.
		2) C语言没有String类型, C语言中的字符串是通过字符指针来间接实现的.

	2. C语言使用指针来管理字符串
		1) C语言中定义字符串方法：char *p = "linux"; 
		2) 此时p就叫做字符串, 但是实际上p只是一个字符指针(本质上就是一个指针变量, 只是p指向了一个
		   字符串的起始地址而已).

	3. C语言中字符串的本质：指针指向头、固定尾部的地址相连的一段内存

		1) 字符串就是一串字符. 字符反映在现实中就是文字、符号、数字等人用来表达的字符, 反映在编程
		   中字符就是字符类型的变量. C语言中使用ASCII编码对字符进行编程, 编码后可以用char型变量来
		   表示一个字符. 字符串就是多个字符打包在一起共同组成的.
		2) 字符串在内存中其实就是多个字节连续分布构成的(类似于数组, 字符串和字符数组非常像).
		3) C语言中字符串有3个核心要点：第一是用一个指针指向字符串头; 第二是固定尾部(字符串总是以
		   '\0'来结尾); 第三是组成字符串的各字符彼此地址相连.
		4) '\0'是一个ASCII字符, 其实就是编码为0的那个字符(真正的0, 和数字0是不同的, 数字0有它自己
		   的ASCII编码). 要注意区分'\0'和'0'和0. (0等于'\0', '0'等于48)
		5) '\0'作为一个特殊的数字被字符串定义为(幸运的选为)结尾标志. 产生的副作用就是: 字符串中无
		   法包含'\0'这个字符. (C语言中不可能存在一个包含'\0'字符的字符串), 这种思路就叫“魔数”(魔
		   数就是选出来的一个特殊的数字, 这个数字表示一个特殊的含义, 你的正式内容中不能包含这个魔
		   数作为内容).

	4. 注意：指向字符串的指针和字符串本身是分开的两个东西
	
		char *p = "linux";
		
		1) 在这段代码中, p本质上是一个字符指针, 占4字节; 
		2) "linux"分配在代码段, 占6个字节; 
		3) 实际上总共耗费了10个字节, 这10个字节中：4字节的指针p叫做字符串指针(用来指向字符串的, 理解
		   为字符串的引子, 但是它本身不是字符串), 5字节的用来存linux这5个字符的内存才是真正的字符串,
		   最后一个用来存'\0'的内存是字符串结尾标志(本质上也不属于字符串).

	5. 存储多个字符的2种方式：字符串和字符数组

		我们有多个连续字符(典型就是linux这个字符串)需要存储, 实际上有两种方式：
		第一种就是字符串.
		第二种是字符数组.
		
		(!!!!!)两者区别,见下节3.
		
		测试:
			char *p = "linux";			// 字符串
			char a[] = "linux";			// 字符数组
			
			printf("p = %s.\n", p);
			printf("a = %s.\n", a);
			
		运行结果都是: linux

//=======================================================================================================
									4.5.6.字符串和字符数组的细节
//-------------------------------------------------------------------------------------------------------
	1. 字符数组初始化与sizeof、strlen
	
		1) sizeof是C语言的一个关键字, 也是C语言的一个运算符(sizeof使用时是sizeof(类型或变量名),
		   所以很多人误以为sizeof是函数, 其实不是), sizeof运算符用来返回一个类型或者是变量所占用
		   的内存字节数. 为什么需要sizeof？主要原因一是int、double等原生类型占几个字节和平台有关;
		   二是C语言中除了ADT之外还有UDT, 这些用户自定义类型占几个字节无法一眼看出, 所以用sizeof
		   运算符来让编译器帮忙计算.
		   
		2) strlen是一个C语言库函数, 这个库函数的原型是：size_t strlen(const char *s);
		   这个函数接收一个字符串的指针, 返回这个字符串的长度(以字节为单位). 注意一点是：strlen
		   返回的字符串长度是不包含字符串结尾的'\0'的. 
		   为什么需要strlen库函数? 因为从字符串的定义(指针指向头、固定结尾、中间依次相连)无法直
		   接得到字符串的长度, 需要用strlen函数来计算得到字符串的长度.
		   
		3) sizeof(数组名)得到的永远是数组的元素个数(也就是数组的大小), 和数组中有无初始化, 初始
		   化多、少等是没有关系的; strlen是用来计算字符串的长度的, 只能传递合法的字符串进去才有
		   意义, 如果随便传递一个字符指针, 但是这个字符指针并不是字符串是没有意义的.
		   
		4) 当我们定义数组时如果没有明确给出数组大小, 则必须同时给出初始化式, 编译器会根据初始化
		   式去自动计算数组的大小(数组定义时必须给出大小, 要么直接给, 要么给初始化式).

		总结: 
			1) sizeof(数据类型), sizeof(变量名). 是编译器来提供的.
			2) 
			
	2. 字符串初始化与sizeof、strlen
	
		1) char *p = "linux"; sizeof(p)得到的永远是4, 因为这时候sizeof测的是字符指针p本身的长度,
		   和字符串的长度是无关的.
		   
		2) strlen刚好用来计算字符串的长度.

		char *p = "linuxddd";
		printf("sizeof(p) = %d.\n", sizeof(p));		// 4
		printf("strlen(p) = %d.\n", strlen(p));		// 8

	3. 字符数组与字符串的本质差异(内存分配角度)
	
		1) 字符数组char a[] = "linux"; 来说, 定义了一个数组a, 数组a占6字节, 右值"linux"本身只存
		   在于编译器中, 编译器将它用来初始化字符数组a后丢弃掉(也就是说内存中是没有"linux"这个
		   字符串的); 这句就相当于是：char a[] = {'l', 'i', 'n', 'u', 'x', '\0'};
		   
		   (????) 这里保留疑问, "linux"是否存在于code区? 或者 直接存在了数组存放的数据区??? 
		   
		2) 字符串char *p = "linux"; 定义了一个字符指针p, p占4字节, 分配在栈上; 同时还定义了一个
		   字符串"linux", 分配在代码段; 然后把代码段中的字符串(一共占6字节)的首地址(也就是'l'的
		   地址)赋值给p.
		   
		对比：字符数组和字符串有本质差别. 字符数组本身是数组, 数组自身自带内存空间, 可以用来存东
	          西(所以数组类似于容器); 而字符串本身是指针, 本身永远只占4字节, 而且这4个字节还不能
			  用来存有效数据, 所以只能把有效数据存到别的地方, 然后把地址存在p中.
			  
			  也就是说字符数组自己存那些字符; 字符串一定需要额外的内存来存那些字符, 字符串本身只
			  存真正的那些字符所在的内存空间的首地址.

		char b[5];

		int main(void)
		{
			// 字符串存在栈上
			char a[7];	
			char *p = a;
			
			// 字符串存在数据段
			char *p = b;
			
			// 字符串存在堆空间
			char *p = (char *)malloc(5);
		}

//=======================================================================================================
									4.5.7.C语言之结构体概述
//-------------------------------------------------------------------------------------------------------
	1. 结构体类型是一种自定义类型
	
		C语言中的2种类型：原生类型和自定义类型.
		自定义类型: 数组, 结构体, 共同体, 枚举, typedef的类型, 函数指针等.
		
	2. 结构体使用时先定义结构体类型再用类型定义变量
	
		1) 结构体定义时需要先定义结构体类型, 然后再用类型来定义变量.
			// 定义类型
			struct people
			{
				char name[20];
				int age;
			};
		
			struct people p1;		// 使用结构体类型定义变量
			s1.age = 23;

		2) 也可以在定义结构体类型的同时定义结构体变量.
			// 定义类型的同时定义变量。
			struct student
			{
				char name[20];
				int age;
			}s1;					// s1是变量名.

		3) 定义结构体时, 用typedef 重命名类型.
		
			// 将类型struct student重命名为s1, s1是一个类型名, 不是变量.
			typedef struct student
			{
				char name[20];
				int age;
			}s1;					// s1是typedef后的类型名, 不是变量
			
		注意: 2)和3) 的s1不同: 一个是结构体变量, 一个是数据类型(一个结构体).

	3. 从数组到结构体的进步之处
		
		1) 结构体可以认为是从数组发展而来的. 其实数组和结构体都算是数据结构的范畴了, 数组就是最简单
		   的数据结构、结构体比数组更复杂一些, 链表、哈希表之类的比结构体又复杂一些; 二叉树、图等又
		   更复杂一些. 栈, 链表也是数据结构的一种.
		2) 数组有2个明显的缺陷：第一个是定义时必须明确给出大小, 且这个大小在以后不能再更改;第二个是
		   数组要求所有的元素的类型必须一致. 更复杂的数据结构中就致力于解决数组的这两个缺陷.
		3) 结构体是用来解决数组的第二个缺陷的, 可以将结构体理解为一个其中元素类型可以不相同的数组.
		   结构体完全可以取代数组, 只是在数组可用的范围内数组比结构体更简单.
		   
		总结: 1) 数组的缺陷: 大小固定, 数据类型必须相同. 
		      2) 其他的一些更复杂的数据结构, 都解决了数组的这两个缺点.

	4. 结构体变量中的元素如何访问?
	
		1) 数组中元素的访问方式：表面上有2种方式(数组下标方式和指针方式); 实质上都是指针方式访问.
		2) 结构体变量中的元素访问方式：只有一种, 用.或者->的方式来访问. (.和->访问结构体元素其实质
		   是一样的, 只是C语言规定用结构体变量来访问元素用. , 用结构体变量的指针来访问元素用-> , 
		   实际上在高级语言中已经不区分了, 都用.)
		3) 结构体的访问方式有点类似于数组下标的方式.
		
	思考：结构体变量的.或者->访问结构体元素的实质是什么？
	
		  其实本质上还是用指针来访问的. (. , -> 是编译器提供的一种包装形式)

	测试:
		struct myStruct
		{
			int a;			// 4 
			double b;		// 8
			char c;
		};

		struct myStruct s1;
		s1.a = 12;			// int *p = (int *)&s1; 				*p = 12;
		s1.b = 4.4;			// double *p = (double *)(&s1 + 4); 	*p = 4.4;
		s1.c = 'a';			// char *p = (char *)((int)&s1 + 12); 	*p = 'a';
		
		这里s1是一个变量, &s1为变量的地址. &s1 + 1 = 首地址 + 1
		如果struct myStruct * p = &s1;   p + 1 = 首地址 + sizeof(struct myStruct)
		
		(!!!!!!!) . -> 访问时, 编译器会进行以上操作. 编译器知道每一个元素应该偏移到多少, 需要考虑
		          内存对其的问题.
		
		(!!!!!!!)(struct myStruct是一种数据结构, sizeof(struct myStruct))

//=======================================================================================================
								4.5.8-10.结构体的对齐访问1-3
//-------------------------------------------------------------------------------------------------------
	1. 举例说明什么是结构体对齐访问
	
		1) 上节讲过结构体中元素的访问其实本质上还是用指针方式, 结合这个元素在整个结构体中的偏移量和
		   这个元素的类型来进行访问的.
		2) 但是实际上结构体的元素的偏移量比我们上节讲的还要复杂, 因为结构体要考虑元素的对齐访问, 所
		   以每个元素时间占的字节数和自己本身的类型所占的字节数不一定完全一样. (譬如char c实际占字节
		   数可能是1, 也可以是2, 也可能是3, 也可以能4····).
		3) 一般来说, 我们用.的方式来访问结构体元素时, 我们是不用考虑结构体的元素对齐的. 因为编译器会
		   帮我们处理这个细节. 
		   
		总结: 
			1) 访问结构体元素,我们是不用考虑结构体的元素对齐的. 因为编译器会帮我们处理这个细节. 
			2) 因为C语言本身是很底层的语言, 而且做嵌入式开发经常需要从内存角度, 以指针方式来处理结构
		       体及其中的元素, 因此还是需要掌握结构体对齐规则.

	2. 结构体为何要对齐访问
	
		1) 结构体中元素对齐访问主要原因是为了配合硬件, 也就是说硬件本身有物理上的限制, 如果对齐排布和
		   访问会提高效率, 否则会大大降低效率.
		2) 内存本身是一个物理器件(DDR内存芯片, SoC上的DDR控制器), 本身有一定的局限性: 如果内存每次访问
		   时按照4字节对齐访问, 那么效率是最高的; 如果不对齐访问效率要低很多.
		3) 还有很多别的因素和原因, 导致我们需要对齐访问. 譬如Cache的一些缓存特性, 还有其他硬件(譬如
		   MMU、LCD显示器)的一些内存依赖特性, 所以会要求内存对齐访问.
		4) 对比对齐访问和不对齐访问：对齐访问牺牲了内存空间, 换取了速度性能; 而非对齐访问牺牲了访问速
		   度性能, 换取了内存空间的完全利用.

	3. 结构体对齐的规则和运算
	
		编译器本身可以设置内存对齐的规则, 有以下的规则需要记住：

		32位编译器, 一般编译器默认对齐方式是4字节对齐.

		1) 对齐原则(以4字节对齐举例):
		
			a) 结构体本身: 结构体变量放置在4字节对齐处; 整体对齐后的大小是4字节的整数倍.
			b) 对于每一个元素而言, 也需要符合本身数据类型的对齐规则.
			c) 满足以上两点最少内存.
			
		2) 举例1
			struct mystruct1
			{					// 1字节对齐	4字节对齐
				int a;			// 4			4
				char b;			// 1			2(1+1)
				short c;		// 2			2
			};
			
			对齐分析:
			a) 整个结构体, 整个结构体变量4字节对齐是由编译器保证的, 我们不用操心.
			b) a的开始地址就是整个结构体的开始地址, 所以自然是4字节对齐的. a的长度也是4, 所以a
			   的结束地址与下一个变量无关.
			c) 因为上一个元素a本身占4字节, 本身就是对齐的. 所以留给b的开始地址也是4字节对齐地址, 所以
			   b可以直接放(b放的位置就决定了a一共占4字节, 因为不需要填充). b的起始地址定了后, 结束地址
			   不能定(因为可能需要填充), 结束地址要看下一个元素来定.
			d) 第三个元素c, short类型需要2字节对齐(short类型元素必须放在类似0,2,4,6这样的地址处,不能
			   放在1,3这样的奇数地址处), 因此c不能紧挨着b来存放, 解决方案是在b之后添加1字节的填充
			   (padding), 然后再开始放c. 
			   
			e) c放完之后还没结束当整个结构体的所有元素都对齐存放后, 还没结束, 因为整个结构体大小还
			   要是4的整数倍.
		3) 举例
			typedef struct mystruct2
			{					// 1字节对齐	4字节对齐
				char a;			// 1			4(1+3)
				int b;			// 4			4
				short c;		// 2			4(2+2)
			}MyS2;	
			
			struct stu
			{							// 1字节对齐	4字节对齐
				char sex;				// 1			4(1+3)
				int length;				// 4			4
				char name[10];			// 10			12(10+2)
			};	
			
	4. gcc支持但不推荐的对齐指令：#pragma pack()   #pragma pack(n) (n=1/2/4/8)
	
		1) #pragma是用来指挥编译器, 或者说设置编译器的对齐方式的.
		
		   编译器的默认对齐方式是4, 但是有时候我不希望对齐方式是4, 而希望是别的(譬如希望1字节对齐,
		   也可能希望是8, 甚至可能希望128字节对齐).
		   
		2) 我们需要#prgama pack(n)开头, 以#pragma pack()结尾, 定义一个区间, 这个区间内的对齐参数就
		   是n.
		   
		3) #prgma pack的方式在很多C环境下都是支持的, 但是gcc虽然也可以不过不建议使用.
		
		(!!!!!!???????) 这种方法最后测试, n=1,4时与上述叙述一致. n = 3,8,256时并不一致. 原因没有
         仔细分析, 先保留.		

	5. gcc推荐的对齐指令__attribute__((packed))  __attribute__((aligned(n)))
	
		1) __attribute__((packed)) 使用时直接放在要进行内存对齐的类型定义的后面, 然后它起作用的范围
		   只有加了这个东西的这一个类型. packed的作用就是取消对齐访问.
		   
		2) __attribute__((aligned(n))) 使用时直接放在要进行内存对齐的类型定义的后面, 然后它起作用的
		   范围只有加了这个东西的这一个类型. 它的作用是让整个结构体变量整体进行n字节对齐(注意是结构
		   体变量整体n字节对齐, 而不是结构体内各元素也要n字节对齐).
		   
		(!!!!!?????) 实际测试,与上述叙述也不相同. 包括视频, 也说的不对. 这里可以明确的有两点:
			__attribute__((packed))   : 取消了对齐, 就是上文说的1字节对齐的情况.
			__attribute__((aligned(4))) : 四字节对齐, 与上文的4字节对齐情况相同.
			
			
	6. 参考阅读blog：
		http://www.cnblogs.com/dolphin0520/archive/2011/09/17/2179466.html
		http://blog.csdn.net/sno_guo/article/details/8042332

//=======================================================================================================
								4.5.11.offsetof宏与container_of宏
//-------------------------------------------------------------------------------------------------------
	1. 由结构体指针进而访问各元素的原理
	
		1) 通过结构体整体变量来访问其中各个元素, 本质上是通过指针方式来访问的, 形式上是通过.的方式来
		   访问的(这时候其实是编译器帮我们自动计算了偏移量).
		   
		2) 测试:
			struct mystruct
			{
				char a;			// 0
				int b;			// 4
				short c;		// 8
			};
			
			struct mystruct s1;
			s1.b = 12;
			
			int *p = (int *)((char *)&s1 + 4);		// s1结构体变量的地址, 强制转化为 char * , 
			printf("*p = %d.\n", *p);				// 由于对齐, +4 得到b的地址. 在转化为int * , 
													// 解引用即可得到元素b的内容.
													
	2. offsetof宏：
	
		1) offsetof宏的作用是：用宏来计算结构体中某个元素和结构体首地址的偏移量(其实质是通过编译器
		   来帮我们计算).
		   
		2) offsetof宏的原理：我们虚拟一个type类型结构体变量, 然后用type.member的方式来访问那个member
		   元素, 继而得到member相对于整个变量首地址的偏移量.
		   
		3) 学习思路：第一步先学会用offsetof宏, 第二步再去理解这个宏的实现原理.
		
			#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)
	
		
			a) (TYPE *)0 是一个强制类型转换, 把0地址强制类型转换成一个指针, 这个指针指向一个TYPE类型
			   的结构体变量.  (实际上这个结构体变量可能不存在, 但是只要我不去解引用这个指针就可以).
			   
			b) ((TYPE *)0)->MEMBER	(TYPE *)0是一个TYPE类型结构体变量的指针, 通过指针指针来访问这个
			   结构体变量的member元素.

			c) &((TYPE *)0)->MEMBER  等效于&(((TYPE *)0)->MEMBER), 意义就是得到member元素的地址.
			   但是因为整个结构体变量的首地址是0. 所以就得到了元素的偏移量.
			   
		4) 使用举例:
			
			struct mystruct
			{
				char a;			// 0
				int b;			// 4
				short c;		// 8
			};

			#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)
			
			int offsetofb = offsetof(struct mystruct, b);		// 第一个参数是类型, 需要有struct
			printf("offsetofb = %d.\n", offsetofb);

	3. container_of宏：
	
		1) 作用：知道一个结构体中某个元素的指针, 反推这个结构体变量的指针. 
		
		2) 有了container_of宏, 可以从一个元素的指针得到整个结构体变量的指针, 继而得到结构体中其他
		   元素的指针. 
		   
		3) typeof关键字的作用是：typeof(a)时由变量a得到a的类型, typeof就是由变量名得到变量数据类型.
		
		4) 这个宏的工作原理：先用typeof得到member元素的类型定义成一个指针, 然后用这个指针减去该元素
		   相对于整个结构体变量的偏移量(偏移量用offsetof宏得到的), 减去之后得到的就是整个结构体变量
		   的首地址了, 再把这个地址强制类型转换为type *即可得到结构体变量的地址.

		5) 使用举例
		
			// ptr是指向结构体元素member的指针，type是结构体类型，member是结构体中一个元素的元素名
			// 这个宏返回的就是指向整个结构体变量的指针，类型是(type *)
			#define container_of(ptr, type, member) ({			\
			const typeof(((type *)0)->member) * __mptr = (ptr);	\
			(type *)((char *)__mptr - offsetof(type, member)); })


			struct mystruct s1;
			struct mystruct *pS = NULL;
			
			short *p = &(s1.c);					// p就是指向结构体中某个member的指针
			
			// 问题是要通过p来计算得到s1的指针
			pS = container_of(p, struct mystruct, c);
			
			printf("pS等于：%p.\n", pS);		// 结构体变量s1的地址(指针)


	4. 这两个宏的学习指南和要求：
	
		1) 最基本要求是：必须要会这两个宏的使用. 就是说能知道这两个宏接收什么参数, 返回什么值, 会用
		   这两个宏来写代码, 看见代码中别人用这两个宏能理解什么意思.
		2) 升级要求：能理解这两个宏的工作原理, 能表述出来. (有些面试笔试题会这么要求)
		3) 更高级要求：能自己写出这两个宏(不要着急,慢慢来)

	5. 附录1, typeof的用法
		
		1) typeof不是C语言本身的关键词或运算符(sizeof是C标准定义的运算符), 它是GCC的一个扩展, 作用正
			如其字面意思, 用某种已有东西(变量、函数等)的类型去定义新的变量类型.
		2) typeof通常用于宏定义中，一些示例用法如下：
			typeof(var)
			typeof(a[0])
			typeof(int *)
			typeof(fun())
		3) 可以看到, typeof()中可以是任何有类型的东西, 变量就是其本身的类型, 函数是它返回值的类型.
		   typeof一般用于声明变量, 如：
			
			typeof(a) var;

	6. 附录2, C语言中()的用法
	
		1) 聚组
			聚组是用来改变运算优先级，实例如下：
			例子1： data = （x + y）*5 ;
			例子2： int (*pointer)[3] ;			// 数组指针. 如果没有()则p先跟[]结合, 就是指针数组.

		2) 函数调用
			函数调用是用来调用函数, 实例如下：
			例子1： func(a , b);
			例子2： (*func_p)(c , d);

		3) 类型转换
			类型转换是用强制类型转换，实例如下：
			例子1： float a = 3.14;
					int b = (int)a;

		4) 复合语句表达式(!!!!!*****!!!!!)
			复合语句表达式是将复合语句通过小括号括起来后, 可以当做表达式, 通常在GUN C中使用.
			实例如下:

			例子1： data = ( {int i,j; i = 2 ; j = i*2 + 1; } );	// data 值为5	
	
	7. container_of宏中复合语句表达式测试：
	
		1) 编译成功, a = 11.
			int a=0;
	
			a =   ({\
			const int b = 6; \
			(b+5);});
			
		2) 编译成功, a = 15

			int b = 5;
			
			a = ({b = 2*b; b+5;});
			
		注意(!!!!!): 必须有(); 必须有{}. 

//=======================================================================================================
									4.5.12.共用体union
//-------------------------------------------------------------------------------------------------------
	1. 共用体类型的定义、变量定义和使用
	
		1) 共用体union和结构体struct在类型定义、变量定义、使用方法上很相似.
		
		2) 共用体和结构体的不同：结构体类似于一个包裹, 结构体中的成员彼此是独立存在的, 分布在内存的
		   不同单元中, 他们只是被打包成一个整体叫做结构体而已; 共用体中的各个成员其实是一体的, 彼此
		   不独立, 他们使用同一个内存单元. 可以理解为：有时候是这个元素, 有时候是那个元素. 更准确的
		   说法是同一个内存空间有多种解释方式.
		   
		3) 共用体union就是对同一块内存中存储的二进制的不同的理解方式. 
		
		4) 在有些书中把union翻译成联合(联合体), 这个名字不好. 现在翻译成共用体比较合适.
		
		5) union的sizeof测到的大小实际是union中各个元素里面占用内存最大的那个元素的大小. 因为可以存
		   的下这个就一定能够存的下其他的元素.
		   
		6) union中的元素不存在内存对齐的问题, 因为union中实际只有1个内存空间, 都是从同一个地址开始的
		   (开始地址就是整个union占有的内存空间的首地址), 所以不涉及内存对齐.
		   
	2. 共用体使用

		// a和b其实指向同一块内存空间, 只是对这块内存空间的2种不同的解析方式. 
		// 如果我们使用u1.a那么就按照int类型来解析这个内存空间; 如果我们使用u1.b那么就按照char类型
		// 来解析这块内存空间.
		union myunion
		{
			int a;
			char b;
		};
		
		union myunion u1;		// 共用体变量的定义
		u1.a = 23;				// 共用体元素的使用
		printf("u1.b = %d.\n", u1.b);		// u1.b = 23.结论是u1.a和u1.b是相关的
		// a和b的地址一样, 充分说明a和b指向同一块内存, 只是对这块内存的不同解析规则(!!!!!!!)
		printf("&u1.a = %p.\n", &u1.a);
		printf("&u1.b = %p.\n", &u1.b);
		

	3. 共用体和结构体的相同和不同
	
		1) 相同点就是操作语法几乎相同.
		2) 不同点是本质上的不同. struct是多个独立元素(内存空间)打包在一起; 
		   union是一个元素(内存空间)的多种不同解析方式.

	4. 共用体的主要用途
	
		1) 用于对同一个内存单元进行多种不同规则解析的情况.
		
		2) C语言中其实是可以没有共用体的, 用指针和强制类型转换可以替代共用体完成同样的功能, 
		   但是共用体的方式更简单、更便捷、更好理解.
		   
			union test
			{
				int a;
				float b;
			};
				   
			union test t1;
			t1.a = 1123477881;
			printf("value = %f.\n", t1.b);
			
			int a = 1123477881;
			printf("指针方式：%f.\n", *((float *)&a));	// 没有用共用体,用指针强制转换同样达到目的.

//=======================================================================================================
									4.5.13.大小端模式1
//-------------------------------------------------------------------------------------------------------
	1. 什么是大小端模式
	
		1) 大端模式(big endian)和小端模式(little endian).
		
		2) 后来计算机通信发展起来后, 遇到一个问题就是：在串口等串行通信中, 一次只能发送1个字节. 这时
		   候要发送一个int类型的数就遇到一个问题. int类型有4个字节, 是按照：byte0 byte1 byte2 byte3
		   这样的顺序发送, 还是按照byte3 byte2 byte1 byte0这样的顺序发送. 规则就是发送方和接收方必须
		   按照同样的字节顺序来通信, 否则就会出现错误. 这就叫通信系统中的大小端模式. 这是大小端这个
		   词和计算机挂钩的最早问题.
		   
		3) 现在我们讲的这个大小端模式, 更多是指计算机存储系统的大小端.
			
				在计算机内存/硬盘/Nnad中, 因为存储系统是32位的, 但是数据仍然是按照字节为单位的. 于是
			乎一个32位的二进制在内存中存储时有2种分布方式：高字节对应低地址(大端模式)、高字节对应高
			地址(小端模式).
			
		4) 大端模式和小端模式本身没有对错, 没有优劣, 理论上按照大端或小端都可以, 但是要求必须存储时
		   和读取时按照同样的大小端模式来进行, 否则会出错.
		   
		5) 现实的情况就是：有些CPU公司用大端(譬如C51单片机); 有些CPU用小端(譬如ARM). 
		   (大部分是用小端模式, 大端模式的不算多). 于是乎我们写代码时, 当不知道当前环境是用大端模式
		   还是小端模式时就需要用代码来检测当前系统的大小端.
		   
		总结:  	1) 存取和读取数据时,都按照同一种方式即可.
				
				2) 小端模式: 高字节对应高地址 (相同的是小端模式; GCC, win中的上位机程序, 一般是小端
							  模式)
				  大端模式: 高字节对应低地址 (相反的是大端模式; 51单片机是大端模式)

				3) 在keil C51中, 用软件仿真测试的话, 就是大端模式. 说明51编译器是大端模式.
				   在MDK中测试, 则是小端模式, 因为ARM是小端, 所以MDK编译器也是小端模式.
				   
		经典笔试题：用C语言写一个函数来测试当前机器的大小端模式.
		

	2. 用union来测试机器的大小端模式
	
		// 共用体中很重要的一点：a和b都是从低地址开始的.
		// b所在的地址是0而不是3.
		union myunion
		{
			int a;
			char b;
		};

		// 如果是小端模式则返回1，小端模式则返回0
		int is_little_endian(void)
		{
			union myunion u1;
			
			u1.a = 1;					// 地址0的那个字节内是1(小端)或者0(大端)
			
			return u1.b;
		}
		
	3. 指针方式来测试机器的大小端

		int is_little_endian2(void)
		{
			int a = 1;
			
			char b = *((char *)(&a));	// 指针方式其实就是共用体的本质
			
			return b;
		}

//=======================================================================================================
									4.5.14.大小端模式2
//-------------------------------------------------------------------------------------------------------
	1. 看似可行实则不行的测试大小端方式：位与、移位、强制类型转化

		1) 位与运算
		
			结论：位与的方式无法测试机器的大小端模式. (表现就是大端机器和小端机器的&运算后的值相同的)
			理论分析：位与运算是编译器提供的运算, 这个运算是高于内存层次的(或者说&运算在二进制层次具
			          有可移植性, 也就是说&的时候一定是高字节&高字节, 低字节&低字节, 和二进制存储无关).
		2) 移位
		
			结论：移位的方式也不能测试机器大小端.
			理论分析：原因和&运算符不能测试一样, 因为C语言对运算符的级别是高于二进制层次的. 右移运算
			          永远是将低字节移除, 而和二进制存储时这个低字节在高位还是低位无关的.

		3) 强制类型转换
			同上


	2. 通信系统中的大小端(数组的大小端)
	
		1) 譬如要通过串口发送一个0x12345678给接收方, 但是因为串口本身限制, 只能以字节为单位来发送,
		   所以需要发4次; 接收方分4次接收, 内容分别是：0x12、0x34、0x56、0x78. 接收方接收到这4个字
		   节之后需要去重组得到0x12345678(而不是得到0x78563412).
		   
		2) 所以在通信双方需要有一个默契, 就是：先发/先接的是高位还是低位? 这就是通信中的大小端问题.
		
		3) 一般来说是：先发低字节叫小端; 先发高字节就叫大端. 实际操作中, 在通信协议里面会去定义大小
		   端, 明确告诉你先发的是低字节还是高字节.
		   
		4) 在通信协议中, 大小端是非常重要的, 大家使用别人定义的通信协议还是自己要去定义通信协议, 一
		   定都要注意标明通信协议中大小端的问题.

//=======================================================================================================
										4.5.15.枚举
//-------------------------------------------------------------------------------------------------------
	1. 枚举是用来干嘛的?
	
		1) 枚举在C语言中其实是一些符号常量集. 直白点说：枚举定义了一些符号, 这些符号的本质就是int类型
		   的常量, 每个符号和一个常量绑定. 这个符号就表示一个自定义的一个识别码, 编译器对枚举的认知就
		   是符号常量所绑定的那个int类型的数字.
		   
		2) 枚举中的枚举值都是常量, 怎么验证?
		
		3) 枚举符号常量和其对应的常量数字相对来说, 数字不重要, 符号才重要. 符号对应的数字只要彼此不相
		   同即可, 没有别的要求. 所以一般情况下我们都不明确指定这个符号所对应的数字, 而让编译器自动分
		   配.(编译器自动分配的原则是：从0开始依次增加. 如果用户自己定义了一个值, 则从那个值开始往后
		   依次增加)
		   

	2. 语言为何需要枚举
	
	1) C语言没有枚举是可以的. 使用枚举其实就是对1、0这些数字进行符号化编码, 这样的好处就是编程时可以不
	   用看数字而直接看符号. 符号的意义是显然的, 一眼可以看出. 而数字所代表的含义除非看文档或者注释.
	   
	2) 宏定义的目的和意义是：不用数字而用符号. 从这里可以看出：宏定义和枚举有内在联系. 宏定义和枚举经
	   常用来解决类似的问题, 他们俩基本相当可以互换, 但是有一些细微差别.
	   
	3. 宏定义和枚举的区别
	
		1) 枚举是将多个有关联的符号封装在一个枚举中, 而宏定义是完全散的. 也就是说枚举其实是多选一.
		
		2) 什么情况下用枚举? 当我们要定义的常量是一个有限集合时(譬如一星期有7天, 譬如一个月有31天,
		   譬如一年有12个月····), 最适合用枚举. (其实宏定义也行, 但是枚举更好)
		   
		3) 不能用枚举的情况下(定义的常量符号之间无关联, 或者无限的)用宏定义.
		
		4) 枚举值的递增, 可以是用来在枚举中定义项数, 这样在一些数组定义时很有用. 参考68400项目中的大量
           的枚举.		
		
		总结：宏定义先出现, 用来解决符号常量的问题; 后来人们发现有时候定义的符号常量彼此之间有关联
		      (多选一的关系), 用宏定义来做虽然可以但是不贴切, 于是乎发明了枚举来解决这种情况.

	4. 枚举的定义和使用
		1) 
			// 这个枚举用来表示函数返回值，ERROR表示错，RIGHT表示对
			enum return_value
			{
				ERROR,				// 枚举值常量是全局的，直接自己就可以用。
				RIGHT,
			};

			enum return_value func1(void)
			{
				enum return_value r1;
				r1 = ERROR;
				return r1;
			}


			int main(void)
			{
				enum return_value r = func1();

				if (r == RIGHT)			// 不是r.RIGHT，也不是return_value.RIGHT
				{
					printf("函数执行正确\n");
				}
				else
				{
					printf("函数执行错误\n");
				}
				
				return 0;
			}
			
		2) 说明
			a) 枚举值常量是全局的, 直接自己就可以用. 使用时不用加 . 访问.
			
			b) 不能有重名的枚举类型. 即在一个文件中不能有两个或两个以上的enum被typedef成相同的别名.
				分析：这很好理解, 因为将两种不同类型重命名为相同的别名, 这会让gcc在还原别名时遇到困惑.
				
			c) 不能有重名的枚举成员.
				分析：经过测试, 两个struct类型内的成员名称可以重名, 而两个enum类型中的成员不可以重名.
				实际上从两者的成员在访问方式上的不同就可以看出了:
					struct类型成员的访问方式是：变量名.成员; 而enum成员的访问方式为：成员名.
					
				两个#define宏定义是可以重名的, 该宏名真正的值取决于最后一次定义的值. 编译器会给出警告
				但不会error.

//=======================================================================================================

