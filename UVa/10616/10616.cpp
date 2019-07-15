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

vi a;
int d,m,n,q;
vector< vvll > dp;

long long solve(int pos, int sum, int taken)
{
	if(dp[pos][sum][taken]!=-1)
		return dp[pos][sum][taken];
	else if(pos == n)
	{
		if(taken==m && sum == 0)
			return dp[pos][sum][taken]=1;
		else if(taken < m || sum != 0)
			return dp[pos][sum][taken]=0;
	}
	else if(taken==m)
	{
		if(sum==0)
			return dp[pos][sum][taken]=1;
		else
			return dp[pos][sum][taken]=0;
	}
	else
	{
		return dp[pos][sum][taken] = solve(pos+1,sum,taken)+solve(pos+1,((sum+a[pos])%d+d)%d,taken+1);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	int set=0;
	while(n!=0)
	{
		set++;
		a.resize(n);
		rep(i,0,n)
			cin>>a[i];
		dp.resize(n+1);
		cout<<"SET "<<set<<":"<<endl;
		rep(i,0,q)
		{
			cin>>d>>m;
			rep(k,0,n+1)
			{
				dp[k].resize(d);
				rep(j,0,d)
					dp[k][j].assign(m+1,-1);
			}
			cout<<"QUERY "<<i+1<<": "<<solve(0,0,0)<<endl;
		}

		cin>>n>>q;
	}
	return 0;
}
