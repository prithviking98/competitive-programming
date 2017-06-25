#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

ll C(ll n,ll r)
{
	if(r==2)
		return n*(n-1)/2;
	else
		return n*(n-1)*(n-2)/6;
}
int main()
{
	ios::sync_with_stdio(0);
	//freopen("input.txt","r",stdin);
	ll size,c,i,j,k,ways=0;
	cin>>size;
	vi a(size);
	for(c=0;c<size;++c)
		cin>>a[c];
	sort(a.begin(),a.end());
	i=j=k=0;
	ll temp;
	temp=a[0];
	for(c=0;c<size;++c)
	{
		if(a[c]==temp)
			++i;
		else
			break;
	}
	if(c<size)
	{
		temp=a[c];
		for(;c<size;++c)
		{
			if(a[c]==temp)
				j++;
			else
				break;
		}
	}
	if(c<size)
	{
		temp=a[c];
		for(;c<size;++c)
		{
			if(a[c]==temp)
				k++;
			else
				break;
		}
	}
	//cout<<i<<j<<k<<endl;
	if(i>=3)
		cout<<C(i,3)<<endl;
	else if(i==2)
		cout<<j<<endl;
	else if(i==1&&j>1)
		cout<<C(j,2)<<endl;
	else if(i==1&&j==1)
		cout<<k<<endl;
	return 0;
}
