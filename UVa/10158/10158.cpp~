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
		
	}
}

void Union(vi &p, vi &r, int u, int v)
{
	int x,y;
	x=find(p,u);
	y=find(p,v);
	if(x==y)
		return ;
	if(r[x]>r[y])
	{
		p[y]=x;
		r[x]+=r[y];
	}
	else
	{
		p[x]=y;
		r[y]+=r[x];
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	while(scanf("%d",&n)==1)
	{
	vi p(2*n,-1),r(2*n);
	int c,u,v;
	while(1)
	{
		scanf("%d %d %d\n",&c,&u,&v);
		if(c==0)
			break;
		if(c==1)
		{
			if(find(p,u)==find(p,v+n)||find(p,v)==find(p,u+n))
				cout<<-1<<endl;
			else
			{
				Union(p,r,u,v);
				Union(p,r,u+n,v+n);
			}
		}
		else if(c==2)
		{
			if(find(p,u)==find(p,v)||find(p,u+n)==find(p,v+n))
				cout<<"-1"<<endl;
			else
			{
				Union(p,r,u,v+n);
				Union(p,r,v,u+n);
			}
		}
		else if(c==3)
		{
			if(find(p,u)==find(p,v)||find(p,v+n)==find(p,u+n))
				cout<<1<<endl;
			else
				cout<<0<<endl;
		}
		else if(c==4)
		{
			if(find(p,u+n)==find(p,v)||find(p,u)==find(p,v+n))
				cout<<"1"<<endl;
			else
				cout<<0<<endl;
		}
	}
	}
	return 0;
}
