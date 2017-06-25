/*
ID: prithvi4
PROG:beads 
LANG: C++                  
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int maxbead(char [], int);

int main()
{
	int n;
	ifstream fin("beads.in");
	ofstream fout("beads.out");
	fin>>n;
	char neck[350];
	fin>>neck;
	//cout<<n<<endl<<neck;
	//cout<<endl<<"test";
	fout<<maxbead(neck,n)<<endl;
	fin.close();
	fout.close();
	return 0;
}
int maxbead(char a[],int n)
{
	int c=0,j,lc,rc,r,l;
	char s;
	for(j=0;j<=n-1;++j)
	{
		for(r=j;;)
		{
			if(a[r]!='w')
			{
				s=a[r];
				break;
			}
			++r;
			if(r==n)
				r=0;
			if(r==j)
				return n;
		}
		rc=0;
		for(r=j;;)
		{
			if(a[r]==s||a[r]=='w')
			{
				rc++;
				++r;
				if(r==n)
					r=0;
				if(r==j)
					return n;
			}
			else
				break;
		}
		lc=0;
		if(j==0)
			l=n-1;
		else 
			l=j-1;
		for(;;)
		{
			if(a[l]!='w')
			{
				s=a[l];
				break;
			}
			--l;
			if(l==-1)
				l=n-1;
		}
		if(j==0)
			l=n-1;
		else 
			l=j-1;
		for(;;)
		{
			if(a[l]==s||a[l]=='w')
			{
				++lc;
				--l;
				if(l==-1)
					l=n-1;
			}
			else
				break;
		}
		if((lc+rc)>=c)
			c=lc+rc;
	}
	if(c<=n)
	return c;
	else
		return n;
}
