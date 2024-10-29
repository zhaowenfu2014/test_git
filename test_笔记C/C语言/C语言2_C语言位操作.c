/*
//=======================================================================================================
										4.2.C语言位操作
//=======================================================================================================
4.2.1.常用位操作符
4.2.2.位与位或位异或在操作寄存器时的特殊作用
4.2.3.如何用位运算构建特定二进制数
4.2.4.位运算实战演练1
4.2.5.位运算实战演练2
4.2.6.技术升级：用宏定义来完成位运算
//=======================================================================================================
									4.2.1.常用位操作符
//-------------------------------------------------------------------------------------------------------
	1. C语言常用的位操作符
	
		位与&
		位或|
		位取反~
		位异或^
		左移位<< 与右移位>>
		
	2. 位与&
	
		1) 注意：位与符号是一个&，两个&&是逻辑与.
		2) 真值表：1&0=0	1&1=1	0&0=0	0&1=0.	
		3) 位与和逻辑与的区别：位与时两个操作数是按照二进制位彼次对应位相与的, 逻辑与是两个操作数
		   作为整体来相与的. (举例：0xAA&0xF0=0xA0,	0xAA && 0xF0=1)
		   
	3. 位或|
	
		1) 注意：位或符号是一个|, 两个||是逻辑或.
		2) 真值表：1|0=1	1|1=1	0|0=0	0|1=1
		3) 位或和逻辑或的区别：位或时两个操作数是按照二进制位彼次对应位相与的, 逻辑或是两个操作数作
		   为整体来相或的.
		   
	4. 位取反~
	
		1) 注意：C语言中位取反是~, C语言中的逻辑取反是!
		2) 按位取反是将操作数的二进制位逐个按位取反(1变成0,0变成1); 而逻辑取反是真(在C语言中只要不
		   是0的任何数都是真)变成假(在C语言中只有0表示假)、假变成真.

		实验：任何非0的数被按逻辑取反再取反就会得到1;
			  任何非0的数被按位取反再取反就会得到他自己;

	5. 位异或^
	
		1) 位异或真值表：1^1=0 	0^0=0	1^0=1	0^1=1	
		2) 位异或的特点：2个数如果相等结果为0, 不等结果为1. 记忆方法：异或就是相异就或操作起来. 

	6. 左移位<< 与右移位>>
	
		C语言的移位要取决于数据类型:

		1) 对于无符号数, 左移时右侧补0(相当于逻辑移位)
		2) 对于无符号数, 右移时左侧补0(相当于逻辑移位)
		3) 对于有符号数, 左移时右侧补0(叫算术移位, 相当于逻辑移位)
		4) 对于有符号数, 右移时左侧补符号位(如果正数就补0, 负数就补1, 叫算术移位)

		嵌入式中研究的移位, 以及使用的移位都是无符号数.
		
	总结:
			位与、位或、位异或的特点总结：
			1) 位与:   (任何数, 其实就是1或者0)与1位与无变化, 与0位与变成0
			2) 位或：  (任何数, 其实就是1或者0)与1位或变成1, 与0位或无变化.
			3) 位异或：(任何数，其实就是1或者0)与1位异或会取反, 与0位异或无变化.
	
	实验:
		unsigned int a = 45;
		unsigned int b, c;
		b = ~a;								// 按位取反，逐个位操作，1变0，0变1
		c = !a;								// 按逻辑取反，真变假，假变真
		printf("b = %u.\n", b);
		printf("c = %d.\n", c);

		1) printf("b = %d.\n", b);			// 打印出来是-46
		2) printf("b = %u.\n", b);  		// 打印出来是4294967250
		3) printf("a & b = 0x%x.\n", c);	// 十六进制打印用%x
		
		存储的内容不变, 打印时候解析格式不同, 数值不同.

//=======================================================================================================
							4.2.2.位与位或位异或在操作寄存器时的特殊作用
//-------------------------------------------------------------------------------------------------------
	1. 寄存器操作的要求(特定位改变而不影响其他位)
	
		1) ARM是内存与IO统一编址的, ARM中有很多内部外设, SoC中CPU通过向这些内部外设的寄存器写入一些
		   特定的值来操控这个内部外设, 进而操控硬件动作. 所以可以说：读写寄存器就是操控硬件.
		2) 寄存器的特点是按位进行规划和使用. 但是寄存器的读写却是整体32位一起进行的(也就是说你只想修
		   改bit5～bit7是不行的, 必须整体32bit全部写入).
		3) 寄存器操作要求就是：在设定特定位时不能影响其他位.
		4) 如何做到? 答案是：读-改-写三部曲. 

	2. 特定位清零用&
		1) 回顾上节讲的位与操作的特点：任何数(其实就是1或者0)与1位与无变化, 与0位与变成0.
		2) 如果希望将一个寄存器的某些特定位变成0而不影响其他位, 可以构造一个合适的1和0组成的数和这个
		   寄存器原来的值进行位与操作, 就可以将特定位清零.
		3) 举例：假设原来32位寄存器中的值为: 0xAAAAAAAA, 我们希望将bit8～bit15清零而其他位不变, 可以
		   将这个数与0xFFFF00FF进行位与即可.

	3. 特定位置1用|
		1) 回顾上节讲的位或操作的特点：任何数(其实就是1或者0)与1位或变成1, 与0位或无变化.
		2) 操作手法和刚才讲的位与是类似的. 我们要构造这样一个数：要置1的特定位为1, 其他位为0, 然后将
		   这个数与原来的数进行位或即可. 

	4. 特定位取反用^
		1) 回顾上节讲的位异或操作的特点：任何数(其实就是1或者0)与1位异或会取反, 与0位异或无变化.
		2) 操作手法和刚才讲的位与是类似的. 我们要构造这样一个数：要取反的特定位为1, 其他位为0, 然后将
		   这个数与原来的数进行位异或即可.

//=======================================================================================================
								4.2.3.如何用位运算构建特定二进制数
//-------------------------------------------------------------------------------------------------------
	1. 寄存器位操作经常需要特定位给特定值
		1) 从上节可知, 对寄存器特定位进行置1或者清0或者取反, 关键性的难点在于要事先构建一个特别的数,
		   这个数和原来的值进行位与、位或、位异或等操作, 即可达到我们对寄存器操作的要求.
		2) 解法1：用工具软件或者计算器或者自己大脑计算, 直接给出完整的32位特定数.
		3) 解法2：自己写代码用位操作符号(主要是移位和位取反)来构建这个特定的二进制数.

	2. 使用移位获取特定位为1的二进制数
		1) 最简单的就是用移位来获取一个特定位为1的二进制数. 譬如我们需要一个bit3～bit7为1(隐含意思就
		   是其他位全部为0)的二进制数, 可以这样：(0x1f<<3)
		2) 更难一点的要求：获取bit3～bit7为1，同时bit23～bit25为1, 其余位为0的数：((0x1f<<3) | (7<<23)).

	3. 再结合位取反获取特定位为0的二进制数
		1) 这次我们要获取bit4～bit10为0, 其余位全部为1的数. 怎么做?
		2) 利用上面讲的方法就可以：(0xf<<0)|(0x1fffff<<11)
			但是问题是：连续为1的位数太多了, 这个数字本身就很难构造, 所以这种方法的优势损失掉了.
		3) 这种特定位(比较少)为0而其余位(大部分)为1的数, 不适合用很多个连续1左移的方式来构造, 适合左移
		   加位取反的方式来构造.
		4) 思路是：先试图构造出这个数的位相反数, 再取反得到这个数. (譬如本例中要构造的数bit4～bit10为0
		   其余位为1, 那我们就先构造一个bit4～bit10为1, 其余位为0的数, 然后对这个数按位取反即可)

	总结：位与、位或结合特定二进制数即可完成寄存器位操作需求
		1) 如果你要的这个数比较少位为1, 大部分位为0, 则可以通过连续很多个1左移n位得到.
		2) 如果你想要的数是比较少位为0, 大部分位为1, 则可以通过先构建其位反数, 然后再位取反来得到. 
		3) 如果你想要的数中连续1(连续0)的部分不止1个, 那么可以通过多段分别构造, 然后再彼此位或即可.
		   这时候因为参与位或运算的各个数为1的位是不重复的, 所以这时候的位或其实相当于几个数的叠加.

//=======================================================================================================
									4.2.4-5.位运算实战演练1,2
//-------------------------------------------------------------------------------------------------------
	1. 给定一个整型数a, 设置a的bit3, 保证其他位不变.
		a = a | (1<<3)		或者 a |= (1<<3)
	2. 给定一个整形数a, 设置a的bit3~bit7, 保持其他位不变.
		a = a | (0b11111<<3)	或者 a |= (0x1f<<3);
	3. 给定一个整型数a, 清除a的bit15, 保证其他位不变.
		a = a & (~(1<<15));		或者 a &= (~(1<<15));
	4. 给定一个整形数a，清除a的bit15~bit23，保持其他位不变。
		a = a & (~(0x1ff<<15));		或者 a &= (~(0x1ff<<15));
	5. 给定一个整形数a, 取出a的bit3~bit8.
		第一步, 先将这个数bit3～bit8不变, 其余位全部清零.
		第二步, 再将其右移3位得到结果.
		第三步, 想明白了上面的2步算法, 再将其转为C语言实现即可:
			a &= (0x3f<<3);
			a >>= 3;

	6. 用C语言给一个寄存器的bit7～bit17赋值937(其余位不受影响)
		关键点：第一, 不能影响其他位; 第二, 你并不知道原来bit7～bit17中装的值.
		思路：  
			第一步, 先将bit7～bit17全部清零, 当然不能影响其他位.
				a &= ~(0x7ff<<7);
			第二步, 再将937写入bit7～bit17即可, 当然不能影响其他位.
				a |= (937<<7);


	7. 用C语言将一个寄存器的bit7～bit17中的值加17(其余位不受影响).
		关键点：不知道原来的值是多少
		思路：
			第一步, 先读出原来bit7～bit17的值.
				tmp = a & (0x3ff<<7);
				tmp >>= 7;			
			第二步, 给这个值加17.
				tmp += 17;
			第三步, 将bit7～bit17清零.
				a &= ~(0x3ff<<7);
			第四步, 将第二步算出来的值写入bit7～bit17.
				a |= tmp<<7;

//=======================================================================================================
								4.2.6.技术升级：用宏定义来完成位运算
//-------------------------------------------------------------------------------------------------------
	1. 直接用宏来置位、复位(最右边为第1位) 

		#define SET_NTH_BIT(x, n)  	(x | ((1U)<<(n-1)))
		
		#define CLEAR_NTH_BIT(x, n) (x & ~((1U)<<(n-1)))
		
		1) 要写为(1U).
		2) 最外层需要加一个().
	
	2. 截取变量的部分连续位. 例如：变量0x88, 也就是10001000b, 若截取第2～4位, 则值为：100b = 4
	
		#define GETBITS(x, n, m) 	(  (  x & ~(~(0U)<<(m-n+1))  <<  (n-1)  )  >>   (n-1)   ) 
	
		((x & ~(~(0U)<<(m-n+1))<<(n-1)) >> (n-1))
		第一步，先分清楚这个复杂宏分为几部分：2部分
		(x & ~(~(0U)<<(m-n+1))<<(n-1)) 			>> 			(n-1)
		分析为什么要>>(n-1)，相当于是我们4.2.4.5中的第二步

		第二步，继续解析剩下的：又分为2部分
		x 		& 		~(~(0U)<<(m-n+1))<<(n-1) 		
		分析为什么要&，相当于我们4.2.4.5中的第一步	

		第三步，继续分析剩下的：
		~		(~(0U)<<(m-n+1))		<<		(n-1) 
		这个分析时要搞清楚第2坨到底应该先左边取反再右边<<还是先右边<<再左边取反。
		解法：第一，查C语言优先级表；第二，自己实际写个代码测试。
		说明这个式子应该是	~(~(0U)<<(m-n+1))		<<		(n-1) ，这就又分为2部分了

	
		总结 : 	1) (!!!! 取反的优先级比左右移优先级高)
				2) 第二步, 是不是少一个括号?

//=======================================================================================================

