#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int find(vi &p,int u)
{
	return (p[u]==-1?u:p[u]=find(p,p[u]));
}

void Union(vi &p,vi &r,vi &a,int u,int v)
{
	int x,y;
	x=find(p,u);
	y=find(p,v);
	if(x==y)
		return;
	else if(r[x]>r[y])
	{
		p[y]=x;
		a[x]+=a[y];
	}
	else if(r[y]>r[x])
	{
		p[x]=y;
		a[y]+=a[x];
	}
	else 
	{
		p[x]=y;
		a[y]+=a[x];
		r[y]++;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		vi a(n),p(n,-1),r(n,0);
		rep(i,0,n)
			cin>>a[i];
		while(m--)
		{
			int u,v;
			cin>>u>>v;
			Union(p,r,a,u,v);
		}
		int flag=0;
		rep(i,0,n)
			if(p[i]==-1)
				if(a[i]!=0)
				{
					flag=1;
					break;
				}
		if(flag)
			cout<<"IMPOSSIBLE"<<endl;
		else
			cout<<"POSSIBLE"<<endl;
	}
	return 0;
}
