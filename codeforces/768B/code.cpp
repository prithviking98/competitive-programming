#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

string series(ll n)
{
	if(n==1)
		return "1";
	else if(n==0)
		return "0";
	else
	{
		string s1,s2;
		s1=series(n/2);
		s2=series(n%2);
		//cout<<s1<<" "<<s2<<endl;
		return s1+s2+s1;
	}
}
int main()
{
	ll n,l,r,count=0;
	string s;
	cin>>n>>l>>r;
	//cout<<n<<l<<r<<endl;
	s=series(n);
	//cout<<s<<endl;
	for(ll i=l-1;i<=r-1;++i)
		if(s[i]=='1')
			++count;
	cout<<count<<endl;
	return 0;
}
