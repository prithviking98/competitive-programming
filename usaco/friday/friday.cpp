
/*
ID: prithvi4
PROG:friday 
LANG: C++                  
*/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main()
{
	int n,j=2;
	ifstream fin("friday.in");
	ofstream fout("friday.out");
	fin>>n;
	vector<int> day(7);
	for(int i=1900;i<1900+n;++i)
	{
		int f; // f is number of days in february
		if(i%100!=0)
		{
			if(i%4==0)
				f=29;
			else
				f=28;
		}
		else
		{
			if(i%400==0)
				f=29;
			else
				f=28;
		}
		for(int k=1;k<=12;++k)
		{
			if(k==1||k==3||k==5||k==7||k==8||k==10||k==12)
			{
				for(int l=1;l<=31;++l)
				{
					if(l==13)
						day[j]=day[j]+1;
					++j;
					if(j==7)
						j=0;
				}
			}
			else if(k==2)	
			{
				for(int l=1;l<=f;++l)
				{
					if(l==13)
						day[j]=day[j]+1;
					++j;
					if(j==7)
						j=0;
				}
			}
			else
			{
				for(int l=1;l<=30;++l)
				{
					if(l==13)
						day[j]=day[j]+1;
					++j;
					if(j==7)
						j=0;
				}
			}
		}
	}
	for(int i=0;i<6;++i)
		fout<<day[i]<<" ";
	fout<<day[6]<<endl;
	fout.close();
	fin.close();
	return 0;
}
