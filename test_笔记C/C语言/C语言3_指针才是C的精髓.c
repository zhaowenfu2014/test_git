/*
//=======================================================================================================
									4.3.指针才是C的精髓
//=======================================================================================================
4.3.1.指针到底是什么？
4.3.2.指针带来的一些符号的理解
4.3.3.野指针问题
4.3.4.const关键字与指针
4.3.5.深入学习一下数组
4.3.6.指针与数组的天生姻缘
4.3.7.指针与强制类型转换
4.3.8.指针、数组与sizeof运算符
4.3.9.指针与函数传参
4.3.10.输入型参数与输出型参数
//=======================================================================================================
								4.3.1.指针到底是什么？
//-------------------------------------------------------------------------------------------------------
	1. 指针变量和普通变量的区别
	
		1)首先必须非常明确：指针的实质就是个变量, 它跟普通变量没有任何本质区别.
		
		2) 指针完整的名字应该叫指针变量, 简称为指针.
		
		(!!!!!!)从内存变量在内存中的存储看, 其实和int类型的变量完全一样.
		int a; int *p;
		
		a) 存储都是4个字节.
		b) 按照道理: a=4; p=4 本质上可以这么赋值. 只是编译器不允许给p赋值一个普通的int类型.
		c) 因此给p赋值时,需要强制转换. p = (int *)4.
		
	2. 为什么需要指针?
	
		1) 指针的出现是为了实现间接访问. 在汇编中都有间接访问, 其实就是CPU的寻址方式中的间接寻址.
		
		2) 间接访问(CPU的间接寻址)是CPU设计时决定的, 这个决定了汇编语言必须能够实现间接寻址, 又决
		   定了汇编之上的C语言也必须实现简介寻址.
		   
		3) 高级语言如Java、C#等没有指针, 那他们怎么实现间接访问? 答案是语言本身帮我们封装了.
		
	3. 指针使用三部曲：定义指针变量、关联指针变量、解引用
		1) 定义指针变量
			int *p;
		2) 绑定指针, 也就是给指针变量赋值. 绑定前,不能被解引用.
			p = &a; 
			p = (int *)0x3000000;
		3) 解引用.
			*p = 10;
			
	4. 指针说明
	
		1) 当我们int *p定义一个指针变量p时, 因为p是局部变量, 所以也遵循C语言局部变量的一般规律(定义
		   局部变量并且未初始化, 则值是随机的), 所以此时p变量中存储的是一个随机的数字.
		2) 此时如果我们解引用p, 则相当于我们访问了这个随机数字为地址的内存空间. 那这个空间到底能不能
		   访问不知道(也许行也许不行), 所以如果直接定义指针变量未绑定有效地址就去解引用几乎必死无疑.
		3) 指针绑定的意义就在于：让指针指向一个可以访问、应该访问的地方, 指针的解引用是为了间接访问
		   目标变量.

	总结:
		1) 指针变量,就是一个变量.
		2) 	printf("p = %p.\n", p);			// 打印p的值,按照指针变量的形式(!!!!!)	
			printf("p = %d.\n", p);			// 有一个警告. 打印p的值,按照int的格式.(!!!!!)
			printf("p = 0x%x.\n", p);		// 有一个警告. 打印指针变量的值.按照
			
			第一个和第三个打印的是一样的. 第二个可能打印一个负号. 
			
//=======================================================================================================
								4.3.2.指针带来的一些符号的理解
//-------------------------------------------------------------------------------------------------------
	1. 星号*
	
		1) C语言中 * 可以表示乘号, 也可以表示指针符号. 这两个用法是毫无关联的, 使用不会带来混淆.
		2) 星号在用于指针相关功能的时候有2种用法：
			(!!!!!) 第一种是指针定义时, *结合前面的类型用于表明要定义的指针的类型, 
			(!!!!!) 第二种功能是指针解引用, 解引用时*p表示p指向的变量本身.
		总结:
				1) *号虽然靠近p, 但是是与前面类型结合的.
				2) int *p;
				   int * p;
				   int*p;
				   int* p;
				   这四种写法都没有正确,且没有警告.
				3) int *p1, *p2, p3  // 定义了两个指针,一个int变量. 

				4) int *p = &a; 因此,这里也证明, int *p 理解为int * 比较合适.
				   

	2. 取地址符&
	
		1)取地址符使用时直接加在一个变量的前面, 然后取地址符和变量加起来构成一个新的符号, 这个符号
		  表示这个变量的地址.

	3. 指针定义并初始化、与指针定义然后赋值的区别
	
		1) 指针定义时可以初始化, 指针的初始化其实就是给指针变量初值(跟普通变量的初始化没有本质区别).
		2) 指针变量定义同时初始化的格式是：int a = 32; int *p = &a;
		2) 不初始化时指针变量先定义再赋值：int a = 32; int *p; 	p = &a;		
		
	4. 左值与右值
	
		1) 放在赋值运算符左边的就叫左值, 右边的就叫右值. 所以赋值操作其实就是：左值 = 右值;
		2) 当一个变量做左值时, 编译器认为这个变量符号的真实含义是这个变量所对应的那个内存空间;
		   当一个变量做右值时, 编译器认为这个变量符号的真实含义是这个变量的值, 也就是这个变量所对应
		   的内存空间中存储的那个数.
		3) 左值与右值的区别, 就好象现实生活中“家”这个字的含义. 譬如“我回家了”, 这里面的家指的是你家
		   的房子(类似于左值); 但是说“家比事业重要”, 这时候的家指的是家人(家人就是住在家所对应的那
		   个房子里面的人, 类似于右值).

	总结:	
			1) 一个变量a, 可能表示两个信息: 对应的内存空间, 内存内容.
			   作为左值时, 表示内存空间; 作为右值时, 表示的是内存的内容.
			   
				int a = 3, b = 5;
			
				a = b;		// 当a做左值时，我们关心的是a所对应的内存空间，而不是其中存储的3
				b = a;		// 当a做右值时，我们关心的是a所对应空间中存储的数，也就是5

//=======================================================================================================
										4.3.3.野指针问题
//-------------------------------------------------------------------------------------------------------
	1. 神马是野指针? 哪里来的? 有什么危害?
	
		1) 野指针. 就是指针指向的位置是不可知的(随机的、不正确的、没有明确限制的).
		2) 野指针很可能触发运行时段错误(Sgmentation fault).
		3) 因为指针变量在定义时如果未初始化, 值也是随机的. 指针变量的值其实就是别的变量(指针所指向
		   的那个变量)的地址, 所以意味着这个指针指向了一个地址是不确定的变量, 这时候去解引用就是去
		   访问这个地址不确定的变量, 所以结果是不可知的.
		4) 野指针因为指向地址是不可预知的, 所以有3种情况：
			a) 第一种是指向不可访问(操作系统不允许访问的敏感地址, 譬如内核空间)的地址, 结果是触发段
			   错误, 这种算是最好的情况了; 
			b) 第二种是指向一个可用的、而且没什么特别意义的空间(譬如我们曾经使用过但是已经不用的栈
			   空间或堆空间), 这时候程序运行不会出错, 也不会对当前程序造成损害, 这种情况下会掩盖你
			   的程序错误, 让你以为程序没问题, 其实是有问题的; 
			c) 第三种情况就是指向了一个可用的空间, 而且这个空间其实在程序中正在被使用(譬如说是程序
			   的一个变量x), 那么野指针的解引用就会刚好修改这个变量x的值, 导致这个变量莫名其妙的被
			   改变, 程序出现离奇的错误. 一般最终都会导致程序崩溃, 或者数据被损害. 这种危害是最大的.
		5) 指针变量如果是局部变量, 则分配在栈上, 本身遵从栈的规律(反复使用, 使用完不擦除, 所以是脏
		   的, 本次在栈上分配到的变量的默认值是上次这个栈空间被使用时余留下来的值), 就决定了栈的使
		   用多少会影响这个默认值. 

	2. 怎么避免野指针?
	
		1) 野指针的错误来源就是指针定义了以后没有初始化, 也没有赋值(总之就是指针没有明确的指向一个可
		   用的内存空间), 然后去解引用.
		2) 知道了野指针产生的原因, 避免方法就出来了：在指针的解引用之前, 一定确保指针指向一个绝对可用
		   的空间.
		3) 常规的做法是：
			第一点：定义指针时, 同时初始化为NULL.
			第二点：在指针解引用之前, 先去判断这个指针是不是NULL.
			第三点：指针使用完之后, 将其赋值为NULL.
			第四点：在指针使用之前, 将其赋值绑定给一个可用地址空间.
		4) 野指针的防治方案4点绝对可行, 但是略显麻烦. 很多人懒得这么做, 那实践中怎么处理? 在中小型程
		   序中, 自己水平可以把握的情况下, 不必严格参照这个标准; 但是在大型程序, 或者自己水平感觉不好
		   把握时, 建议严格参照这个方法.


	3. NULL到底是什么?
	
	1) NULL在C/C++中定义为：
		#ifdef _cplusplus			// 定义这个符号就表示当前是C++环境
		#define NULL 0				// 在C++中NULL就是0
		#else
		#define NULL (void *)0		// 在C中NULL是强制类型转换为void *的0, 确保任何类型的指针都可以
		#endif						// 赋值NULL

	2) 在C语言中, int *p; 可以p = (int *)0; 但是不可以p = 0; 因为类型不相同. 
	3) 所以NULL的实质其实就是0, 然后我们给指针赋初值为NULL, 其实就是让指针指向0地址处. 
	
		//---------------------!!!!!!!!*******!!!!!!!!--------------------------------
   	   为什么指向0地址处? 2个原因. 第一层原因是0地址处作为一个特殊地址(我们认为指针指向这里就表示指针
	   没有被初始化, 就表示是野指针); 第二层原因是这个地址0地址在一般的操作系统中都是不可被访问的, 如
	   果C语言程序员不按规矩(不检查是否等于NULL就去解引用)写代码直接去解引用就会触发段错误, 这种已经是
	   最好的结果了.
		//---------------------!!!!!!!!*******!!!!!!!!--------------------------------
	   
	4) 一般在判断指针是否野指针时, 都写成:
		if (NULL != p)

//=======================================================================================================
									4.3.4.const关键字与指针
//-------------------------------------------------------------------------------------------------------
	1. const关键字
		
		1) const关键字, 在C语言中用来修饰变量, 表示这个变量是常量.
		2) 指针也属于变量, 所以可以用const来修饰.
	
	2. const修饰指针有4种形式, 区分清楚这4种即可全部理解const和指针.
	
		第一种：const int *p;
		第二种：int const *p;
		第三种：int * const p;
		第四种：const int * const p;

		关于指针变量的理解, 主要涉及到2个变量：第一个是指针变量p本身, 第二个是p指向的那个变量(*p).
		一个const关键字只能修饰一个变量, 所以弄清楚这4个表达式的关键就是搞清楚const放在某个位置是
		修饰谁的.
		
		const int *p1;			// p本身不是cosnt的, 而p指向的变量是const的
		int const *p2;			// p本身不是cosnt的, 而p指向的变量是const的 (!!!!!!!)
		int * const p3;			// p本身是cosnt的, p指向的变量不是const的
		const int * const p4;	// p本身是cosnt的, p指向的变量也是const的
			
		总结: 1) 这里需要注意 int const *p; 这里不像定义时理解的(*与int结合), 应该把*p结合起来认为指向
		         的变量时常量.
			  2) const 如果紧挨着p, 才修饰指针. 
			  
	3. const修饰的变量真的不能改吗?
	
		1) 课堂练习说明：const修饰的变量其实是可以改的(前提是gcc环境下):

			const int a = 5;
			//a = 6;				// error: assignment of read-only variable ‘a’
			int *p;
			p = (int *)&a;			// 这里报警高可以通过强制类型转换来消除
			*p = 6;
			printf("a = %d.\n", a);	// a = 6,结果证明const类型的变量被改了
			
		2) 在某些单片机环境下, const修饰的变量是不可以改的. const修饰的变量到底能不能真的被修改,取
		   决于具体的环境, C语言本身并没有完全严格一致的要求. 

		3) 在gcc中, const是通过编译器在编译的时候执行检查来确保实现的(也就是说const类型的变量不能
		   改是编译错误, 不是运行时错误). 所以我们只要想办法骗过编译器, 就可以修改const定义的常量,
		   而运行时不会报错.
		   
		4) 更深入一层的原因, 是因为gcc把const类型的常量也放在了data段, 其实和普通的全局变量放在data
		   段是一样实现的, 只是通过编译器认定这个变量是const的, 运行时并没有标记const标志, 所以只要
		   骗过编译器就可以修改了.

	4. const究竟应该怎么用
	
		1) const是在编译器中实现的, 编译时检查, 并非不能骗过.
		2) 在C语言中使用const, 就好象是 一种道德约束而非法律约束, 所以大家使用const时更多是传递一
		   种信息, 就是告诉编译器、也告诉读程序的人, 这个变量是不应该也不必被修改的.

//=======================================================================================================
									4.3.5.深入学习一下数组
//-------------------------------------------------------------------------------------------------------
	1. 从内存角度来理解数组
	
		1) 从内存角度讲, 数组变量就是一次分配多个变量, 而且这多个变量在内存中的存储单元是依次相连接. 
		2) 我们分开定义多个变量(譬如int a, b, c, d;)和一次定义一个数组(int a[4]); 这两种定义方法相同
		   点是都定义了4个int型变量, 而且这4个变量都是独立的单个使用的; 不同点是单独定义时a、b、c、d
		   在内存中的地址不一定相连, 但是定义成数组后, 数组中的4个元素地址肯定是依次相连的.
		3) 数组中多个变量虽然必须单独访问, 但是因为他们的地址彼此相连, 因此很适合用指针来操作, 因此数
		   组和指针天生就叫纠结在一起.
		   
		总结: 数组地址连续,所以与指针来操作. 因此指针与和数组就是天生纠结在一块的.

	2. 从编译器角度来理解数组
	
		1) 从编译器角度来讲, 数组变量也是变量, 和普通变量和指针变量并没有本质不同. 变量的本质就是一个
		   地址, 这个地址在编译器中决定具体数值, 具体数值和变量名绑定, 变量类型决定这个地址的延续长度.
		2) 搞清楚：变量、变量名、变量类型这三个概念的具体含义, 很多问题都清楚了.
			int a;  char a;

	3. 数组中几个关键符号(a a[0] &a &a[0])的理解(前提是 int a[10])
	
		1) 这4个符号搞清楚了, 数组相关的很多问题都有答案了. 理解这些符号的时候要和左值右值结合起来,
		   也就是搞清楚每个符号分别做左值和右值时的不同含义.
		   
		2) a就是数组名.
			a) a做左值时表示整个数组的所有空间(10×4=40字节), 又因为C语言规定数组操作时要独立单个操作, 
			   不能整体操作数组, 所以a不能做左值(!!!!****); 
			   (!!!!????这里不是应该理解为a是地址,是常量,不能做左值?)
		    b) a做右值表示数组首元素(数组的第0个元素, 也就是a[0])的首地址(首地址就是起始地址, 就是4个
			   字节中最开始第一个字节的地址). a做右值等同于&a[0];
			   
		2) a[0]表示数组的首元素, 也就是数组的第0个元素. 做左值时表示数组第0个元素对应的内存空间(连续
		   4字节); 做右值时表示数组第0个元素的值(也就是数组第0个元素对应的内存空间中存储的那个数).
		
		3) &a就是数组名a取地址, 字面意思来看就应该是数组的地址. &a不能做左值(&a实质是一个常量,不是变
		   量因此不能赋值, 所以自然不能做左值); &a做右值时表示整个数组的首地址.
		   
		4) &a[0]字面意思就是数组第0个元素的首地址(搞清楚[]和&的优先级, []的优先级要高于&, 所以a先和
		   []结合再取地址), 做右值时&a[0]等同于a.

	解释：为什么数组的地址是常量? 因为数组是编译器在内存中自动分配的. 当我们每次执行程序时, 运行时都
	      会帮我们分配一块内存给这个数组, 只要完成了分配, 这个数组的地址就定好了, 本次程序运行直到终
		  止都无法再改了. 那么我们在程序中只能通过&a来获取这个分配的地址, 却不能去用赋值运算符修改它.

	总结：
		1：&a和a做右值时的区别：&a是整个数组的首地址, 而a是数组首元素的首地址. 这两个在数字上是相等
		   的, 但是意义不相同. 意义不相同会导致他们在参与运算的时候有不同的表现(!!!!!!!).
		   (!!!!!*****!!!!! &a是数组指针, 是int (*)[n]类型, 见下一节!!!!!*****!!!!! )
		2：a和&a[0]做右值时意义和数值完全相同, 完全可以互相替代.
		3：&a是常量, 不能做左值.
		4：a做左值代表整个数组所有空间, 所以a不能做左值.
		
	测试:
	
		int a[4];			// 一次定义一个数组，包含4个int型变量
		printf("a = %p, &a = %p, &a[0] = %p", a, &a, &a[0]);
		
		a = 0xbfed8ba0, &a = 0xbfed8ba0, &a[0] = 0xbfed8ba0

//=======================================================================================================
									4.3.6.指针与数组的天生姻缘
//-------------------------------------------------------------------------------------------------------
	1 以指针方式来访问数组元素
	
		1) 数组元素使用时不能整体访问, 只能单个访问. 访问方式有2种：数组形式和指针形式.
		2) 数组格式访问数组元素是：数组名[下标]; (注意下标从0开始).
		3) 指针格式访问数组元素是：*(指针+偏移量); 如果指针是数组首元素地址(a或者&a[0]), 那么偏移量
		   就是下标; 指针也可以不是首元素地址而是其他哪个元素的地址, 这时候偏移量就要考虑叠加了.
		4) 数组下标方式和指针方式均可以访问数组元素, 两者的实质其实是一样的. 在编译器内部都是用指针
		   方式来访问数组元素的, 数组下标方式只是编译器提供给编程者一种壳(语法糖)而已. 所以用指针方
		   式来访问数组才是本质的做法.
		   
		测试:
			1)
				int a[5] = {1, 2, 3, 4, 5};

				printf("a[3] = %d.\n", a[3]);
				printf("*(a+3) = %d.\n", *(a+3));
			2) 
				int *p;
				p = a;								// a做右值表示数组首元素首地址，等同于&a[0]
				printf("*(p+3) = %d.\n", *(p+3));	// 等同于a[3]


	2. 从内存角度理解指针访问数组的实质
	
		1) 数组的特点就是：数组中各个元素的地址是依次相连的, 而且数组还有一个很大的特点(其实也是
		   数组的一个限制)就是数组中各个元素的类型比较相同. 类型相同就决定了每个数组元素占几个字节是
		   相同的.
		2) 数组中的元素其实就是地址相连接、占地大小相同的一串内存空间. 这两个特点就决定了只要知道数
		   组中一个元素的地址, 就可以很容易推算出其他元素的地址.

	3. 指针和数组类型的匹配问题
	
		1) int *p; int a[5];	p = a;		// 类型匹配
		2) int *p; int a[5];	p = &a;		// 类型不匹配. p是int *, &a是整个数组的指针, 也就是一个
		                                    // 数组指针类型, 不是int指针类型, 所以不匹配.
		3) &a、a、&a[0]从数值上来看是完全相等的, 但是意义来看就不同了. 
			a) 从意义上来看, a和&a[0]是数组首元素首地址, 而&a是整个数组的首地址.
			b) 从类型来看, a和&a[0]是元素的指针, 也就是int *类型; 而&a是数组指针, 是int (*)[5];类型.
			
		总结: &a是数组指针, 是int (*)[n]类型.

	4. 总结：指针类型决定了指针如何参与运算
	
		1) 指针参与运算时, 因为指针变量本身存储的数值是表示地址的, 所以运算也是地址的运算.
		2) 指针参与运算的特点是, 指针变量+1, 并不是真的加1, 而是加1*sizeof(指针类型); 
			   如果是int *指针, 则+1就实际表示地址+4.
			   如果是char *指针, 则+1就表示地址+1.
			   如果是double *指针, 则+1就表示地址+8.
		3) 指针变量+1时实际不是加1而是加1×sizeof(指针类型), 主要原因是希望指针+1后刚好指向下一个元素.

	测试:
			int a[5] = {1, 2, 3, 4, 5};
			int *p;
			p = a;
			
			printf("*(p+1) = %d.\n", *(p+1));
			printf("*(p+1) = %d.\n", *((char *)p+1));
			printf("*(p+1) = %d.\n", *(int *)((unsigned int)p+1));
			
			char *p2;
			p2 = (char *)p;
			printf("*(p+1) = %d.\n", *(p2+1));

		结果: 2,0,33554432,0
			1) *((char *)p+1): p转化为char类型的指针, 所以最后解引用后是第二个内存单元的数值0, 然后
			   按照int类型(%d)打印得到.
			2)  *(int *)((unsigned int)p+1) p强制转化为uint类型, 加1之后. 强制转化为int *类型. 
			   也就是把第二个字节开始的四个字节的数值,作为一个int *型的指针:
			   这个指针对应的地址为首地址的int类型的数据, 33554432.
//=======================================================================================================
									4.3.7.指针与强制类型转换
//-------------------------------------------------------------------------------------------------------
	1. 变量的数据类型的含义
		1) 所有的类型的数据存储在内存中, 都是按照二进制格式存储的. 所以内存中只知道有0和1, 不知道是
		   int的、还是float的还是其他类型.
		2) int、char、short等属于整形, 他们的存储方式(数转换成二进制往内存中放的方式)是相同的, 只是
		   内存格子大小不同(所以这几种整形就彼此叫二进制兼容格式); 而float和double的存储方式彼此不同,
		   和整形更不同.
		3) int a = 5;时, 编译器给a分配4字节空间, 并且将5按照int类型的存储方式转成二进制存到a所对应的
		   内存空间中去(a做左值的); 我们printf去打印a的时候(a此时做右值), printf内部的vsprintf函数会
		   按照格式化字符串(就是printf传参的第一个字符串参数中的%d之类的东西)所代表的类型去解析a所对
		   应的内存空间, 解析出的值用来输出. 也就是说, 存进去时是按照这个变量本身的数据类型来存储的
		   (譬如本例中a为int所以按照int格式来存储); 但是取出来时是按照printf中%d之类的格式化字符串的
		   格式来提取的. 此时虽然a所代表的内存空间中的10101序列并没有变(内存是没被修改的)但是怎么理
		   解(怎么把这些1010转成数字)就不一定了. 譬如我们用%d来解析, 那么还是按照int格式解析则值自然
		   还是5; 但是如果用%f来解析, 则printf就以为a对应的内存空间中存储的是一个float类型的数, 会按
		   照float类型来解析, 会是以他的一个数值.

		总结：C语言中的数据类型的本质, 就是决定了这个数在内存中怎么存储的问题, 也就是决定了这个数如何
		      转成二进制的问题. 一定要记住的一点是内存只是存储1010的序列, 而不管这些1010怎么解析. 所以
			  要求我们平时数据类型不能瞎胡乱搞.
		
		分析几个题目：
		* 按照int类型存却按照float类型取	一定会出错
		* 按照int类型存却按照char类型取		有可能出错也有可能不出错
		* 按照short类型存却按照int类型取	有可能出错也有可能不出错
		* 按照float类型存却按照double取		一定会出错

	2. 指针的数据类型的含义
		
		1) 指针的本质是：变量, 指针就是指针变量.
		
		2) 一个指针涉及2个变量：一个是指针变量自己本身, 一个是指针变量指向的那个变量. (!!!!)
		
		3) int *p; 定义指针变量时, p(指针变量本身)是(int *)类型, *p(指针指向的那个变量)是int类型的.
		
		4) (int *) 类型说白了就是指针类型, 只要是指针类型就都是占4字节, 解析方式都是按照地址的方式来
		   解析(意思是里面存的32个二进制加起来表示一个内存地址)的. 结论就是：所有的指针类型(不管是
		   int * 还是char * 还是double *)的解析方式是相同的, 都是地址.
		   
		5) 对于指针所指向的那个变量来说, 指针的类型就很重要了. 指针所指向的那个变量的类型(它所对应的
		   内存空间的解析方法)要取决于指针类型. 譬如指针是int *的, 那么指针所指向的变量就是int类型的.

	3. 指针数据类型转换实例分析1 (int * -> char *)
		1) int和char类型都是整形, 类型兼容的. 所以互转的时候有时候错有时候对.
		2) int和char的不同在于char只有1个字节而int有4个字节, 所以int的范围比char大. 在char所表示的范
		   围之内int和char是可以互转的不会出错; 但是超过了char的范围后char转成int不会错, 而从int到
		   char转就会出错.

	4. 指针数据类型转换实例分析2 (int * -> float *)
		1) 之前分析过：int和float的解析方式是不兼容的, 所以int *转成float *再去访问绝对会出错.

//=======================================================================================================
								4.3.8.指针、数组与sizeof运算符
//-------------------------------------------------------------------------------------------------------
	1. sizeof运算符
		1) sizeof是C语言的一个运算符(主要sizeof不是函数,虽然用法很像函数), sizeof的作用是用来返回()
		   里面的 "变量" 或者 "数据类型" 占用的内存字节数.
		2) sizeof存在的价值?
			主要是因为在不同平台下各种数据类型所占的内存字节数不尽相同(譬如int在32位系统中为4字节,
			在16位系统中为2字节···). 所以程序中需要使用sizeof来判断当前"变量"/"数据类型"在当前环境下
			占几个字节.

	2. sizeof实验测试
		1) char str[] = ”hello”;  
		   sizeof(str)	sizeof(str[0])	 strlen(str)  // 6, 1, 5

			(!!!!!) sizeof(字符串)	// 包含'\n'.
			        strlen(字符串)	// 不包含'\n'
		2) char str[] = ”hello”; 
		   char *p=str;  			
		   sizeof(p)	sizeof(*p)	strlen(p)		  // 4, 1, 5
		   
		   (!!!!!)  sizeof(指针), 32位系统里面, 一定是4. 
					strlen()是一个返回字符串长度的函数, 接收的函数一定一个字符串, 一直找到'\0', 才
		            返回长度,长度不包含'\0'.
				   
		3) int n=10; 				
		   sizeof(n)								// 4
		   sizeof(int)								// 4
		   
		   (!!!!!) sizeof测试一个变量本身, 和sizeof测试这个变量的类型, 结果是一样的.
		           同理,也适用于结构体. sizeof(结构体类型) 和 sizeof(结构体变量) 是一样的.
				   
		4) int b[100];			
		   sizeof(b)								// 400
		   
		   (!!!!!) sizeof(数组名)的时候, 数组名不做左值也不做右值, 纯粹就是数组名的含义. 那么
		           sizeof(数组名)实际返回的是整个数组所占用内存空间(以字节为单位的).
		5) 
			void func(int a[])
			{
				printf("数组大小 = %d.\n", sizeof(a));
			}

			void func1(int *a)
			{
				printf("数组大小 = %d.\n", sizeof(a));
			}
			
			int a[20];
			func(a);			// 4 因为a在函数func内部就是指针,而不是数组.
			func1(a);			// 4 

			a) 函数传参, 形参是可以用数组的.
			
			b) 函数形参是数组时, 实际传递是不是整个数组, 而是数组的首元素首地址. 也就是说函数传参
			   用数组来传, 实际相当于传递的是指针(指针指向数组的首元素首地址).	


		总结: (!!!!!)
			1) 
				void func(int a[100])
				{
					printf("数组大小 = %d.\n", sizeof(a));
				}
				这样写函数的形参, 也可以. 编译器不报错, 但是好像数组的大小不起任何作用:
				参考下一节的3.3.
			2) 	
				void func(int a[100])
				{
					printf("a = %p, a +1 = %p. \n", a,a+1);		// 两个值相差4 , 不是400
					
				}

	3. typedef 和#define 定义变量
	
		1) #define  dpChar  char *
		
			dpChar p1,  p2;			sizeof(p1)	sizeof(p2)		// 4 ,1 

			(!!!!) p2 不是一个指针.
			
		2) typedef  char *  tpChar;

			tpChar p3,  p4;			sizeof(p3)	sizeof(p4)		// 4, 4

			(!!!!!) 这里时一个新的数据类型 (char *)
			
	4. sizeof 用于结构体, 涉及到对齐等等, 后续讲解.

//=======================================================================================================
									4.3.9.指针与函数传参
//-------------------------------------------------------------------------------------------------------
	1. 函数传参

		1) 普通变量作为函数形参
		2) 数组作为函数形参
		3) 指针作为函数形参
		4) 结构体变量作为函数形参
  		
	2. 普通变量作为函数形参
		1) 函数传参时, 普通变量作为参数时, 形参和实参名字可以相同也可以不同, 实际上都是用实参来替代
		   相对应的形参的.
		2) 在子函数内部, 形参的值等于实参. 原因是函数调用时把实参的值赋值给了形参. 
		3) 这就是很多书上写的“传值调用”(相当于实参做右值, 形参做左值).

	3. 数组作为函数形参
		1) 函数名作为形参传参时, 实际传递是不是整个数组, 而是数组的首元素的首地址(也就是整个数组的首
		   地址. 因为传参时是传值, 所以这两个没区别). 所以在子函数内部, 传进来的数组名就等于是一个指
		   向数组首元素首地址的指针. 所以sizeof得到的是4.
		2) 在子函数内传参得到的数组首元素首地址, 和外面得到的数组首元素首地址的值是相同的.很多人把这
		   种特性叫做“传址调用”(所谓的传址调用就是调用子函数时传了地址(也就是指针), 此时可以通过传进
		   去的地址来访问实参).
		   
			void func2(int a[])
			{
				printf("sizeof(a) = %d.\n", sizeof(a));		
				printf("in func2, a = %p.\n", a);				// 地址与main的相同.
			}
				
		   	int a[5];
			printf("a = %p.\n", a);								// 地址与子函数的相同.
			func2(a);

		   
		3) 数组作为函数形参时, []里的数字是可有可无的. 为什么? 因为数组名做形参传递的实际只是个指针,
		   根本没有数组长度这个信息.

	4. 指针作为函数形参
	
		和数组作为函数形参是一样的. 这就好像指针方式访问数组元素和数组方式访问数组元素的结果一样.

	5. 结构体变量作为函数形参
	
		1) 结构体变量作为函数形参的时候, 实际上和普通变量(类似于int之类的)传参时表现是一模一样的.
		   所以说结构体变量其实也是普通变量而已.
		   
		2) 因为结构体一般都很大, 所以如果直接用结构体变量进行传参, 那么函数调用效率就会很低. (因为
		   在函数传参的时候需要将实参赋值给形参, 所以当传参的变量越大调用效率就会越低). 怎么解决?
		   思路只有一个那就是不要传变量了, 改传变量的指针(地址)进去.
		   
		3) 结构体因为自身太大, 所以传参应该用指针来传(但是程序员可以自己决定, 你非要传结构体变量过
		   去C语言也是允许的, 只是效率低了); 回想一下数组, 为什么C语言设计的时候数组传参默认是传的
		   数组首元素首地址而不是整个数组?

	6. 传值调用与传址调用
	
		void swap1(int a, int b)
		{
			int tmp;
			tmp = a;
			a = b;
			b = tmp;
			printf("in swap1, a = %d, b = %d.\n", a, b);
		}

		void swap2(int *a, int *b)
		{
			int tmp;
			tmp = *a;
			*a = *b;
			*b = tmp;
			printf("in swap1, *a = %d, *b = %d.\n", *a, *b);
		}
		
		1) 传值调用描述的是这样一种现象：x和y作为实参, 自己并没有真身进入swap1函数内部, 而只是拷贝
		   了一份自己的副本(副本具有和自己一样的值, 但是是不同的变量)进入子函数swap1, 然后我们在子
		   函数swap1中交换的实际是副本而不是x、y真身. 所以在swap1内部确实是交换了, 但是到外部的x和
		   y根本没有受影响.

		2) 在swap2中x和y真的被改变了. 在swap2我们把x和y的地址传进去给子函数了, 于是乎在子函数内可以
		   通过指针解引用方式从函数内部访问到外部的x和y真身, 从而改变x和y.
		   
		结论：这个世界上根本没有传值和传址这两种方式, C语言本身函数调用时一直是传值的, 只不过传的值
		      可以是变量名, 也可以是变量的指针.

//=======================================================================================================
								4.3.10.输入型参数与输出型参数
//-------------------------------------------------------------------------------------------------------
4.3.10.输入型参数与输出型参数

	1. 函数为什么需要形参与返回值
	
		1) 函数名是一个符号, 表示整个函数代码段的首地址, 实质是一个指针常量, 所以在程序中使用到函数
		   名时都是当地址用的, 用来调用这个函数的.
		   
		2) 函数体是函数的关键, 由一对{}括起来, 包含很多句代码, 函数体就是函数实际做的工作.
		
		3) 形参列表和返回值. 形参是函数的输入部分, 返回值是函数的输出部分.
		
		4) 如果没有形参列表和返回值, 函数也能对数据进行加工, 用全局变量即可. 
			用全局变量来传参和用函数参数列表返回值来传参各有特点, 在实践中都有使用. 
			总的来说, 函数参数传参用的比较多, 因为这样可以实现模块化编程, 而C语言中也是尽量减少使用
			全局变量.
			
		5) 全局变量传参最大的好处就是省略了函数传参的开销, 所以效率要高一些; 但是实战中用的最多的还
		   是传参, 如果参数很多传参开销非常大, 通常的做法是把很多参数打包成一个结构体, 然后传结构体
		   变量指针进去.

	2. 函数传参中使用const指针
	
		1) const一般用在函数参数列表中, 用法是const int *p; (意义是指针变量p本身可变的, 而p所指向的
		   变量是不可变的).
		   
		2) const用来修饰指针做函数传参, 作用就在于声明在函数内部不会改变这个指针所指向的内容, 所以
		   给该函数传一个不可改变的指针(char *p = "linux";这种), 有可能会触发一个段错误(当函数修改
		   了指针指向的内容时); 
		   
		3) 实验:
			a) 报段错误. 原因就是 "linux" 放置在代码段的, 不可以写, 如果调用了func3(),会报错.
				void func3(char *p)
				{
					*p = 'a';
				}
						
				char *pStr = "linux";				// 
				func3(pStr);
				printf("%s.\n", pStr);
				
			b) 换成数组, 则正常.
			    char pStr[] = "linux";			// ok的

	3. 函数需要向外部返回多个值时怎么办?
	
		1) 一般来说, 函数的收入部分就是函数参数, 输出部分就是返回值. 问题是函数的参数可以有很多个,
		   而返回值只能有1个. 这就造成我们无法让一个函数返回多个值.
		   
		2) 现实编程中, 一个函数需要返回多个值是非常普遍的, 通常的做法是用参数来做返回(在典型的linux
		   风格函数中, 返回值是不用来返回结果的, 而是用来返回0或者负数用来表示程序执行结果是对还是
		   错, 是成功还是失败).
		   
		3) 普遍做法, 编程中函数的输入和输出都是靠函数参数的, 返回值只是用来表示函数执行的结果是对
		   (成功)还是错(失败). 如果这个参数是用来做输入的, 就叫输入型参数; 如果这个参数的目的是用
		   来做输出的, 就叫输出型参数.
		   
		4) 输出型参数就是用来让函数内部把数据输出到函数外部的.

	总结: 
		看到一个函数的原型后, 怎么样一眼看出来哪个参数做输入哪个做输出?
		
		1) 函数传参如果传的是普通变量(不是指针)那肯定是输入型参数.
		
		2) 如果传指针就有2种可能性了. 为了区别, 经常的做法是: 
		
			a) 如果这个参数是做输入的(通常做输入的在函数内部只需要读取这个参数而不会需要更改它)就在
			   指针前面加const来修饰.
			   
			b) 如果函数形参是指针变量并且还没加const, 那么就表示这个参数是用来做输出型参数的.
		
			譬如C库函数中strcpy函数.

//=======================================================================================================








