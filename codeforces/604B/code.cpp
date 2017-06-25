#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int findmax(vi s,int n)
{
	int p=0;
	for(int i=0;i<n/2;++i)
		if(p<s[i]+s[n-1-i])
			p=s[i]+s[n-1-i];
	return p;
}
int main()
{
	int n,k,S,i;
	cin>>n>>k;
	vi s(n);
	rep(i,0,n)
		cin>>s[i];
	if(k>=n)
	{
		S=s[n-1];
	}
	else if(n>k&&n<2*k)
	{
		int t=findmax(s,2*(n-k));
		S=t>s[n-1]?t:s[n-1];
	}
	else if(n==2*k)
	{
		S=findmax(s,n);
	}
	cout<<S<<endl;
	return 0;
}
