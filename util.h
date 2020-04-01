#pragma once
#pragma warning(disable:4996)
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

void gotoxy(int x, int y); //�ú��������ù�굽��������
void getxy(int* x, int* y); //�ú�����ȡ��ǰ����̨���λ��


class BigInteger
{
public:
	static const int base = 100000000; // s��ÿ��Ԫ�صķ�Χ
	static const int width = 8; // Ԫ�صĿ�ȣ���base��Ӧ
	vector<int>s;  // ���������

	BigInteger(long long num = 0) { *this = num; }    //���캯��������longlong���͵���������ֱ�ӹ���

	BigInteger operator=(long long num) // ����=�ţ�ע������ֻ�������long long���͵�������
	{
		vector<int> news;
		news.swap(s);
		news.clear(); // ���s��������s������ڴ�ռ�

		do
		{
			s.push_back(num % base);
			num = num / base;
		} while (num > 0); // ����������8λ���ֺ�������飨����

		return *this;
	}

	BigInteger operator=(const string& str)      //����=�� �������ַ������͵�������
	{
		s.clear();
		int x, len = (str.length() - 1) / width + 1; // ���غ����ĳ���
		for (int i = 0; i < len; i++)
		{
			int end = str.length() - i * width;
			int start = max(0, end - width); // ���ڲ���8λ��ѡ��0����8λ��ѡ��end - width
			s.push_back(stoi(str.substr(start, end - start)));  // ���ַ���ת��Ϊ���ֺ�װ��s������
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const BigInteger& x)   //���������
	{
		out << x.s.back();
		for (int i = x.s.size() - 2; i >= 0; i--)
		{
			char buf[20];
			sprintf(buf, "%08d", x.s[i]);
			for (int j = 0; j<int(strlen(buf)); j++)
				out << buf[j];
		}
		return out;
	}
	friend istream& operator>>(istream& in, BigInteger& x)   //���������
	{
		string s;
		if (!(in >> s)) return in;
		x = s;
		return in;
	}
	BigInteger operator+(const BigInteger& b)const   //���ؼӺ�
	{
		BigInteger c;
		c.s.clear();
		for (int i = 0, g = 0;; i++) {
			if (g == 0 && i >= s.size() && i >= b.s.size()) break;
			int x = g;
			if (i < s.size()) x += s[i];
			if (i < b.s.size()) x += b.s[i];
			c.s.push_back(x % base);
			g = x / base;
		}
		return c;
	}
	BigInteger operator-(const BigInteger& b)   //���ؼ���,Ĭ��ǰ����ں���
	{
		BigInteger c;
		c.s.clear();
		if (*this > b) {
			int i, g;
			for (i = 0, g = 0;; i++) {
				if (g == 0 && i >= b.s.size()) break;
				int x = g;
				if (s[i] < b.s[i]) {
					s[i + 1] -= 1;
					s[i] = s[i] + base;
				}
				if (i < s.size()) x += s[i];
				if (i < b.s.size()) x -= b.s[i];
				c.s.push_back(x % base);
				g = x / base;
			}
			int x = 0;
			for (; i < s.size(); i++) {
				x += s[i];
				c.s.push_back(x % base);
				x = x / base;
			}
		}
		return c;
	}
	bool operator<(const BigInteger& b)const   //����С�ں�
	{
		if (s.size() != b.s.size()) return s.size() < b.s.size();
		for (int i = s.size() - 1; i >= 0; i--)
			if (s[i] != b.s[i]) return s[i] < b.s[i];
		return false;
	}
	bool operator>(const BigInteger& b)const   //���ش��ں�
	{
		return b < *this;
	}
	bool operator<=(const BigInteger& b)const
	{
		return !(b < *this);
	}
	bool operator>=(const BigInteger& b)const
	{
		return !(*this < b);
	}
	bool operator==(const long long& b)const // ���ص��ڣ�������ƥ��
	{
		return !(BigInteger(b) < *this) && !(*this < BigInteger(b)); // ���С��
	}
	bool operator==(const BigInteger& b)const  //���ص��ڣ��ʹ�������ƥ��
	{
		return !(b < *this) && !(*this < b);
	}
	bool operator!=(const BigInteger& b)const // ���ز�����
	{
		return (b < *this) || (*this < b); // ֻҪ���ڻ�С�ھ���
	}
	bool operator!=(const long long& b)const
	{
		return (BigInteger(b) < *this) || (*this < BigInteger(b));
	}
	BigInteger operator+=(const BigInteger& b)
	{
		*this = (*this + b);
		return *this;
	}
	BigInteger operator-=(const BigInteger& b)
	{
		*this = (*this - b);
		return *this;
	}
	BigInteger operator++( int ) // ��������
	{
		*this += 1;
		return *this;
	}
	BigInteger operator%(const BigInteger& b)
	{
		BigInteger temp;
		temp = *this;
		while (true)
		{
			if (temp < b) // ���temp��bС��˵��������
				return temp;
			temp -= b; // ��ȥn��b
		}
		assert(true); // ��Ӧ�õ��������п�������Ϊ�Ǹ���
	}
};