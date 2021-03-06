#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

#define TRACE
#ifdef TRACE
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracea(a,n) rep(II,0,n) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracevv(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define tracem(a,r,c)\
	{\
	rep(II,0,r){\
		rep(JJ,0,c)\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#else
#define trace1(x)   
#define trace2(x,y)   
#define trace3(x,y,z)   
#define trace4(w,x,y,z)  
#define tracev(a) 
#define tracea(a,n)  
#define tracevv(a)  
#define tracem(a,r,c)  
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int n,k,p;
vi isp(1121,1);
vi primes;
vector<vvi> dp;

int search(int index,int rem,int count)
{
	if(dp[index][rem][count]!=-1)
		return dp[index][rem][count];
	if(index==p)
	{
		if(rem>0||count<k)
			return dp[index][rem][count]=0;
		return dp[index][rem][count]=1;
	}
	if(rem==0)
	{
		if(count==k)
			return dp[index][rem][count]=1;
		return dp[index][rem][count]=0;
	}
	if(count==k)
	{
		if(rem>0)
			return dp[index][rem][count]=0;
		return dp[index][rem][count]=1;
	}
	if(primes[index]>rem)
	{
		return dp[index][rem][count]=search(index+1,rem,count);
	}
	return	dp[index][rem][count]=search(index+1,rem-primes[index],count+1)+search(index+1,rem,count);
}


int main()
{
	ios::sync_with_stdio(0);
	isp[0]=isp[1]=0;
	for(int i=2;2*i<=1120;++i)
		isp[2*i]=0;
	primes.PUB(2);
	for(int i=3;i<=1120;i+=2)
	{
		if(isp[i]==0)
			continue;
		primes.PUB(i);
		for(int j=3;j*i<=1120;j+=2)
			isp[j*i]=0;
	}
	p=primes.size();
	dp.resize(primes.size()+1);
	while(cin>>n>>k)
	{
		rep(i,0,p+1)
			dp[i].resize(n+5);
		rep(i,0,p+1)
			rep(j,0,n+5)
				dp[i][j].resize(k+1);
		rep(i,0,p+1)
			rep(j,0,n+5)
				rep(f,0,k+1)
					dp[i][j][f]=-1;
		if(n==0&&k==0)
			break;
		cout<<search(0,n,0)<<endl;
	}
	return 0;
}
