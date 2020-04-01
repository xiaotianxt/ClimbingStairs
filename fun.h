#pragma once
#include "util.h"

using namespace std;

const int MAX_STACK = 5000; // ��������ջ�ܳ��ܲ�������visual studio�����йأ�
const int FLOOR_LENGTH_LIMMIT = 8; // ����һ���㷨���ܵ��������λ��

static vector<BigInteger> memory; // ���𱣴��м����Թ�����ʱ��ʹ��

/*********************************
* ���ƣ�		RecursionStart
* ������		���ڳ�ʼ���ݹ��㷨
* 
* ������		int& floor // ������
* ����ֵ��	BigInteger // ���ؼ�����
*********************************/
BigInteger RecursionStart(int& floor);

/*********************************
* ���ƣ�		Recursion
* ������		�ݹ��㷨
* 
* ������		int& floor // ������
			int current // ��ǰ����
* ����ֵ��	BigInteger // ���ؼ�����
*********************************/
BigInteger Recursion(int& floor, int current);

/*********************************
* ���ƣ�		NotRecur
* ������		�ǵݹ�ʵ�ּ���
* 
* ������		int floor ������
* ����ֵ��	BigInteger ���ؽ��
*********************************/
BigInteger NotRecur(int floor);

/*********************************
* ���ƣ�		isInteger
* ������		�����ж��Ƿ�������
* 
* ������		string* judge // �����ַ���ָ��
* ����ֵ��	bool // �ǣ�true
*********************************/
bool isInteger(string* judge);

/*********************************
* ���ƣ�		MemoryReset
* ������		���memory����
* 
* ������		None
* ����ֵ��	None
*********************************/
void MemoryReset();

/*********************************
* ���ƣ�		MemoryInit
* ������		��ʼ��memory���飨��0
* 
* ������		int &max_floor // ���̨����
* ����ֵ��	None
*********************************/
void MemoryInit(int &max_floor);

/*********************************
* ���ƣ�		Initialize
* ������		��ʼ������ʼ�Ŀ�ʼ
*
* ������		None
* ����ֵ��	None
*********************************/
void Initialize();

/*********************************
* ���ƣ�		TestMode
* ������		�������ģʽ
* 
* ������		None
* ����ֵ��	None
*********************************/
void TestMode();

void Calculate(string choice);

BigInteger NotRecurBig(BigInteger input);
