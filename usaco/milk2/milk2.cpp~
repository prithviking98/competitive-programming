/*
ID: prithvi4
PROG: milk2
LANG: C++                  
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class farmer
{
public:
	int start,stop;
	farmer()
	{
		start=stop=0;
	}
};

bool comp(farmer& x,farmer& y)
{
	return x.start<y.start;
}

int main()
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");
	int s,e,n,i=0,m=0;
	fin>>n;
	vector <farmer> a(n);
	vector <int> it(n),mt(n);
	for(int i=0;i<n;++i)
		fin>>a[i].start>>a[i].stop;
	sort(a.begin(),a.end(),comp);
	s=a[0].start;
	e=a[0].stop;
	for(int j=1;j<n;++j)
	{
		if(a[j].stop<=e)
			continue;
		else if(a[j].start>e)
		{
			mt[m]=e-s;
			++m;
			it[i]=a[j].start-e;
			++i;
			s=a[j].start;
			e=a[j].stop;
		}
		else if(a[j].start<=e&&a[j].stop>e)
		{
			e=a[j].stop;
		}
	}
	mt[m]=e-s;
	sort(it.begin(),it.end());
	sort(mt.begin(),mt.end());
	fout<<mt[n-1]<<" "<<it[n-1]<<endl;
	return 0;
}
