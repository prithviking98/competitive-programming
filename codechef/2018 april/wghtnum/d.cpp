#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

ll calc(ll n)
{
	ll m=1000000000+7;
	ll cp=10;
	ll pow=1;
	for(;n>0;n/=2)
	{
		if(n%2==1)
			pow=(cp*pow)%m;
		cp=(cp*cp)%m;
	}
	return pow;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		ll n,w;
		cin>>n>>w;
		if(w<-9||w>8)
		{
			cout<<0<<endl;
			continue;
		}
		ll num;
		if(w>=0)
			num=9-w;
		else
			num=10+w;
		num=(num*calc(n-2))%(1000000000+7);
		cout<<num<<endl;
	}
	return 0;
}
