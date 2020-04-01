#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <cstdio>
#include <time.h>
#include <assert.h>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

void gotoxy(int x, int y);	//该函数可设置光标到任意坐标
void getxy(int *x, int *y); //该函数获取当前控制台光标位置

class BigInteger
{
public:
	static const int base = 100000000; // s中每个元素的范围
	static const int width = 8;		   // 元素的宽度，与base对应
	vector<int> s;					   // 储存大整数

	bool IsEven() // 返回是否是偶数
	{
		return !(s[0] % 2);
	}

	BigInteger(long long num = 0) { *this = num; } //构造函数，对于longlong类型的整数可以直接构造

	BigInteger operator=(long long num) // 重载=号（注意这里只接受最大long long类型的整数）
	{
		vector<int> news;
		news.swap(s);
		news.clear(); // 清空s，并销毁s多余的内存空间

		do
		{
			s.push_back(num % base);
			num = num / base;
		} while (num > 0); // 将大数按照8位划分后放入数组（倒序）

		return *this;
	}

	BigInteger operator=(const string &str) //重载=号 （接受字符串类型的整数）
	{
		s.clear();
		int x, len = (str.length() - 1) / width + 1; // 返回函数的长度
		for (int i = 0; i < len; i++)
		{
			int end = str.length() - i * width;
			int start = max(0, end - width);				   // 对于不够8位的选择0，够8位的选择end - width
			s.push_back(stoi(str.substr(start, end - start))); // 将字符串转换为数字后装入s（倒序）
		}
		return *this;
	}

	friend ostream &operator<<(ostream &out, const BigInteger &x) //重载输出号
	{
		out << x.s.back();
		for (int i = x.s.size() - 2; i >= 0; i--)
		{
			char buf[20];
			sprintf(buf, "%08d", x.s[i]);
			for (int j = 0; j < int(strlen(buf)); j++)
				out << buf[j];
		}
		return out;
	}
	friend istream &operator>>(istream &in, BigInteger &x) //重载输入号
	{
		string s;
		if (!(in >> s))
			return in;
		x = s;
		return in;
	}
	BigInteger operator+(const BigInteger &b) const //重载加号
	{
		BigInteger c;
		c.s.clear();
		for (int i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = g;
			if (i < s.size())
				x += s[i];
			if (i < b.s.size())
				x += b.s[i];
			c.s.push_back(x % base);
			g = x / base;
		}
		return c;
	}
	BigInteger operator-(const BigInteger &b) //重载减号,默认前面大于后面
	{
		BigInteger c;
		c.s.clear();
		if (*this > b)
		{
			int i, g;
			for (i = 0, g = 0;; i++)
			{
				if (g == 0 && i >= b.s.size())
					break;
				int x = g;
				if (s[i] < b.s[i])
				{
					s[i + 1] -= 1;
					s[i] = s[i] + base;
				}
				if (i < s.size())
					x += s[i];
				if (i < b.s.size())
					x -= b.s[i];
				c.s.push_back(x % base);
				g = x / base;
			}
			int x = 0;
			for (; i < s.size(); i++)
			{
				x += s[i];
				c.s.push_back(x % base);
				x = x / base;
			}
		}
		return c;
	}
	bool operator<(const BigInteger &b) const //重载小于号
	{
		if (s.size() != b.s.size())
			return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i])
				return s[i] < b.s[i];
		return false;
	}
	bool operator>(const BigInteger &b) const //重载大于号
	{
		return b < *this;
	}
	bool operator<=(const BigInteger &b) const
	{
		return !(b < *this);
	}
	bool operator>=(const BigInteger &b) const
	{
		return !(*this < b);
	}
	bool operator==(const long long &b) const // 重载等于，和整数匹配
	{
		return !(BigInteger(b) < *this) && !(*this < BigInteger(b)); // 如果小于
	}
	bool operator==(const BigInteger &b) const //重载等于，和大数类型匹配
	{
		return !(b < *this) && !(*this < b);
	}
	bool operator!=(const BigInteger &b) const // 重载不等于
	{
		return (b < *this) || (*this < b); // 只要大于或小于就行
	}
	bool operator!=(const long long &b) const
	{
		return (BigInteger(b) < *this) || (*this < BigInteger(b));
	}
	BigInteger operator+=(const BigInteger &b)
	{
		*this = (*this + b);
		return *this;
	}
	BigInteger operator-=(const BigInteger &b)
	{
		*this = (*this - b);
		return *this;
	}
	BigInteger operator++(int) // 重载自增
	{
		*this += 1;
		return *this;
	}
	BigInteger operator%(const BigInteger &b)
	{
		BigInteger temp;
		temp = *this;
		while (true)
		{
			if (temp < b) // 如果temp比b小，说明可以了
				return temp;
			temp -= b; // 减去n个b
		}
		assert(true); // 不应该到这来，有可能是因为是负数
	}
};