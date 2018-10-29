#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

ll fact(ll a)
{
	ll f=1,i;
	for(i=1;i<=a;++i)
		f*=i;
	return f;
}
int main()
{
	ll a,b,f=1;
	cin>>a>>b;
	if(a<b)
		cout<<fact(a)<<endl;
	else cout<<fact(b)<<endl;
	return 0;
}
