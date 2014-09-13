#include<iostream>
#include<fstream>
#include<vector>
#include"MineFinder.h"
#include"util.h"

using namespace std;


void MineFinder::Operator(char* filename)
{
	/*read file*/
	fstream fin, fout;
	fin.open(filename, fstream::in);
	fout.open("c:\\algo_hw\\hw1\\2011196093.txt ", fstream::out);

	/*read testcase*/
	char* input;
	input = new char[1000];
	memset(input,NULL,1000);

	fin.getline(input, 999);

	vector<int> rt = intParsing(input);
	Testcase(rt[0]);

	memset(input,NULL,1000);
	
	/*iterate until testcase is over*/
	int i = 0;
	while(testcase > i)
	{
		/*read row and colum*/
		memset(input,NULL,1000);
		fin.getline(input, 999);
		vector<int> row_col = intParsing(input);
		int row = row_col[0];
		int col = row_col[1];
		Setsize(row, col);

		/*read all map*/
		int j = 0;
		while(row > j)
		{
			/*read one line*/
			fin.getline(input, 999);
			vector<int> temp_row = intParsing(input);
			World.push_back(temp_row);
			memset(input,NULL,1000);

			j++;
		}  //read map end

		/*find mines and nones*/
		vector<int> result = Minefinder();

		/*print out result*/
		fout << '#' << (i + 1) << endl;
		for(vector<int>::iterator it = result.begin(); it != result.end(); ++it)
		{
			if(*it == -1)
			{
				++it;
				fout << endl;
				if(it == result.end()) break;
			}
			fout << *it << ' ';
		}

		fout << endl;

		World.clear();
		i++;
	}  // while end
	delete input;
}

vector<int> MineFinder::intParsing(char* in)
{
	vector<int> ret;
	char* s = in;
	int length = strlen(in);

	for(int i = 0; i < length; i++)
	{
		if(in[i] == ' ')
		{
			in[i] = NULL;
			ret.push_back(atoi(s));
			s = in; s += (i+1);
		}
		else if(i == (length-1) )
		{
			in[i+1] = NULL;
			ret.push_back(atoi(s));
			break;
		}
		else if(in[i] == '/')
		{
			in[i] = NULL;
			ret.push_back(atoi(s));
			break;
		}
	}
	return ret;
}


vector<int> MineFinder::Minefinder(void)
{
	vector<int> ret;
	XY current;
	XY center;
	bool IsFound = true;
int cir = 0;	
	while(IsFound)
	{
		IsFound = false;
		for(int i = 0; i < Row; i++)
			for(int j = 0; j < Col; j++)
			{
				if(World[i][j] >= 0 && World[i][j] <= 8)
				{	
					int FoundMine = 0;
					XY Available[8];
					int Aindex = 0;
					center.x = i; center.y = j;
					current = center;

					/*check each block near center*/
					current.y--;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}

					current.x--;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}

					current.y++;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}
				
					current.y++;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}
				
					current.x++;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}

					current.x++;
	
 					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}

					current.y--;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}

					current.y--;
					if(IsMine(current))
						FoundMine++;
					else if(IsExist(current) && IsCovered(current) && !IsNone(current))
					{
						Available[Aindex++] = current; 
					}													// end of iterate near blocks
				
	/*if(i ==  0 && j == 6)
	{
		cout << "(" << i << ',' << j << ')' << endl;
		cout << "World near mine number : " << World[i][j] << endl;
		cout << "mine num : " << FoundMine << endl;
		cout << "Availabe : " << Aindex << endl;
	}*/
					if(World[i][j] == FoundMine)
					{
						for(int k = 0; k < Aindex; k++)
						{
							World[Available[k].x][Available[k].y] = '+';
							IsFound = true;
						}
					}
					else if((World[i][j] - FoundMine) == (Aindex))
					{
						for(int k = 0; k < Aindex; k++)
						{
							World[Available[k].x][Available[k].y] = '*';
						}
						IsFound = true;
					}
				}
			}
			++cir;
		}

		for(int i = 0; i < Row; i++)
		{
			for(int j = 0; j < Col; j++)
				if(World[i][j] == '*')
				{
					ret.push_back(i); ret.push_back(j);
				}
		}	
		ret.push_back(-1);

		for(int i = 0; i < Row; i++)
		{
			for(int j = 0; j < Col; j++)
				if(World[i][j] == '+')
				{
					ret.push_back(i); ret.push_back(j);
				}
		}

	return ret;
}



bool MineFinder::IsExist(XY cur)
{
	if(cur.x < 0 || cur.x >= Row)
		return false;
	if(cur.y < 0 || cur.y >= Col)
		return false;
	return true;
}

bool MineFinder::IsNone(XY cur)
{
	//if(!IsExist(cur)) return false;
	if(World[cur.x][cur.y] == '+')
		return true;  
	return false; 
}

bool MineFinder::IsCovered(XY cur)
{
	//if(!IsExist(cur)) return false;
	if(World[cur.x][cur.y] == -1)
		return true;
	return false;
}

bool MineFinder::IsMine(XY cur)
{
	if(!IsExist(cur)) return false;
	if(World[cur.x][cur.y] == '*')
		return true;
	return false;
}

int main()
{
	MineFinder MineF;
	MineF.Operator("C:\\algo_hw\\hw1\\input.txt");

	return 1;
}