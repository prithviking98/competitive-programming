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

int n,m,Time,sc;
vvi a;
vi low,num,s,v;

void dfs(int r)
{
	num[r]=low[r]=++Time;
	v[r]=1;
	s.PUB(r);
	rep(i,0,a[r].size())
	{
		int t=a[r][i];
		if(num[t]==0)
			dfs(t);
		if(v[t])
			low[r]=min(low[r],low[t]);
	}

	if(low[r]==num[r])
	{
		sc++;
		while(1)
		{
			int temp=s.back();
			v[temp]=0;
			s.pop_back();
			if(temp==r)
				break;
		}
	}
}


int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		cin>>n>>m;
		if(n==0)
			break;
		a.assign(n+1,vector<int>(0));
		rep(i,0,m)
		{
			int u,v,t;
			cin>>u>>v>>t;
			if(t==1)
				a[u].PUB(v);
			else
			{
				a[u].PUB(v);
				a[v].PUB(u);
			}
		}
		num.assign(n+1,0);
		low.assign(n+1,0);
		v.assign(n+1,0);
		s.clear();
		Time=0;
		sc=0;
		rep(i,1,n+1)
			if(!num[i])
				dfs(i);
		if(sc==1)
			cout<<1<<endl;
		else
			cout<<0<<endl;
	}

	return 0;
}