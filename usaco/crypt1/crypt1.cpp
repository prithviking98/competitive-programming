/*
ID: prithvi4
PROG: crypt1 
LANG: C++                  
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int DigitCheck(int p, vector <int> d,int n)
{
	int i,j,digit,flag=0;
	for(i=0;p!=0;++i)
	{
		digit=p%10;
		flag=0;
		for(j=0;j<n;++j)
		{
			if(digit==d[j])
				flag=1;
		}
		if(flag==0)
			return 0;
		p/=10;
	}
	return 1;
}

int main()
{
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");
	int i,j,k,l,m,ptemp,x,y,n,solutions=0,num;
	fin>>n;
	vector <int> d(n),p;
	for(i=0;i<n;++i)
		fin>>d[i];
	sort(d.begin(),d.end());
	for(i=0;i<n;++i)
		cout<<d[i];
	cout<<endl;
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{
			for(k=0;k<n;++k)
			{
				num=d[i]*100+d[j]*10+d[k];
				cout<<num<<endl;
				m=0;
				p.clear();
				for(l=0;l<n;++l)
				{
					ptemp=num*d[l];
					if(ptemp/1000==0)
						if(DigitCheck(ptemp,d,n))
						{
							p.push_back(ptemp);
							cout<<"ptemp "<<ptemp<<endl;
							++m;
						}
				}
				for(x=0;x<m;++x)
					for(y=0;y<m;++y)
						if(/*((p[x]+p[y])/10000==0)&&*/DigitCheck(10*p[x]+p[y],d,n))
						{	
							cout<<"  px+py "<<10*p[x]+p[y]<<endl;
							++solutions;
							cout<<"solution "<<solutions<<endl;
						}
			}
		}
	}
	fout<<solutions<<endl;
	fin.close();
	fout.close();
	return 0;
}
