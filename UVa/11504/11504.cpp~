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

int n,m,Time,sc;
vvi a,ar;
vi low,num,vis,s;
vector<set<int> > scc;

void dfs(int r)
{
	low[r]=num[r]=++Time;
	vis[r]=1;
	s.PUB(r);
	rep(i,0,a[r].size())
	{
		int v=a[r][i];
		if(num[v]==0)
		{
			dfs(v);
			/*
			if(vis[v]==0)
			{
				trace3(r,v,sc);
			}
			*/
		}
		if(vis[v]==1)
			low[r]=min(low[r],low[v]);
	}

	if(low[r]==num[r])
	{
		sc++;
		scc.PUB(set<int>());
		trace2(r,sc);
		while(1)
		{
			vis[s.back()]=0;
			int t=s.back();
			s.POB();
			scc.back().insert(t);
			if(t==r)
				break;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		trace2(n,m);
		a.assign(n+1,vi(0));
		ar.assign(n+1,vi(0));
		rep(i,0,m)
		{
			int u,v;
			cin>>u>>v;
			a[u].PUB(v);
			ar[v].PUB(u);
		}
		tracevv(a);
		low.assign(n+1,0);
		num.assign(n+1,0);
		vis.assign(n+1,0);
		s.clear();
		scc.clear();
		Time=0;
		sc=0;

		rep(i,1,n+1)
			if(!num[i])
				dfs(i);

		rep(i,0,scc.size())
		{
			auto j=scc[i].begin();
			int flag=0;
			for(;j!=scc[i].end();++j)
			{
				int u=*j;
				rep(k,0,ar[u].size())
					if(scc[i].count(ar[u][k])==0)
					{
						flag=1;
						break;
					}
				if(flag)
					break;
			}
			if(flag)
				sc--;
		}
		cout<<sc<<endl;
	}

	return 0;
}
