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
int ans;

void longest(int r, vvi &a, vvi &ve,int p)
{
	ans=max(ans,p);
	for(int i=0;i<ve[r].size();++i)
	{
		if(ve[r][i]==0)
		{
			ve[r][i]=1;
			int j;
			for(j=0;j<ve[a[r][i]].size();++j)
				if(a[a[r][i]][j]==r)
				{
					ve[a[r][i]][j]=1;
					break;
				}
			longest(a[r][i],a,ve,p+1);
			ve[r][i]=0;
			ve[a[r][i]][j]=0;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	while(true)
	{
		cin>>n>>m;
		if(n==0)
			break;
		vvi a(n);
		vvi ve(n);
		for(int i=0;i<m;++i)
		{
			int u,v;
			cin>>u>>v;
			a[u].push_back(v);
			a[v].push_back(u);
			ve[u].push_back(0);
			ve[v].push_back(0);
		}
		ans=0;
		for(int i=0;i<n;++i)
		{
			/*
			for(int j=0;j<n;++j)
			{
				v[j]=0;
				for(int k=0;k<ve[j].size();++k)
					ve[j][k]=0;
			}*/
			longest(i,a,ve,0);
		}
		cout<<ans<<endl;
	}

	return 0;
}
