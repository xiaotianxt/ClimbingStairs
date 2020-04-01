#include "fun.h"

BigInteger RecursionStart(int& floor)
{
	int counter = 0;

	if (memory.back() == 0) // ������һλ��0
		while (memory[counter++] != 0); // �����ҵ���һ��Ϊ���ֵ

	if (counter - 2 > floor) // ���֮ǰ�Ѿ��㶨��
		return Recursion(floor, floor);

	for (int temp_floor = counter - 2 + MAX_STACK; temp_floor < floor; temp_floor += MAX_STACK) // ÿ�εݹ������������ܴ���5000
	{
			Recursion(temp_floor, temp_floor);
	}

	// ��ʱ�Ѿ�����ֱ�Ӵ�floor�ݹ�
	Recursion(floor, floor);
	

	return memory[floor];
}

BigInteger Recursion(int& floor, int current)
{
	if (current == -1) // ��ʱԽ�緵��0
	{
		return 0;
	}
	else if (current == 0) // ��ʱ��������1
	{
		assert(memory[0] == 1); // memory�ĵ�һ��Ӧ����1���ڶ���ҲӦ����1
		return memory[0];
	}
	else
	{
		if (memory[current] != 0) // ����Ѿ���ֵ��
			return memory[current]; // ֱ�ӾͿ��Է���
		else // ������Ҫ�ݹ�Ѱ����һ��ֵ
		{
			return memory[current] = \
				Recursion(floor, current - 1) + Recursion(floor, current - 2);
		}
	}
}

