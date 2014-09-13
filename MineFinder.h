#ifndef MF
#define MF

#include<iostream>
#include<fstream>
#include<vector>
#include"util.h"
using namespace std;



class MineFinder
{
public:
	void Operator(char* filename);
	void Testcase(int n){testcase = n;};
	vector<int> intParsing(char* in);
	vector<int> Minefinder(void);
	void IncTestcase(void){++testcase;};
	void Setsize(int r, int c){Row = r; Col =c;};
	bool IsExist(XY cur);     //whether block is exist or not
	bool IsCovered(XY cur);   // whether block is covered or not   
	bool IsMine(XY cur);
	bool IsNone(XY cur);

private:
	vector<vector<int>> World;
	int testcase;
	int Row, Col;
};



#endif