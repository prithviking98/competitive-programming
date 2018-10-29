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

int r,c,n,m;
vector<string> g;
vi dr={0,1,0,-1};
vi dc={1,0,-1,0};
vvi vis;

int dfs(int r,int c)
{
	if(r<0||c<0||r==n||c==m)
		return 0;
	if(vis[r][c]||g[r][c]=='1')
		return 0;
	int ans=1;
	vis[r][c]=1;
	rep(i,0,4)
		ans+=dfs(r+dr[i],c+dc[i]);
	return ans;
}
	
int main()
{
	ios::sync_with_stdio(0);

	int t;
	cin>>t;
	rep(I,0,t)
	{
		if(I>0)
			cout<<endl;
		int r,c;
//		getchar();
		cin>>r>>c;
		trace2(r,c);
		g.clear();
		string l;
		cin.ignore();
		while(getline(cin,l,'\n'))
		{
			if(l.empty())
				break;
			g.PUB(l);
		}
		tracev(g);
		n=g.size();
		m=g[0].size();
		vis.clear();
		vis.resize(g.size());
		rep(i,0,n)
		{
			vis[i].resize(m);
			rep(j,0,m)
				vis[i][j]=0;
		}
		tracevv(vis);
		cout<<dfs(r-1,c-1)<<endl;
	}
	return 0;
}