BigInteger NotRecur(int floor)
{
	if (memory[floor] != 0) // ����Ѿ��н���˾�ֱ�ӷ���
	{
		return memory[floor];
	}

	for (int i = 2; i <= floor; i++) // ע���floor�����������floor
	{
		if (memory[i] != 0) // ����Ѿ�������˾�����
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

bool isInteger(string* judge)
{
	if ((*judge)[0] == '-' && (*judge).length() > 1) // ������ȴ���1�����Ǹ���
	{
		for (int i = 1; i < (*judge).length(); i++) // �ӵ�2���ַ���ʼ�ж��Ƿ�������
		{
			if ((*judge)[i] > '9' || (*judge)[i] < '0')
				return false;
		}
	}
	else // ����ֻ����������
	{

		for (int i = 0; i < (*judge).length(); i++) // �ӵ�0����ʼ
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
	new_memory.push_back(1); // ��ʼ��
	memory.clear();				// ���memory
	memory.swap(new_memory); // ����memory
}

void MemoryInit(int &max_floor)
{
	while ((max_floor + 1) > memory.size()) // �ڶ��㵽input�㶼����ֵ0
	{
		memory.push_back(0); // vector����ʱ��ʼ��
	}
}

void Initialize()


{
	memory.push_back(1); // ����Ϊ0�ķ�����1��
	memory.push_back(1); // ����Ϊ1�ķ�����1��
	clock_t start1, start2, end1, end2;
	string choice, temp;
	int input = 0;

	/***************** ѡ��ģʽ ******************/
	cout << "֧�ֵݹ�(A)��ǵݹ�(B)����ʵ�֣��Լ�����ģʽ(C, ����ʱ����ԣ�)" << endl;
	cout << "���������ѡ�� A/B/C" << endl;
	cin >> choice;
	while (cin.fail() || (choice != "A" && choice != "B" && choice != "C"))
	{
		cin.sync();
		cout << "����������������룡 A/B/C\n";
		cin >> choice;
	}
	while (getchar() != '\n'); // ����ո�

	/***************** ����ģʽ ******************/
	if (choice == "C") // ���ѡ�����ģʽ���Զ����㡢�Զ���ʱ����������
	{
		TestMode();
		return;
	}

	/***************** �����������ѭ���� ******************/
	Calculate(choice);
}

void TestMode()
{
	clock_t start1, end1, start2, end2;
	cout << "------------------------------------" << endl;
	cout << setiosflags(ios::left) << setw(14) << "Floor" << resetiosflags(ios::left) // ����֮�����
		<< setiosflags(ios::right) << setw(9) << "�ݹ�" << setw(12) << "�ǵݹ�"
		<< resetiosflags(ios::right) << endl;
	cout << "------------------------------------" << endl;
	for (int i = 0; i < 5; ++i) {

	}
	MemoryReset();
	assert(memory.size() == 2); // ��ʱ����Ӧ����գ������ڳ�ʼ����0,1
	int max_floor = 100, x = 0, y = 0; // x, y �������ÿ���̨���
	while (max_floor != 0)
	{
		MemoryInit(max_floor);
		/***************** �ݹ鷨 ******************/
		start1 = clock();
		RecursionStart(max_floor);
		end1 = clock();

		/***************** �ǵݹ� ******************/
		MemoryReset(); // ����ڴ����¼���
		MemoryInit(max_floor);
		start2 = clock();
		NotRecur(max_floor);
		end2 = clock();
		MemoryReset(); // ����ڴ����¼���

		cout << setiosflags(ios::left) << setiosflags(ios::scientific) << setw(14) << max_floor << resetiosflags(ios::left) << resetiosflags(ios::scientific) << setiosflags(ios::fixed) << setprecision(0)
			<< setiosflags(ios::right) << setw(9) << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << "ms" << setw(10) << (double)(end2 - start2) * 1000 / CLOCKS_PER_SEC << "ms"
			<< resetiosflags(ios::right) << endl;
		cin.sync();
		cin.clear();
		cin.ignore();
		cout << "����n�˳������������" << endl;
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
	/***************** �������� ******************/
	cout << "���ļ�����(floors.txt)�� y/n" << endl;
	char file;
	file = getchar();
	ifstream fin;

	if (file == 'y')
	{
		fin.open("floors.txt");
	}
	clock_t start1, end1;
	string temp;
	int input;
	do { // ѭ��������룬ֱ������-1
		if (file == 'y') // ���ļ��л�ȡ����
		{
			fin >> temp;
			while (!isInteger(&temp) || fin.fail() || atoi(temp.c_str()) < 0)
				// �Ŵ�:1. �������� 2. ������� 3. ��Χ����
			{
				cout << temp << "���Ǵ���1�������������ļ���ʽ������\n" << endl;
				fflush(stdin);
				fin.clear();
				fin.ignore(INT_MAX, '\n');
				fin >> temp;
			}
		}
		else // �ӿ���̨��ȡ����
		{
			cout << "\n�����������-1�ص��ϲ㣬0�˳���" << endl; // ��ʵ0���Է���1������û�����壬�������ֱ����0Ϊ�����ϲ�˵�
			cin >> temp;
			while (!isInteger(&temp) || cin.fail() || atoi(temp.c_str()) < -1)
				// �Ŵ�:1. �������� 2. ������� 3. ��Χ����
			{
				fflush(stdin);
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "��������ȷ�Ĳ�������\n";
				cin >> temp;
			}
		}

		/***************** ��Ϊ�����������ṩ�㷨 ******************/
		if (temp.length() > FLOOR_LENGTH_LIMMIT) // �������8λ��ֻ���÷ǵݹ��㷨
		{
			cout << "��̫���ˣ���������" << endl;
			BigInteger longinput;
			longinput = temp;
			start1 = clock();
			cout << NotRecurBig(longinput) << endl;
			end1 = clock();
			cout << "��ʱ�� \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n" << endl;
			continue;
		}


		input = atoi(temp.c_str()); // �ַ��� -> ����
		if (input == 0)
		{
			return; // ֱ���˳�
		}

		else if (input == -1) // ����ģʽ
		{
			Initialize(); // �������У�������ȱ���Ƕ�һ�㣬��Ӱ�첻��
			return;
		}

		/***************** memory��ʼ�� ******************/
		MemoryInit(input);


		/***************** ʵ����¥�� ******************/
		if ("A" == choice) // �ߵݹ�
		{
			start1 = clock();
			cout << input << ": \t" << RecursionStart(input) << '\t';
			end1 = clock();
			cout << "��ʱ�� \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n" << endl;
		}
		else if ("B" == choice) // ���ߵݹ�
		{
			start1 = clock();
			cout << input << ": \t" << NotRecur(input) << '\t';
			end1 = clock();
			cout << "��ʱ�� \t" << (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC << " ms\n" << endl;
		}

		/***************** ��һ���� ******************/
	} while (true);
	return;
}

BigInteger NotRecurBig(BigInteger input)
{
	BigInteger i, a, b;
	i = 2;
	a = 1; // ����
	b = 2; // ż��
	for (; i < input; i+=2)
	{
		a = (a + b);
		b = (a + b);
	}

	if (input % 2 == 1) // ���������
	{
		return a;
	}
	else
	{
		return b;
	}

}
