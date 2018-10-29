#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

//#define TRACE
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
vi p,w,mw;
int g,sol;
vvi dp(1001);

int search(int index,int item,int rem)
{
	rep(i,0,n)
	{
		rep(j,0,rem+1)
		{
			if(i==0)
			{
				dp[i][j]=j>=w[i]?p[i]:0;
				continue;
			}
			dp[i][j]=dp[i-1][j];
			if(w[i]<=j)
				dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+p[i]);
			trace4(index,i,j,dp[i][j]);
		}
	}
	return dp[n-1][rem];
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	rep(i,0,1001)
		dp[i].resize(31);
	while(t--)
	{
		cin>>n;
		trace1(n);
		p.resize(n);
		w.resize(n);
		rep(i,0,n)
			cin>>p[i]>>w[i];
		cin>>g;
		mw.resize(g);
		rep(i,0,g)
			cin>>mw[i];
		int sum=0;
		rep(i,0,g)
		{
			rep(j,0,n+1)
				rep(k,0,mw[i]+1)
					dp[j][k]=-1;
			sum+=search(i,0,mw[i]);
		}
		cout<<sum<<endl;
	}
	return 0;
}
