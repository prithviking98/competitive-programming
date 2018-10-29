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

int n,m;
vi a(1e5+5),p(1e5+5,-1),r(1e5+5),c(1e5+5),rot(1e5+5,1),f(1e5+5),ft(1e5+5);

int find(int o,int u)
{
	if(f[u]&&u!=o)
	{
		c[o]=c[o]^1;
		ft[o]=ft[o]^1;
	}
	if(p[u]==-1)
		return u;
	ft[p[u]]=0;
	int k=find(o,p[u]);
	if(u!=o)
		return k;
	else if(f[u]&&ft[o]==1)
	{
		f[u]=0;
		return p[u]=k;
	}
	else if(f[u]&&ft[o]==0)
	{
		return p[u]=k;
	}
	else if(f[u]==0&&ft[o]==1)
	{
		f[u]=1;
		return p[u]=k;
	}
	else if(f[u]==0&&ft[o]==0)
	{
		return p[u]=k;
	}
}

void Union(int u,int v)
{
	int x,y;
	ft[u]=0;
	ft[v]=0;
	x=find(u,u);
	y=find(v,v);
	if(x==y)
	{
		if(c[u]==c[v])
			rot[x]=0;
		return;
	}
	else if(r[x]>r[y])
	{
		if(c[u]==c[v])
		{
			c[y]=c[y]^1;
			f[y]=1;
		}
		p[y]=x;
		if(rot[y]==0)
			rot[x]=0;
	}
	else if(r[y]>=r[x])
	{
		if(c[u]==c[v])
		{
			c[x]=c[x]^1;
			f[x]=1;
		}
		p[x]=y;
		if(r[y]==r[x])
			r[y]++;
		if(rot[x]==0)
			rot[y]=0;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,n+1)
		cin>>a[i];	
	int t;
	rep(i,0,m)
	{
		cin>>t;
		if(t==1)
		{
			int x,teeth;
			cin>>x>>teeth;
			a[x]=teeth;
		}
		else if(t==2)
		{
			int x,y;
			cin>>x>>y;
			trace3(t,x,y);
			if(x!=y)
				Union(x,y);
		}
		else if(t==3)
		{
			int x,y,v;
			cin>>x>>y>>v;
			int px,py;
			ft[x]=0;
			ft[y]=0;
			px=find(x,x);
			py=find(y,y);
			if(px!=py)
				cout<<0<<endl;
			else if(px==py&&rot[px])
			{
				ll num,den;
				num=(ll)v*a[x];
				den=a[y];
				ll gcd=__gcd(num,den);
				num/=gcd;
				den/=gcd;
				trace4(x,y,c[x],c[y]);
				if(c[x]!=c[y])
					cout<<"-"<<num<<"/"<<den<<endl;
				else
					cout<<num<<"/"<<den<<endl;
			}
			else
				cout<<0<<endl;
		}
		tracea(f,n+1);
		tracea(c,n+1);
	}
	return 0;
}
