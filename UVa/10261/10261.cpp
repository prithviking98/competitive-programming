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

vector<int> a,sum;
int length,n;
vector<vector<int> > dp,side;

int solve(int p, int l1)
{
	if(dp[p][l1]!=-1)
		return dp[p][l1];
	else if(a[p]+l1>length&&a[p]+sum[p]-l1>length)
	{
		trace2(p,l1);
		side[p][l1]=-1;
		dp[p][l1]=0;
		return 0;
	}
	else if(a[p]+l1>length)
	{
		side[p][l1]=1;
		return dp[p][l1]=solve(p+1,l1)+1;
	}
	else if(a[p]+sum[p]-l1>length)
	{
		side[p][l1]=0;
		return dp[p][l1]=solve(p+1,l1+a[p])+1;
	}
	else
	{
		int port,star;
		port = solve(p+1,l1+a[p])+1;
		star = solve(p+1,l1)+1;
		if(port>star)
		{
			side[p][l1]=0;
			dp[p][l1]=port;
		}
		else
		{
			side[p][l1]=1;
			dp[p][l1]=star;
		}
		return dp[p][l1];
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>length;
		length*=100;
		trace1(length);
		a.clear();
		dp.clear();
		sum.clear();
		side.clear();
		sum.push_back(0);
		int temp;
		cin>>temp;
		while(temp!=0)
		{
			a.push_back(temp);
			sum.push_back(sum.back()+a.back());
			cin>>temp;
		}
		tracev(a);
		tracev(sum);
		n=a.size();
		dp.resize(n+1);
		side.resize(n+1);
		for(int i=0;i<n+1;++i)
		{
			dp[i].resize(length+1);
			side[i].resize(length+1);
			for(int j=0;j<dp[i].size();++j)
				dp[i][j]=-1;
		}
		for(int i=0;i<dp[n].size();++i)
		{
			dp[n][i]=0;
			side[n][i]=-1;
		}
		cout<<solve(0,0)<<endl;
		int i=0,j=0;
		while(side[i][j]!=-1)
		{
			if(side[i][j]==0)
			{
				cout<<"port"<<endl;
				j=j+a[i];
			}
			else
				cout<<"starboard"<<endl;
			i=i+1;
		}

		if(T>0)
			cout<<endl;
	}
	return 0;
}
