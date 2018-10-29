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
const int M=1e9+7;
int n,m;
vi c,v,f;
vvi a,ra;

void dfs(int root)
{
	if(v[root])
		return;
	trace1(root);
	v[root]=1;
	rep(i,0,a[root].size())
		dfs(a[root][i]);
	f.PUB(root);
}

void dfs(int root,int &t,int &count)
{
	if(v[root])
		return;
	v[root]=1;
	rep(i,0,ra[root].size())
	{
		if(v[ra[root][i]])
			continue;
		int k=ra[root][i];
		if(c[k]<t)
		{
			t=c[k];
			count=1;
		}
		else if(c[k]==t)
			count++;
		dfs(ra[root][i],t,count);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	c.resize(n+1);
	v.resize(n+1);
	rep(i,1,n+1)
	{
		v[i]=0;
		cin>>c[i];
	}
	tracev(c);
	cin>>m;
	a.resize(n+1);
	ra.resize(n+1);
	rep(i,0,m)
	{
		int u,v;
		cin>>u>>v;
		trace2(u,v);
		a[u].PUB(v);
		ra[v].PUB(u);
	}
	tracevv(a);
	tracevv(ra);
	rep(i,1,n+1)
		dfs(i);
	tracev(f);
	rep(i,1,n+1)
		v[i]=0;
	ll mincost=0,ways=1;
	for(int i=f.size()-1;i>=0;--i)
	{
		trace3(i,f[i],v[i]);
		if(v[f[i]])
			continue;
		int t=c[f[i]],count=1;
		dfs(f[i],t,count);
		mincost+=t;
		ways=((ll)ways*(count%M))%M;
	}
	cout<<mincost<<" "<<ways<<endl;

	return 0;
}
