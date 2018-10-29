#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

unsigned int coinmax(ll n, vector <unsigned int> &m)
{
	if(n==0)
		return 0;
	if(n<=m.size())
		if(m[n-1])
			return m[n-1];
	//m[n-1]=n;
	unsigned int temp;
	temp=coinmax(n/4,m)+coinmax(n/3,m)+coinmax(n/2,m);
	if(temp>n)
	{
		if(n<=m.size())
			m[n-1]=temp;
		return temp;
	}
	else
	{
		if(n<=m.size())
			m[n-1]=n;
		return n;
	}
}

int main()
{
	int n;
	while(cin>>n)
	{
		if(n<3)
			cout<<n<<endl;
		else
		{
		vector <unsigned int>  m(n/3);
		m[0]=1;
		unsigned int dollars,mnhalf,temp;
		dollars=n;
		mnhalf=coinmax(n/2,m);
		temp=coinmax(n/4,m)+coinmax(n/3,m)+mnhalf;
		if(temp>n)
			dollars=temp;
		cout<<dollars<<endl;
		}
	}
	return 0;
}
