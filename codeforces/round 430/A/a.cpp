#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	long long l,r,x,y,k,flag=0;
	cin>>l>>r>>x>>y>>k;
	for(int i=x;i<=y;++i)
	{
		if(i*k>=l&&i*k<=r)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		cout<<"YES";
	else 
		cout<<"NO";

	return 0;
}
