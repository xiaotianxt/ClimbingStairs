#include "fun.h"

BigInteger RecursionStart(int &floor)
{
	int counter = 0;

	if (memory.back() == 0) // 如果最后一位是0
		while (memory[counter++] != 0)
			; // 首先找到第一个为零的值

	if (counter - 2 > floor) // 如果之前已经搞定了
		return Recursion(floor, floor);

	for (int temp_floor = counter - 2 + MAX_STACK; temp_floor < floor; temp_floor += MAX_STACK) // 每次递归搜索层数不能大于5000
	{
		Recursion(temp_floor, temp_floor);
	}

	// 此时已经可以直接从floor递归
	Recursion(floor, floor);

	return memory[floor];
}

BigInteger Recursion(int &floor, int current)
{
	if (current == -1) // 此时越界返回0
	{
		return 0;
	}
	else if (current == 0) // 此时结束返回1
	{
		assert(memory[0] == 1); // memory的第一个应当是1，第二个也应当是1
		return memory[0];
	}
	else
	{
		if (memory[current] != 0)	// 如果已经有值了
			return memory[current]; // 直接就可以返回
		else						// 否则需要递归寻找上一个值
		{
			return memory[current] =
					   Recursion(floor, current - 1) + Recursion(floor, current - 2);
		}
	}
}

BigInteger NotRecur(int floor)
{
	if (memory[floor] != 0) // 如果已经有结果了就直接返回
	{
		return memory[floor];
	}

	for (int i = 2; i <= floor; i++) // 注意第floor层的索引就是floor
	{
		if (memory[i] != 0) // 如果已经计算过了就跳过
		{
			continue;
		}
		else
		{
			memory[i] = memory[i - 1] + memory[i - 2];
		}
	}

	return memory[floor];
}

bool isInteger(string *judge)
{
	if ((*judge)[0] == '-' && (*judge).length() > 1) // 如果长度大于1，且是负数
	{
		for (int i = 1; i < (*judge).length(); i++) // 从第2个字符开始判断是否是整数
		{
			if ((*judge)[i] > '9' || (*judge)[i] < '0')
				return false;
		}
	}
	else // 否则只可能是正数
	{

		for (int i = 0; i < (*judge).length(); i++) // 从第0个开始
		{
			if ((*judge)[i] > '9' || (*judge)[i] < '0')
				return false;
		}
	}
	return true;
}

void MemoryReset()
{
	vector<BigInteger> new_memory;
	new_memory.push_back(1);
	new_memory.push_back(1); // 初始化
	memory.clear();			 // 清空memory
	memory.swap(new_memory); // 更新memory
}

void MemoryInit(int &max_floor)
{
	while ((max_floor + 1) > memory.size()) // 第二层到input层都赋初值0
	{
		memory.push_back(0); // vector不够时初始化
	}
}

void Initialize()

{
	memory.push_back(1); // 层数为0的方法有1种
	memory.push_back(1); // 层数为1的方法有1种
	clock_t start1, start2, end1, end2;
	string choice, temp;
	int input = 0;

	/***************** 选择模式 ******************/
	cout << "支持递归(A)与非递归(B)方法实现，以及测试模式(C, 包含时间测试，)" << endl;
	cout << "请输入你的选择！ A/B/C" << endl;
	cin >> choice;
	while (cin.fail() || (choice != "A" && choice != "B" && choice != "C"))
	{
		cin.sync();
		cout << "输入错误！请重新输入！ A/B/C\n";
		cin >> choice;
	}
	while (getchar() != '\n')
		; // 清除空格

	/***************** 测试模式 ******************/
	if (choice == "C") // 如果选择测试模式，自动运算、自动计时、无需输入
	{
		TestMode();
		return;
	}

	/***************** 输入层数（可循环） ******************/
	Calculate(choice);
}

