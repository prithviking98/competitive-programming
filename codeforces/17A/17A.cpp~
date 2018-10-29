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
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	vector <bool> isp(n+1,true);
	vi primes;
	isp[0]=isp[1]=false;
	primes.PUB(2);
	for(int i=2;i*2<=n;++i)
		isp[i*2]=false;
	for(int i=3;i<=n;i+=2)
	{
		if(isp[i])
		{
			primes.PUB(i);
			for(int j=i;j*i<=n;j+=2)
				isp[j*i]=false;
		}
	}
//	tracev(isp);
//	tracev(primes);
	int count=0;
	for(int i=1;i<=primes.size()-1;++i)
	{
		if(primes[i]+primes[i+1]+1<=n&&isp[primes[i]+primes[i+1]+1])
			count++;
	}
	if(count>=k)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
