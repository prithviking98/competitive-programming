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
	if(p[u]==-1)
		return u;
	else
	{
		p[u]=find(p,p[u]);
		return p[u];
	}
}

void Union(vi &p,vi &rank,int u,int v)
{
	int x=find(p,u);
	int y=find(p,v);
	if(x==y)
		return ;
	if(rank[x]>rank[y])
		p[y]=x;
	else if(rank[x]<rank[y])
		p[x]=y;
	else
	{
		p[x]=y;
		rank[y]++;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	while(cin>>n>>m)
	{
		if(n==0)
			break;
		vi p(n,-1),r(n,0);
		rep(i,0,m)
		{
			int k;
			cin>>k;
			int h;
			cin>>h;
			rep(j,1,k)
			{
				int c;
				cin>>c;
				Union(p,r,h,c);
			}
		}
		int count=0;
		rep(i,0,n)
			if(find(p,0)==find(p,i))
				count++;
		cout<<count<<endl;
	}
}
