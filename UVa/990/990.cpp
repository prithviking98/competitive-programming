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

int t,w,n;
int sol,ans;
vi d,v;
int dp[31][1001];
int dpset[31][1001];


int search()
{
	for(int i=1;i<n+1;++i)
	{
		for(int j=1;j<=t;++j)
		{
			if(d[i-1]>j)
			{
				dp[i][j]=dp[i-1][j];
				dpset[i][j]=dpset[i-1][j];
				continue;
			}
			int a=dp[i-1][j];
			int b=dp[i-1][j-d[i-1]]+v[i-1];
			if(a>=b)
			{
				dp[i][j]=a;
				dpset[i][j]=dpset[i-1][j];
			}
			else
			{
				dp[i][j]=b;
				dpset[i][j]=dpset[i-1][j-d[i-1]]|(1<<(i-1));
			}
		}
	}
	return dp[n][t];
}

int main()
{
	ios::sync_with_stdio(0);
	int count=0;
	while(cin>>t>>w)
	{
		count++;
		cin>>n;
		d.resize(n);
		v.resize(n);
		rep(i,0,31)
			rep(j,0,1001)
				dpset[i][j]=0;
		rep(i,0,1001)
			dp[0][i]=0;
		rep(i,0,31)
			dp[i][0]=0;
		rep(i,0,n)
		{
			cin>>d[i]>>v[i];
			d[i]*=3*w;
		}
		ans=search();
		if(count>1)
			cout<<endl;
		cout<<ans<<endl;
		int temp=0;
		rep(i,0,n)
			if(dpset[n][t]&(1<<i))
				temp++;
		cout<<temp<<endl;
		rep(i,0,n)
			if(dpset[n][t]&(1<<i))
				cout<<d[i]/3/w<<" "<<v[i]<<endl;
	}

	return 0;
}
