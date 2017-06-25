/*
ID: prithvi4
PROG: barn1 
LANG: C++                  
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int j,i,planks,stalls,cows,gaps=0,covered;
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");
	fin>>planks>>stalls>>cows;
	//cout<<planks<<stalls<<cows<<endl;
	vector <int> a(cows);
	for(i=0;i<cows;++i)
		fin>>a[i];
	//for(i=0;i<cows;++i)
	//	cout<<a[i]<<endl;
	sort(a.begin(),a.end());
	covered=a[cows-1]-a[0]+1;
	cout<<covered<<endl;
	for(i=0;i<cows-1;++i)
		if(a[i+1]-a[i]>1)
			gaps++;
	//cout<<gaps<<endl;
	if(gaps==0)
		fout<<covered<<endl;
	else
	{
		vector <int> glength(gaps);
		for(i=0,j=0;i<cows-1;++i)
			if(a[i+1]-a[i]>1)
			{
				glength[j]=a[i+1]-a[i]-1;
				++j;
			}
		sort(glength.begin(),glength.end());
		for(i=0;i<gaps;++i)
			cout<<glength[i]<<endl;
		for(i=0;(i<planks-1)&&(i<gaps);++i)
			covered-=glength[gaps-1-i];
		fout<<covered<<endl;
	}
	fin.close();
	fout.close();
	return 0;
}
