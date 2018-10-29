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

void dfs(vvi &a,vi &v,int r,vi &ts)
{
	v[r]=1;
	rep(i,0,a[r].size())
	{
		if(v[a[r][i]])
			continue;
		dfs(a,v,a[r][i],ts);
	}
	ts.PUB(r);
}
int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		int n,m;
		cin>>n>>m;
		if(n==0)
			break;
		vvi a(n+1);
		vi v(n+1);
		rep(i,0,m)
		{
			int u,v;
			cin>>u>>v;
			a[u].PUB(v);
		}
		vi ts;
		for(int i=1;i<n+1;++i)
		{
			if(v[i]==1)
				continue;
			dfs(a,v,i,ts);
		}

		rep(i,0,n)
		{
			int t=ts.back();
			ts.POB();
			if(i>0)
				cout<<" ";
			cout<<t;
		}
		cout<<endl;
	}	

	return 0;
}
