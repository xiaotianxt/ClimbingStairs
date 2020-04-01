#pragma once
#include "util.h"

using namespace std;

const int MAX_STACK = 5000; // 定义最大堆栈能承受层数（与visual studio配置有关）
const int FLOOR_LENGTH_LIMMIT = 8; // 定义一般算法接受的最大整数位数

static vector<BigInteger> memory; // 负责保存中间结果以供其他时间使用

/*********************************
* 名称：		RecursionStart
* 描述：		用于初始化递归算法
* 
* 参数：		int& floor // 最大层数
* 返回值：	BigInteger // 返回计算结果
*********************************/
BigInteger RecursionStart(int& floor);

/*********************************
* 名称：		Recursion
* 描述：		递归算法
* 
* 参数：		int& floor // 最大层数
			int current // 当前层数
* 返回值：	BigInteger // 返回计算结果
*********************************/
BigInteger Recursion(int& floor, int current);

/*********************************
* 名称：		NotRecur
* 描述：		非递归实现计算
* 
* 参数：		int floor 最大层数
* 返回值：	BigInteger 返回结果
*********************************/
BigInteger NotRecur(int floor);

/*********************************
* 名称：		isInteger
* 描述：		用于判断是否是整数
* 
* 参数：		string* judge // 传入字符串指针
* 返回值：	bool // 是：true
*********************************/
bool isInteger(string* judge);

/*********************************
* 名称：		MemoryReset
* 描述：		清除memory数组
* 
* 参数：		None
* 返回值：	None
*********************************/
void MemoryReset();

/*********************************
* 名称：		MemoryInit
* 描述：		初始化memory数组（设0
* 
* 参数：		int &max_floor // 最大台阶数
* 返回值：	None
*********************************/
void MemoryInit(int &max_floor);

/*********************************
* 名称：		Initialize
* 描述：		初始化，开始的开始
*
* 参数：		None
* 返回值：	None
*********************************/
void Initialize();

/*********************************
* 名称：		TestMode
* 描述：		进入测试模式
* 
* 参数：		None
* 返回值：	None
*********************************/
void TestMode();

void Calculate(string choice);

BigInteger NotRecurBig(BigInteger input);
