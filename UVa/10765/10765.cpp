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
vvi a;
vi low,num,pv,p;
int t,rc=0;

void dfs(int r)
{
	low[r]=num[r]=++t;
	rep(i,0,a[r].size())
	{
		int v=a[r][i];
		if(num[v]==0)
		{
			if(r==0)
				rc++;
			p[v]=r;
			dfs(v);
			if(low[v]>=num[r])
				pv[r]++;
			low[r]=min(low[v],low[r]);
		}
		else
			low[r]=min(low[r],num[v]);
	}
}

bool comp(const pii &a, const pii &b)
{
	if(a.second!=b.second)
		return a.second>b.second;
	else
		return a.first<b.first;
}

int main()
{
	ios::sync_with_stdio(0);
	int T=0;
	while(++T)
	{
		cin>>n>>m;
		if(n==0)
		{
			cout<<endl;
			break;
		}
		a.assign(n,vector<int>(0));
		while(1)
		{
			int u,v;
			cin>>u>>v;
			if(u==-1)
				break;
			a[u].PUB(v);
			a[v].PUB(u);
		}
		num.assign(n,0);
		low.assign(n,0);
		pv.assign(n,1);
		p.assign(n,-1);
		t=0;
		rc=0;
		dfs(0);
		pv[0]=rc;
		vector<pii> s;
		rep(i,0,n)
			s.PUB({i,pv[i]});
		sort(s.begin(),s.end(),comp);

		if(T>1)
			cout<<endl;
		rep(i,0,m)
			cout<<s[i].first<<" "<<s[i].second<<endl;
	}
	return 0;
}