void TestMode()
{
	clock_t start1, end1, start2, end2;
	cout << "------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "Floor" << resetiosflags(ios::left) // 用完之后清除
		 << setiosflags(ios::right) << setw(9) << "递归" << setw(12) << "非递归"
		 << resetiosflags(ios::right) << endl;
	cout << "------------------------------------" << endl;

	MemoryReset();
	assert(memory.size() == 2);		   // 此时记忆应当清空，仅存在初始条件0,1
	int max_floor = 100, x = 0, y = 0; // x, y 用于设置控制台光标
	while (max_floor != 0)
	{
		MemoryInit(max_floor);
		/***************** 递归法 ******************/
		start1 = clock();
		RecursionStart(max_floor);
		end1 = clock();

		/***************** 非递归 ******************/
		MemoryReset(); // 清空内存重新计算
		MemoryInit(max_floor);
		start2 = clock();
		NotRecur(max_floor);
		end2 = clock();
		MemoryReset(); // 清空内存重新计算

		cout << setiosflags(ios::left) << setiosflags(ios::scientific) << setw(14) << max_floor << resetiosflags(ios::left) << resetiosflags(ios::scientific) << setiosflags(ios::fixed) << setprecision(0)
			 << setiosflags(ios::right) << setw(9) << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << "ms" << setw(10) << (double)(end2 - start2) * 1000 / CLOCKS_PER_SEC << "ms"
			 << resetiosflags(ios::right) << endl;
		cin.sync();
		cin.clear();
		cin.ignore();
		cout << "输入n退出，回车键继续" << endl;
		char ch;
		ch = getch();
		if (ch == 'n')
			break;
		max_floor *= 2;
		getxy(&x, &y);
		gotoxy(x, y - 1);
		cout << "                           ";
		gotoxy(x, y - 1);
	}
	cout << "------------------------------------" << endl;
	Initialize();
	return;
}

void Calculate(string choice)
{
	/***************** 输入渠道 ******************/
	cout << "从文件导入(floors.txt)吗？ y/n" << endl;
	char file;
	file = getchar();
	ifstream fin;

	if (file == 'y')
	{
		cout << "\n正在打开文件.....\n"
			 << endl;
		fin.open("floors.txt");
	}
	else
	{
		cout << "\n 不打开文件 \n"
			 << endl;
	}
	clock_t start1, end1;
	string temp;
	int input;
	do
	{					 // 循环获得输入，直到输入-1
		if (file == 'y') // 从文件中获取输入
		{
			fin >> temp;
			while (!isInteger(&temp) || fin.fail() || atoi(temp.c_str()) < 0)
			// 排错:1. 不是整数 2. 输入错误 3. 范围错误
			{
				cout << temp << "不是大于1的整数，请检查文件格式！！！\n"
					 << endl;
				fflush(stdin);
				fin.clear();
				fin.ignore(INT_MAX, '\n');
				fin >> temp;
			}
		}
		else // 从控制台获取输入
		{
			cout << "\n请输入层数，-1回到上层，0退出：" << endl; // 其实0可以返回1，但是没有意义，因此这里直接令0为返回上层菜单
			cin >> temp;
			while (!isInteger(&temp) || cin.fail() || atoi(temp.c_str()) < -1)
			// 排错:1. 不是整数 2. 输入错误 3. 范围错误
			{
				fflush(stdin);
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "请输入正确的层数！！\n";
				cin >> temp;
			}
		}

		/***************** 仅为超长整数的提供算法 ******************/
		if (temp.length() > FLOOR_LENGTH_LIMMIT) // 如果超过8位，只能用非递归算法
		{
			cout << "数太大了，让我算算" << endl;
			BigInteger longinput;
			longinput = temp;
			start1 = clock();
			cout << NotRecurBig(longinput) << endl;
			end1 = clock();
			cout << "用时： \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n"
				 << endl;
			continue;
		}

		input = atoi(temp.c_str()); // 字符串 -> 整数
		if (input == 0)
		{
			return; // 直接退出
		}

		else if (input == -1) // 更换模式
		{
			Initialize(); // 重新运行，这样的缺点是多一层，但影响不大
			return;
		}

		/***************** memory初始化 ******************/
		MemoryInit(input);

		/***************** 实现走楼梯 ******************/
		if ("A" == choice) // 走递归
		{
			start1 = clock();
			cout << input << ": \t" << RecursionStart(input) << '\t';
			end1 = clock();
			cout << "用时： \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n"
				 << endl;
		}
		else if ("B" == choice) // 不走递归
		{
			start1 = clock();
			cout << input << ": \t" << NotRecur(input) << '\t';
			end1 = clock();
			cout << "用时： \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n"
				 << endl;
		}

		/***************** 下一个数 ******************/
	} while (true);
	return;
}

BigInteger NotRecurBig(BigInteger input)
{
	BigInteger i, a, b;
	i = 2;
	a = 1; // 奇数
	b = 2; // 偶数
	for (; i < input; i += 2)
	{
		a = (a + b);
		b = (a + b);
	}

	if (input % 2 == 1) // 如果是奇数
	{
		return a;
	}
	else
	{
		return b;
	}
}
