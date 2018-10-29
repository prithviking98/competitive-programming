#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n;
	cin>>n;
	int count=1;
	int i=2;
	int f=2;
	while(i<n)
	{
		if(f==2)
		{
			--i;
			f=1;
			++count;
		}
		else
		{
			i+=2;
			f=2;
			++count;
		}
	}
	if(n==2)
		count+=2;
	else
		++count;
	cout<<count<<endl;
	i=f=2;
	while(i<n)
	{
		if(f==2)
		{
			cout<<i<<" ";
			--i;
			f=1;
		}
		else
		{
			cout<<i<<" ";
			i+=2;
			f=2;
		}
	}
	cout<<i<<" "<<i-1;
	if(i==2)
		cout<<" "<<i;
	return 0;
}
