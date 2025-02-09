/*
//=======================================================================================================
								4.9.链表&状态机与多线程
//=======================================================================================================
4.9.1.链表的引入
4.9.2.单链表的实现
4.9.3.单链表的算法之插入节点
4.9.4.单链表的算法之插入节点续
4.9.5.从链表头部插入新节点
4.9.6.单链表的算法之遍历节点
4.9.7.单链表的算法之删除节点
4.9.8.单链表的算法之逆序
4.9.9.双链表的引入和基本实现
4.9.10.双链表的算法之插入节点
4.9.11.双链表的算法之遍历节点
4.9.12.双链表的算法之删除节点
4.9.13.linux内核链表
4.9.14.内核链表的基本算法和使用简介	
4.9.15.什么是状态机
4.9.16.C语言实现简单的状态机
4.9.17.多线程简介
//=======================================================================================================
									4.9.1.链表的引入
//-------------------------------------------------------------------------------------------------------
	1. 从数组的缺陷说起
	
		1) 数组有2个缺陷: 一个是数组中所有元素的类型必须一致; 第二个是数组的元素个数必须事先制定并且
		   一旦指定之后不能更改.
		2) 如何解决数组的2个缺陷：数组的第一个缺陷靠结构体去解决. 结构体允许其中的元素的类型不相同. 
		   因此解决了数组的第一个缺陷. 所以说结构体是因为数组不能解决某些问题所以才发明的.
		3) 如何解决数组的第二个缺陷? 我们希望数组的大小能够实时扩展. 譬如我刚开始定了一个元素个数是
		   10, 后来程序运行时觉得不够因此动态扩展为20. 普通的数组显然不行, 我们可以对数组进行封装以
		   达到这种目的; 我们还可以使用一个新的数据结构来解决, 这个新的数据结构就是链表.
		   
		总结：几乎可以这样理解: 链表就是一个元素个数可以实时变大/变小的数组.

	2. 链表是什么样的?
	
		1) 顾名思义, 链表就是用锁链连接起来的表. 这里的表指的是一个一个的节点, 节点中有一些内存可以
		   用来存储数据(所以叫表, 表就是数据表); 这里的锁链指的是链接各个表的方法, C语言中用来连接2
		   个表(其实就是2块内存)的方法就是指针.
		   
		2) 链表是由若干个节点组成的(链表的各个节点结构是完全类似的), 节点是由有效数据和指针组成的.有
		   效数据区域用来存储信息完成任务的, 指针区域用于指向链表的下一个节点从而构成链表.

	3. 时刻别忘了链表是用来干嘛的
	
		1) 时刻谨记：链表就是用来解决数组的大小不能动态扩展的问题, 所以链表其实就是当数组用的. 
		   直白点：链表能完成的任务用数组也能完成, 数组能完成的任务用链表也能完成. 但是灵活性不一样.
		2) 简单说：链表就是用来存储数据的. 链表用来存数据相对于数组来说优点就是灵活性, 需要多少个动
		   态分配多少个, 不占用额外的内存. 数组的优势是使用简单(简单粗暴).

//=======================================================================================================
									4.9.2.单链表的实现
//-------------------------------------------------------------------------------------------------------
	1. 单链表的节点构成
	
		1) 链表是由节点组成的, 节点中包含: 有"效数据"和"指针".
	
		2) 定义的struct node只是一个结构体, 本身并没有变量生成, 也不占内存. 结构体定义相当于为链表节点
		   定义了一个模板, 但还没有一个节点, 将来在实际创建链表时需要一个节点时用这个模板复制一个即可.

	2. 堆内存的申请和使用
	
		1) 链表的内存要求比较灵活, 不能用栈, 也不能用data数据段, 只能用堆内存.
			a) 不能用栈, 因为链表的节点会随时删除,申请. 而栈是先进后出的.
			b) 不能用data数据段, 因为数据段在程序加载的时候就定了, 程序一开始就分配了空间, 程序结束前
			   不能释放.
	
		2) 使用堆内存来创建一个链表节点的步骤：
			a) 申请堆内存, 大小为一个节点的大小(检查申请结果是否正确);
			b) 清理申请到的堆内存; 
			c) 把申请到的堆内存当作一个新节点;
			d) 填充新节点的有效数据和指针区域.
		
			// 每创建一个新的节点，把这个新的节点和它前一个节点关联起来
			// 创建一个链表节点
			struct node *p = (struct node *)malloc(sizeof(struct node));
			if (NULL == p)
			{
				printf("malloc error.\n");
				return -1;
			}
			// 清理申请到的堆内存
			bzero(p, sizeof(struct node));		// 等效于memeset();
			// 填充节点
			p->data = 1;
			p->pNext = NULL;			// 将来要指向下一个节点的首地址


	3. 链表的头指针
	
		1) 头指针并不是节点, 而是一个普通指针, 只占4字节. 头指针的类型是struct node *类型的, 所以它
		   才能指向链表的节点.
		   
		2) 一个典型的链表的实现就是: 头指针指向链表的第1个节点, 然后第1个节点中的指针指向下一个节点,
		   然后依次类推一直到最后一个节点. 这样就构成了一个链.

	4. 实战：构建一个简单的单链表
	
		1) 目标：构建一个链表, 然后将一些数据(譬如1, 2, 3三个数字)存储在链表中.
		
		2) 程序:
			
			// 定义头指针
			struct node *pHeader = NULL;
			
			...

	5. 访问链表中各个节点的数据

		1) 只能用头指针, 不能用各个节点自己的指针. 因为在实际当中我们保存链表的时候是不会保存各个节点
		   的指针的, 只能通过头指针来访问链表节点.

		2) 前一个节点内部的pNext指针能帮助我们找到下一个节点.

//=======================================================================================================
									4.9.3.单链表的算法之插入节点
//-------------------------------------------------------------------------------------------------------
	1. 将创建节点的代码封装成一个函数
		
		封装时的关键点就是函数的接口(函数参数和返回值)的设计.

		struct node * create_node(int data)
		{
			struct node *p = (struct node *)malloc(sizeof(struct node));
			if (NULL == p)
			{
				printf("malloc error.\n");
				return NULL;
			}
			// 清理申请到的堆内存
			bzero(p, sizeof(struct node));
			// 填充节点
			p->data = data;
			p->pNext = NULL;	
			
			return p;
		}
	
	2. 从链表头部插入新节点
	
		void insert_head(struct node *pH, struct node *new)
		{
			// 第1步： 新节点的next指向原来的第一个节点
			new->pNext = pH->pNext;
			
			// 第2步： 头节点的next指向新节点的地址
			pH->pNext = new;
			
			// 第3步： 头节点中的计数要加1
			pH->data += 1;
		}
	
	3. 从链表尾部插入新节点
	
		尾部插入简单点, 因为前面已经建立好的链表不用动. 直接动最后一个就可以了.

		void insert_tail(struct node *pH, struct node *new)
		{
			int cnt = 0;
			// 分两步来完成插入
			// 第一步，先找到链表中最后一个节点
			struct node *p = pH;
			while (NULL != p->pNext)
			{
				p = p->pNext;				// 往后走一个节点
				cnt++;
			}
			
			// 第二步，将新节点插入到最后一个节点尾部
			p->pNext = new;
			pH->data = cnt + 1;
		}
	
	4. 创建链表
	
		1) 定义头指针, 创建第一个节点, 地址赋给头指针.
		
		2) 调用插入函数, 添加节点.
		
		struct node *pHeader = create_node(0);
		
		insert_head(pHeader, create_node(1));
		insert_tail(pHeader, create_node(2));
		insert_head(pHeader, create_node(3));

//=======================================================================================================
									4.9.4.单链表的算法之插入节点续
//-------------------------------------------------------------------------------------------------------
	1. 什么是头节点
		
		1)问题：上一节中, 因为我们在insert_tail中直接默认了头指针指向的有一个节点, 因此如果程序中直接
		        定义了头指针后就直接insert_tail就会报段错误. 我们不得不在定义头指针之后先create_node
				创建一个新节点给头指针初始化, 否则不能避免这个错误; 但是这样解决让程序看起来逻辑有点
				不太顺, 因为看起来第一个节点和后面的节点的创建、添加方式有点不同.
				
				(上一节的程序其实已经是头节点的程序了. 这里把数据设置为了链表中的节点数量, 与其他的
				 节点的数据含义不同)
				
			如下例子, 第一个节点和其他的节点的添加方式不同:
			
				struct node *pHeader = create_node(0);
				
				insert_head(pHeader, create_node(1));
				insert_tail(pHeader, create_node(2));
				insert_head(pHeader, create_node(3));
				
		2) 链表还有另外一种用法: 就是把头指针指向的第一个节点作为头节点使用. 
			头节点的特点是：
				第一, 它紧跟在头指针后面.
				第二, 头节点的数据部分是空的(有时候不是空的, 而是存储整个链表的节点数), 指针部分指向
				      下一个节点, 也就是第一个节点.
					  
				(头结点不属于节点)	  
					  
		3) 这样看来, 头节点确实和其他节点不同. 我们在创建一个链表时添加节点的方法也不同. 头节点在创
		   建头指针时一并创建并且和头指针关联起来; 后面的真正的存储数据的节点用节点添加的函数来完成,
		   譬如insert_tail.
		   
		4) 链表有没有头节点是不同的. 体现在链表的插入节点、删除节点、遍历节点、解析链表的各个算法函
		   数都不同. 所以如果一个链表设计的时候就有头节点那么后面的所有算法都应该这样来处理; 如果设
		   计时就没有头节点, 那么后面的所有算法都应该按照没有头节点来做. 实际编程中两种链表都有人用,
		   所以大家在看别人写的代码时一定要注意看它有没有头节点.

	注意: 头指针, 头节点, 第一个节点. 要区分.

//=======================================================================================================
									4.9.5.从链表头部插入新节点
//-------------------------------------------------------------------------------------------------------
	1. 从链表头部插入新节点
	
		1) 注意写代码过程中的箭头符号, 和说话过程中的指针指向. 这是两码事, 容易搞混. 箭头符号实际上
		   是用指针方式来访问结构体, 所以箭头符号的实质是访问结构体中的成员. 更清楚一点说程序中的箭
		   头和链表的连接没有任何关系; 链表中的节点通过指针指向来连接, 编程中表现为一个赋值语句
		   (用=来进行连接), 实质是把后一个节点的首地址, 赋值给前一个节点中的pNext元素做为值.
		   
		2) 链表可以从头部插入, 也可以从尾部插入. 也可以两头插入. 头部插入和尾部插入对链表来说几乎
		   没有差别. 对链表本身无差别, 但是有时候对业务逻辑有差别.

//=======================================================================================================
									4.9.6.单链表的算法之遍历节点
//-------------------------------------------------------------------------------------------------------
	1. 什么是遍历

		1) 遍历就是把单链表中的各个节点挨个拿出来, 就叫遍历.
		2) 遍历的要点：一是不能遗漏、二是不能重复、追求效率.
		
	2. 如何遍历单链表
	
		1) 分析一个数据结构如何遍历, 关键是分析这个数据结构本身的特点. 然后根据本身特点来制定它的遍历
		   算法.
		2) 单链表的特点就是由很多个节点组成, 头指针+头节点为整个链表的起始, 最后一个节点的特征是它内部
		   的pNext指针值为NULL. 从起始到结尾中间由各个节点内部的pNext指针来挂接. 由起始到结尾的路径有
		   且只有一条. 单链表的这些特点就决定了它的遍历算法.
		3) 遍历方法：从头指针+头节点开始, 顺着链表挂接指针依次访问链表的各个节点, 取出这个节点的数据,
		   然后再往下一个节点, 直到最后一个节点, 结束返回.

	3. 编程实战
	
		void bianli2(struct node*pH)
		{
			//pH->data				// 头节点数据，不是链表的常规数据，不要算进去了
			struct node *p = pH;		// 头指针后面是头节点

			printf("-----------开始遍历-----------\n");
			while (NULL != p->pNext)		// 是不是最后一个节点
			{
				p = p->pNext;				// 走到下一个节点，也就是循环增量
				printf("node data: %d.\n", p->data);
			}

			printf("-------------完了-------------\n");
		}

//=======================================================================================================
									4.9.7.单链表的算法之删除节点
//-------------------------------------------------------------------------------------------------------
	1. 为什么要删除节点
	
		1) 一直在强调, 链表到底用来干嘛的? 
		2) 有时候链表节点中的数据不想要了, 因此要删掉这个节点. 对应从列表中取出数据的操作.
		
	2. 删除节点的2个步骤
		
		1) 第一步：找到要删除的节点;
		
			a) 知道要删除节点的序号(第几个节点).
			b) 或者知道要删除节点的内容.
			
		2) 第二步：删除这个节点.
		
	3. 如何找到待删除的节点

		1) 通过遍历来查找节点. 从头指针+头节点开始, 顺着链表依次将各个节点拿出来.
		2) 按照一定的方法比对, 找到我们要删除的那个节点.
		
	4. 如何删除一个节点
	
		1) 待删除的节点不是尾节点的情况: 首先把待删除的节点的前一个节点的pNext指针指向待删除的节点的
		   后一个节点的首地址(这样就把这个节点从链表中摘出来了), 然后再将这个摘出来的节点free掉接口.
		   
		2) 待删除的节点是尾节点的情况：首先把待删除的尾节点的前一个节点的pNext指针指向null(这时候就
		   相当于原来尾节点前面的一个节点变成了新的尾节点), 然后将摘出来的节点free掉.

	5. 注意堆内存的释放
	
		1) 前面几节课我们写的代码最终都没有释放堆内存. 当程序都结束了的情况下那些没有free的堆内存
		   也被释放了.
		   
		2) 有时候我们的程序运行时间很久, 这时候malloc的内存如果没有free会一直被占用直到你free释放它
		   或者整个程序终止.
	
	6. 编程实战
	
		int delete_node(struct node*pH, int data)
		{
			// 找到这个待删除的节点，通过遍历链表来查找
			struct node *p = pH;			// 用来指向当前节点
			struct node *pPrev = NULL;		// 用来指向当前节点的前一个节点

			while (NULL != p->pNext)		// 是不是最后一个节点
			{
				pPrev = p;					// 在p走向下一个节点前先将其保存
				p = p->pNext;				// 走到下一个节点，也就是循环增量
				// 判断这个节点是不是我们要找的那个节点
				if (p->data == data)
				{
					if (NULL == p->pNext)
					{
						// 尾节点
						pPrev->pNext = NULL;		// 原来尾节点的前一个节点变成新尾节点
						free(p);					// 释放原来的尾节点的内存
					}
					else
					{
						// 普通节点
						pPrev->pNext = p->pNext;	// 要删除的节点的前一个节点和它的后一个节点相连
						free(p);
					}
					// 处理完成之后退出程序
					return 0;
				}
			}
			// 到这里还没找到，说明链表中没有我们想要的节点
			printf("没找到这个节点.\n");
			return -1;
		}	

//=======================================================================================================
									4.9.8.单链表的算法之逆序
//-------------------------------------------------------------------------------------------------------
	1. 什么是链表的逆序
		
		链表的逆序又叫反向, 意思就是把链表中所有的有效节点在链表中的顺序给反过来.

	2. 单链表逆序算法分析

		1) 当我们对一个数据结构进行一个操作时, 我们就需要一套算法. 这就是数据结构和算法的关系.
		
		2) 我总结：算法有2个层次. 第一个层次是数学和逻辑上的算法; 第二次个层次是用编程语言来实现算法.
		
		3) 从逻辑上来讲, 链表的逆序有很多种方法. 这些方法都能实现最终的需要, 但是效率是不一样的. 彼此
		   的可扩展性、容错性等不同.
		   
		4) 思路：首先遍历原链表, 然后将原链表中的头指针和头节点作为新链表的头指针和头节点, 原链表中
		   的有效节点挨个依次取出来, 采用头插入的方法插入新链表中即可.
		   
		5) 链表逆序 = 遍历 + 头插入.

	3. 编程实战

		void reverse_linkedlist(struct node *pH)
		{
			struct node *p = pH->pNext;		// pH指向头节点，p指向第1个有效节点
			struct node *pBack;				// 保存当前节点的后一个节点地址
			
			// 当链表没有有效节点或者只有一个有效节点时，逆序不用做任何操作
			if ((NULL ==p) || (NULL == p->pNext))
				return;
			
			// 当链表有2个及2个以上节点时才需要真正进行逆序操作
			while (NULL != p->pNext)		// 是不是最后一个节点
			{
				// 原链表中第一个有效节点将是逆序后新链表的尾节点，尾节点的pNext指向NULL
				pBack = p->pNext;			// 保存p节点后面一个节点地址
				if (p == pH->pNext)
				{
					// 原链表第一个有效节点
					p->pNext = NULL;
				}
				else
				{
					// 原链表的非第1个有效节点
					p->pNext = pH->pNext;
				}
				pH->pNext = p;
				
				p = pBack;			// 走到下一个节点
			}
			// 循环结束后，最后一个节点仍然缺失
			insert_head(pH, p);
		}

//=======================================================================================================
									4.9.9.双链表的引入和基本实现
//-------------------------------------------------------------------------------------------------------
	1. 单链表的局限性
		
		1) 单链表是对数组的一个扩展, 解决了数组的大小比较死板不容易扩展的问题. 使用堆内存来存储数据,
		   将数据分散到各个节点之间, 其各个节点在内存中可以不相连, 节点之间通过指针进行单向链接. 链表
		   中的各个节点内存不相连, 有利于利用碎片化的内存.
		   
		2) 单链表各个节点之间只由一个指针单向链接, 这样实现有一些局限性. 局限性主要体现在单链表只能经
		   由指针单向移动(一旦指针移动过某个节点就无法再回来, 如果要再次操作这个节点除非从头指针开始
		   再次遍历一次), 因此单链表的某些操作就比较麻烦(算法比较有局限). 回忆之前单链表的所有操作
		   (插入、删除节点、 遍历、从单链表中取某个节点的数·····), 因为单链表的单向移动性导致了不少
		   麻烦.

		总结：单链表的单向移动性导致我们在操作单链表时, 当前节点只能向后移动不能向前移动, 因此不自由,
		      不利于解决更复杂的算法.

	2. 有效数据+2个指针的节点(双链表)
	
		1) 单链表的节点 = 有效数据 + 指针(指针指向后一个节点)
		
		2) 双向链表的节点 = 有效数据 + 2个指针(一个指向后一个节点, 另一个指向前一个节点)

	3. 双链表的封装和编程实现

//=======================================================================================================
									4.9.10.双链表的算法之插入节点
//-------------------------------------------------------------------------------------------------------
	1. 双链表尾部插入新节点
	
		void insert_tail(struct node *pH, struct node *new)
		{
			// 第一步先走到链表的尾节点
			struct node *p = pH;
			while (NULL != p->pNext)
			{
				p = p->pNext;			// 第一次循环走过了头节点
			}
			// 循环结束后p就指向了原来的最后一个节点
			// 第二步：将新节点插入到原来的尾节点的后面
			p->pNext = new;				// 后向指针关联好了。新节点的地址和前节点的next
			new->pPrev = p;				// 前向指针关联好了。新节点的prev和前节点的地址
										// 前节点的prev和新节点的next指针未变动
		}
	
	2. 双链表头部插入新节点

		// 一共有4个指针需要赋值. 注意的是顺序.
		void insert_head(struct node *pH, struct node *new)
		{
			// 新节点的next指针指向原来的第1个有效节点的地址
			new->pNext = pH->pNext;      // 可能等于NULL, 也可能不是NULL
			
			// 原来第1个有效节点的prev指针指向新节点的地址
			if (NULL != pH->pNext)
				pH->pNext->pPrev = new;
			
			// 头节点的next指针指向新节点地址
			pH->pNext = new;
			
			// 新节点的prev指针指向头节点的地址
			new->pPrev = pH;
		}

//=======================================================================================================
									4.9.11.双链表的算法之遍历节点
//-------------------------------------------------------------------------------------------------------
	1. 双链表的算法之遍历节点
	
		1) 双链表是单链表的一个父集. 双链表中如何完全无视pPrev指针, 则双链表就变成了单链表. 这就决定
		   了双链表的正向遍历(后向遍历)和单链表是完全相同的.
		   
		2) 双链表中因为多了pPrev指针, 因此双链表还可以前向遍历(从链表的尾节点向前面依次遍历直到头节
		   点). 但是前向遍历的意义并不大, 主要是因为很少有当前当了尾节点需要前向遍历的情况.
		 
		3) 如果仅仅是遍历链表, 不需要双向链表, 单向就可以.
		
		4) 总结：双链表是对单链表的一种有成本的扩展, 但是这个扩展在有些时候意义不大, 在另一些时候意义
		   就比较大. 因此在实践用途中要根据业务要求选择适合的链表.

	2. 编程实战
		
		// 后向遍历一个双链表
		void bianli(struct node *pH)
		{
			struct node *p = pH;
			
			while (NULL != p->pNext)
			{
				p = p->pNext;
				
				printf("data = %d.\n", p->data);
			}
		}

		// 前向遍历一个双遍历，参数pTail要指向链表末尾
		void qianxiang_bianli(struct node *pTail)
		{
			struct node *p = pTail;
			
			while (NULL != p->pPrev)
			{
				printf("data = %d.\n", p->data);		// 现在需要先打印, 在移动指针.
														// 
				p = p->pPrev;
			}
		}


		struct node *p = pHeader->pNext->pNext->pNext;  // 定义一个指针指向链表末尾.
		
		qianxiang_bianli(p);


		注意:
				1) 前向遍历时, 需要先打印, 再移动节点的指针.
				2) 后项遍历时, 开始指向的是头指针(不是第一个节点). 而前向遍历的时候, 开始指向的就是
				   最后一个节点. 两者不同, 打印和移动指针的顺序也不同.
				   
//=======================================================================================================
								4.9.12.双链表的算法之删除节点
//-------------------------------------------------------------------------------------------------------
	1. 双链表的算法之删除节点

		// 从链表pH中删除一个节点，节点中的数据是data
		int delete_node(struct node *pH, int data)
		{
			struct node *p = pH;
			
			if (NULL == p)
			{
				return -1;
			}
			
			while (NULL != p->pNext)
			{
				p = p->pNext;
				
				// 在这里先判断当前节点是不是我们要删除的那个节点
				if(p->data == data)
				{
					// 找到了, 删除之.当前上下文是: 当前节点为p
					if (NULL == p->pNext)
					{
						// 尾节点
						// p表示当前节点地址, p->pNext表示后一个节点地址, p->pPrev表示前一个节点的地址
						p->pPrev->pNext = NULL;
						// p->pPrev = NULL;			可以省略, 因为后面整个都被销毁了
						
						// 销毁p节点
						free(p);
						return 0;
					}
					else
					{
						// 不是尾节点, 普通节点
						// 前一个节点的next指针指向后一个节点的首地址
						p->pPrev->pNext = p->pNext;
						
						// 当前节点的prev和next指针都不用管, 因为后面会整体销毁整个节点
						
						// 后一个节点的prev指针指向前一个节点的首地址
						p->pNext->pPrev = p->pPrev;
						
						free(p);
						return 0;
					}
				}
			}
			printf("未找到目标节点.\n");
			return -1;
		}

//=======================================================================================================
									4.9.13.linux内核链表
//-------------------------------------------------------------------------------------------------------
	1. 前述链表数据区域的局限性
	
		1) 之前定义数据区域时直接int data, 我们认为我们的链表中需要存储的是一个int类型的数. 但是实际
		   上现实编程中链接中的节点不可能这么简单, 而是多种多样的.
		   
		2) 一般实际项目中的链表, 节点中存储的数据其实是一个结构体, 这个结构体中包含若干的成员, 这些
		   成员加起来构成了我们的节点数据区域.

	2. 一般性解决思路：数据区封装为一个结构体
	
		1) 因为链表实际解决的问题是多种多样的, 所以内部数据区域的结构体构成也是多种多样的. 这样也导
		   致了不同程序当中的链表总体构成是多种多样的. 导致的问题是：我们无法通过一个泛性的、普遍适
		   用的操作函数来访问所有的链表. 这就意味着我们设计一个链表就得写一套链表的操作函数(节点创建、
		   插入、删除、遍历······).
		   
		2) 实际上深层次分析会发现: 不同的链表虽然这些方法不能通用需要单独写, 但是实际上内部的思路和
		   方法是相同的, 只是函数的局部地区有不同. (实际上链表操作是相同的, 而涉及到数据区域的操作就
		   有不同)
		   
		3) 鉴于以上2点：我们的理念就是, 能不能有一种办法把所有链表中操作方法里共同的部分提取出来用
		   一套标准方法实现, 然后把不同的部分留着让具体链表的实现者自己去处理.
		   
		总结: 操作链表的操作可以分为两部分: 
				一部分是标准部分(链表的一些操作, 节点的创建,插入,遍历,删除);
				另一部分是非标准部分(操作数据区的部分).

				提供标准化的链表的操作供用户使用, 用户仅仅需要编写数据区的操作部分.

	3. 内核链表的设计思路(!!!!!!******!!!!!!)
	
		1) 内核链表中自己实现了一个纯链表(纯链表就是没有数据区域, 只有前后向指针)的封装. 以及纯链表
		   的各种操作函数(节点创建、插入、删除、遍历······).
		   
		2) 这个纯链表本身自己没有任何用处, 它的用法是给我们具体链表作为核心来调用.

	4. list.h文件简介
	
		1) 内核中核心纯链表的实现在include/linux/list.h文件中
		
		2) list.h中就是一个纯链表的完整封装, 包含节点定义和各种链表操作方法.

//=======================================================================================================
									4.9.14.内核链表的基本算法和使用简介	
//-------------------------------------------------------------------------------------------------------
	1. 内核链表的基本算法和使用简介
	
	2. 内核链表的节点创建、删除、遍历等
	
	3. 内核链表的使用实践
		
		1) 问题：内核链表只有纯链表, 没有数据区域, 怎么使用?
		
		2) 设计的使用方法是将内核链表作为将来整个数据结构的结构体的一个成员内嵌进去.
		
	4. 使用举例
		
		struct driver_info
		{
			int data;
		};

		// driver结构体用来管理内核中的驱动
		struct driver
		{
			char name[20];				// 驱动名称
			int id;						// 驱动id编号
			struct driver_info info;	// 驱动信息
			
			struct list_head head;		// 内嵌的内核链表成员
		};

		1) 分析driver结构体, 可知：前三个成员都是数据区域成员(就是我们之前简化为int data的东西), 
		   第4个成员是一个struct list_head类型的变量, 这就是一个纯链表.
		   
		2) 本来driver结构体是没有链表的, 也无法用链表来管理. 但是我们driver内嵌的head成员本身就是
		   一个纯链表, 所以driver通过head成员给自己扩展了链表的功能.
		   
		3) driver通过内嵌的方式扩展链表成员, 本身不只是有了一个链表成员, 关键是可以通过利用
		   list_head本身事先实现的链表的各种操作方法来操作head.

		最终效果：我们可以通过遍历head来实现driver的遍历; 遍历head的函数在list.h中已经事先写好了,
		          所以我们内核中去遍历driver时就不用重复去写了.
				  
		总结:
				1) LINUX内核通过操作head来操作driver, 实质上就是通过操作结构体的某个成员变量来操作
				   整个结构体变量. 这里面要借助container_of宏.
				   
				2) 借助head成员, 实现链表的功能. 进而可以通过链表访问操作其他的数据成员.

	5. 疑问list.h中
			struct list_head {
		struct list_head *next, *prev;
		};
		(??????)这里的list_head 应该是链表项(??????)

//=======================================================================================================
									4.9.15.什么是状态机
//-------------------------------------------------------------------------------------------------------
	1. 有限状态机
	
		1) 常说的状态机是有限状态机FSM. FSM指的是有有限个状态(一般是一个状态变量的值), 这个机器同时能够
		   从外部接收信号和信息输入, 机器在接收到外部输入的信号后会综合考虑当前自己的状态和用户输入的信
		   息, 然后机器做出动作：跳转到另一个状态,
		2) 考虑状态机的关键点：当前状态、外部输入、下一个状态.

	2. 两种状态机：Moore型和Mealy型
	
		1) Moore型状态机特点是：输出只与当前状态有关(与输入信号无关). 相对简单, 考虑状态机的下一个状态
		   时只需要考虑它的当前状态就行了.
		2) Mealy型状态机的特点是：输出不只和当前状态有关, 还与输入信号有关. 状态机接收到一个输入信号
		   需要跳转到下一个状态时, 状态机综合考虑2个条件(当前状态、输入值)后才决定跳转到哪个状态.
		   
	3. 状态机的主要用途：电路设计、FPGA程序设计、软件设计
	
		1) 电路设计中广泛使用了状态机思想.
		2) FPGA程序设计.
		3) 软件设计(框架类型的设计, 譬如操作系统的GUI系统、消息机制).

	4. 状态机解决了什么问题
	
		1) 我们平时写程序都是顺序执行的, 这种程序有个特点：程序的大体执行流程是既定的, 程序的执行是
		   遵照一定的大的方向有迹可寻的.
		2) 但是偶尔会碰到这样的程序：外部不一定会按照既定流程来给程序输入信息, 而程序还需要完全能够
		   接收并响应外部的这些输入信号, 还要能做出符合逻辑的输出.

//=======================================================================================================
									4.9.16.C语言实现简单的状态机
//-------------------------------------------------------------------------------------------------------
	1. C语言实现简单的状态机
	
	2. 题目：		开锁状态机
	   功能描述：	用户连续输入正确的密码则会开锁, 如果密码输入过程错误则锁会退回到初始状态重新计
	                入密码, 即：用户只需要连续输入出正确的密码即可开锁(输入错误不用撤销、也不用删除)
					
	3. 题目分析
		略

//=======================================================================================================
									4.9.17.多线程简介
//-------------------------------------------------------------------------------------------------------
	1. 操作系统下的并行执行机制
	
		1) 并行就是说多个任务同时被执行. 并行分微观上的并行和宏观上的并行.
		
		2) 宏观上的并行就是从长时间段(相对于人来说)来看, 多个任务是同时进行的; 微观上的并行就是真的
		   在并行执行.
		   
		3) 操作系统要求实现宏观上的并行. 宏观上的并行有2种情况：第一种是微观上的串行, 第二种是微观上
		   的并行.
		   
		4) 理论来说, 单核CPU本身只有一个核心, 同时只能执行一条指令, 这种CPU只能实现宏观上的并行, 微
		   观上一定是串行的. 微观上的并行要求多核心CPU. 多核CPU中的多个核心可以同时微观上执行多个指
		   令, 因此可以达到微观上的并行, 从而提升宏观上的并行度.

	2. 进程和线程的区别和联系
	
		1) 进程和线程是操作系统的两种不同软件技术, 目的都是实现宏观上的并行(通俗一点就是让多个程序同
		   时在一个机器上运行, 达到宏观上看起来并行执行的效果).
		   
		   (主要是实现并行, 当然也有隔离等其他目的.)
		   (单片机通过中断实现并行.)
		   
		2) 进程和线程在实现并行效果的原理上不同. 而且这个差异和操作系统有关. 譬如windows中进程和线程
		   差异比较大, 在linux中进程和线程差异不大(linux中线程就是轻量级的进程).
		   
		3) 不管是多进程还是多线程, 最终目标都是实现并行执行.
		
		4) 什么时候选多进程, 什么时候用多线程. 需要进一步参考应用编程部分.

	3. 多线程的优势
	
		1) 前些年多进程多一些, 近些年多线程开始用得多.
		
		2) 现代操作系统设计时考虑到了多核心CPU的优化问题, 保证了：多线程程序在运行的时候, 操作系统会
		   优先将多个线程放在多个核心中分别单独运行. 所以说多核心CPU给多线程程序提供了完美的运行环境.
		   所以在多核心CPU上使用多线程程序有极大的好处.

	4. 线程同步和锁
	
		多线程程序运行时要注意线程之间的同步.

	( 注意: 详细情况参考《3.linux应用编程和网络编程》)

//=======================================================================================================



