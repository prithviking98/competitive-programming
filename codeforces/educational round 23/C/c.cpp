#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll digitsum(ll n)
{
	ll t=n;
	ll s=0;
	while(t!=0)
	{
		s+=t%10;
		t/=10;
	}
	return s;
}

int main()
{
	//freopen("input.txt","r",stdin);
	ll s,n,i,count=0,d,k;
	cin>>n>>s;
	if(s<n)
	{
		for(k=s+1;k<=n;++k)
		{
			d=digitsum(k);
			if(k-d>=s)
				++count;
		}
	}
	cout<<count<<endl;
	return 0;
}
