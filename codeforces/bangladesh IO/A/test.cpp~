#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector <float> q;
int count=0;
ifstream fin("input.txt");
ofstream fout("output.txt");

void add(char,float);
void leave(char);
void disp(char, float);

int main()
{
	int op,n,t;
	char loc;
	float id,val;
	fin>>t;
	for(int i=0;i<t;++i)
	{
		fout<<"Case "<<i+1<<":\n";
		fin>>n;
		for(int j=0;j<n;++j)
		{
			fin>>op;
			fin>>loc;
			if(op==1)
			{
				fin>>id;
				add(loc,id);
			}
			else if(op==2)
			{
				leave(loc);
			}
			else
			{
				fin>>val;
				disp(loc,val);	
			}
		}
	}
	return 0;
}

void add(char loc, float id)
{
	if(loc=='B')
	{
		q.push_back(id);
		++count;
	}
	else
	{
		q.push_back(0);
		for(int i=count-1;i>=0;--i)
			q[i+1]=q[i];
		q[0]=id;
		++count;
	}
}

void leave(char loc)
{
	if(loc=='B')
	{
		q.pop_back();
		--count;
	}
	else
	{
		for(int i=0;i<(count-1);++i)
			q[i]=q[i+1];
		q.pop_back();
		--count;
	}
}

void disp(char loc, float val)
{
	if(loc=='D')
		fout<<q[val-1]<<endl;
	else
	{
		for(int i=0;i<count;++i)
			if(q[i]==val)
				fout<<q[i];
	}
}
