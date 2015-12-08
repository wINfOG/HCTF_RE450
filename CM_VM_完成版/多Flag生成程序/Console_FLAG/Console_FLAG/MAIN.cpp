#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
char stringIn[] = "HCTF{S1FALS1R1Fa9123489}";
int M_Rand(void);
int main()
{
	char xx1 = '6';//修改的新的Flag  6个
	char xx2 = '5';
	char xx3 = '4';
	char xx4 = '3';
	char xx5 = '2';
	char xx6 = '1';

	int AimportantNum = 0;

	const char* SourceFile = "C_easy_VMP.exe";	//文件源位置
	const char* FlagList = "OUT//FlagList.txt";	//FlagList
	const int	Offset = 0x1A190;				//偏移
	const int	FileNum = 1000;					//生成文件个数
	char NewFile[20] = "OUT//";				//新文件位置

	std::ifstream in;
	std::ofstream out;
	std::ofstream FList;
	int num = 0;

	srand((int)time(NULL));

	FList.open(FlagList, std::ios::binary);//二进制打开FlagTable
	if (FList.fail())//打开源文件失败
	{
		printf("打开Flag表失败");
		return 1;
	}
	in.open(SourceFile, std::ios::binary);//二进制打开源文件

	if (in.fail())//打开源文件失败
	{
		printf("打开文件失败");
		return 1;
	}
	for (; num < FileNum; num++)
	{
		char change1[20];
		char change2[20];
		_itoa(num, change1, 10);
		strcat(change1, ".exe");
		//指定文件
		strcpy(change2, NewFile);
		strcat(change2, change1);
		//
		out.open(change2, std::ios::binary);//创建目标文件 
		if (out.fail())//创建文件失败
		{
			printf("创建文件:%s	————>Fail！\n", change2);
			out.close();
			in.close();
			return 1;
		}
		else				//复制文件
		{
			out << in.rdbuf();
			in.seekg(0, std::ios::beg);
			printf("创建文件:%s	————>OK\n", change2);
		}

		out.seekp(Offset, std::ios::beg);//到指定位置
		//flag随机。
		xx6 = (AimportantNum % 10) + 'A';
		xx5 = ((AimportantNum / 10) % 10) + 'a';
		xx4 = ((AimportantNum / 100) % 10) + '0';
		xx3 = M_Rand();
		xx2 = M_Rand();
		xx1 = M_Rand();

		AimportantNum++;
		//输出
		out << (char)(xx6 ^ 0x22);
		out << (char)(xx5 ^ 0x22);
		out << (char)(xx4 ^ 0x22);
		out << (char)(xx3 ^ 0x22);
		out << (char)(xx2 ^ 0x22);
		out << (char)(xx1 ^ 0x22);
		//输出到flagList
		FList << change1 << ":" << "HCTF{S1FALS1R1Fa9" << xx1 << xx2 << xx3 << xx4 << xx5 << xx6 <<"}"<< "\r\n";

		out.close();
	}
	//release
	in.close();
	FList.close();
	/*
	for (int i = 0; i < 100;i++)
	printf("%x\n", M_Rand());
	*/
	return 0;
}
int M_Rand()
{
	const int RandMax = 0x39;
	const int RandMin = 0x30;
	int ret = 0;
	
	for (; ret < RandMin;)
		ret = (int)(rand() % (RandMax + 1));
	return ret;
}