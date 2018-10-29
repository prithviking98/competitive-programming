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

int n,m;
vector<vector<int> > yey,blo;
vector<vector<int> >  dp;

int search(int r,int c)
{
	if(dp[r][c]!=-1)
		return dp[r][c];
	if(r==0&&c==0)
		return dp[r][c]=max(blo[r][c],yey[r][c]);
	if(r==0)
		return dp[r][c]=max(yey[r][c],blo[r][c]+search(r,c-1));
	if(c==0)
		return dp[r][c]=max(yey[r][c]+search(r-1,c),blo[r][c]);
	return dp[r][c]=max(blo[r][c]+search(r,c-1),yey[r][c]+search(r-1,c));
}

int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		cin>>n>>m;
		if(n==0)
			break;
		yey.resize(n);
		blo.resize(n);
		dp.resize(n);
		rep(i,0,n)
		{
			yey[i].resize(m);
			blo[i].resize(m);
			dp[i].resize(m);
			rep(j,0,m)
				dp[i][j]=-1;
		}
		rep(i,0,n)
			rep(j,0,m)
			{
				cin>>yey[i][j];
				if(j>0)
					yey[i][j]+=yey[i][j-1];
			}
		rep(i,0,n)
			rep(j,0,m)
			{
				cin>>blo[i][j];
				if(i>0)
					blo[i][j]+=blo[i-1][j];
			}
		cout<<search(n-1,m-1)<<endl;
	}
	return 0;
}
