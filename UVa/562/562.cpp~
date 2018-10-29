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

int n;
vi a;
vvi dp(105);
int search(int index,int rem,int sum)
{
	if(dp[index][rem]!=-1)
		return dp[index][rem];
	if(index==n)
	{
		return dp[index][rem]=sum-rem;
	}
	if(a[index]>rem)
	{
		return dp[index][rem]=search(index+1,rem,sum);
	}
	return dp[index][rem]=max(search(index+1,rem-a[index],sum),search(index+1,rem,sum));
}

int main()
{
	ios::sync_with_stdio(0);
	rep(i,0,105)
		dp[i].resize(55000);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		a.resize(n);
		rep(i,0,n+1)
			rep(j,0,501*(n+1))
				dp[i][j]=-1;
		int sum=0;
		rep(i,0,n)
		{
			cin>>a[i];
			sum+=a[i];
		}
		int sub=sum/2;
		int a=search(0,sub,sub);
		int b=sum-a;
		int diff=abs(b-a);
		cout<<diff<<endl;
	}
	return 0;
}
