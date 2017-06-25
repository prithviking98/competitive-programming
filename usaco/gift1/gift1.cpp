/*
ID: prithvi4
PROG: gift1
LANG: C++                  
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class giver
{
public:
	int ini,ng,gift,acc;
	char name[15];
	giver()
	{
		ini=ng=gift=acc=0;
	}
	void calcacc()
	{
		acc+=(ini%ng);
	}
	void calcgift()
	{
		gift=ini/ng;
	}
};

int find(giver*,char*,int);

int main()
{
	int np,i,j,k,m;
	fstream fin("gift1.in");
	ofstream fout("gift1.out");
	char name[15];
	fin>>np;
	giver* ptr;
	ptr= new giver[np];
	for(i=0;i<np;++i)
	{
		fin>>ptr[i].name;
	}
	for(i=0;i<np;++i)
	{
		fin>>name;
		j=find(ptr,name,np);
		fin>>ptr[j].ini>>ptr[j].ng;
		if(ptr[j].ng!=0)
		{
			ptr[j].calcacc();
			ptr[j].calcgift();
			for(k=0;k<ptr[j].ng;++k)
			{
				fin>>name;
				m=find(ptr,name,np);
				ptr[m].acc+=ptr[j].gift;
			}
		}
		else
			ptr[j].acc+=ptr[j].ini;
	}
	for(i=0;i<np;++i)
	{
		fout<<ptr[i].name<<" "<<ptr[i].acc-ptr[i].ini<<endl;
	}
	delete [] ptr;
	ptr=NULL;
	fin.close();
	fout.close();
	return 0;
}
int find(giver* ptr,char* name,int np)
{
	int i;
	for(i=0;i<np;++i)
	{
		if(strcmp(name,ptr[i].name)==0)
			return i;
	}
}
