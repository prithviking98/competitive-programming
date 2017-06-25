/*
ID: prithvi4
PROG: milk 
LANG: C++                  
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class farmer
{
public:
	int price, amount;
};

int comp(farmer& x, farmer& y)
{
	return x.price<y.price;
}

int main()
{
	int n,m;
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	fin>>n>>m;
	vector <farmer> f(m);
	for(int i=0;i<m;++i)
		fin>>f[i].price>>f[i].amount;
	sort(f.begin(),f.end(),comp);
	/*for(int i=0;i<m;++i)
		cout<<f[i].price<<endl;*/
	int cost=0;
	for(int i=0;n>0;++i)
	{
		if(f[i].amount<=n)
		{
			cost+=f[i].price*f[i].amount;
			n-=f[i].amount;
		}
		else
		{
			cost+=f[i].price*n;
			n=0;
		}
	}
	fout<<cost<<endl;
	fin.close();
	fout.close();
	return 0;
}