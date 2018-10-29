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
	int n;
	cin>>n;
	vector<bool> isp(n+1,true);
	vector<int> primes;
	isp[0]=isp[1]=false;
	primes.PUB(2);
	for(int i=4;i<=n;i+=2)
		isp[i]=false;
	for(int i=3;i<=n;i+=2)
	{
		if(isp[i])
		{
			primes.PUB(i);
			for(int j=i;j*i<=n;j+=2)
				isp[j*i]=false;
		}
	}
	int count=0;
	for(int i=6;i<=n;i++)
	{
		int dc=0;
		for(int j=0;j<primes.size()&&primes[j]<i;j++)
		{
			if(i%primes[j]==0)
			{
				dc++;
			}
		}
		if(dc==2)
			count++;
	}
	cout<<count<<endl;
	return 0;
}
