#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

struct node
{
	vi adj,type;
};
struct edge
{
	int s,d,t;
};

int find(vi &p,int x)
{
	if(p[x]==-1)
		return x;
	else 
	{
		p[x]=find(p,p[x]);
		return p[x];
	}
}

void Union(vi &p,vi &rank,int x, int y)
{
	if(rank[x]>rank[y])
		p[y]=x;
	else if(rank[y]>rank[x])
		p[x]=y;
	else
	{
		p[x]=y;
		rank[y]++;
	}
}

int ncc(const vector <edge> e,int v, int t)
{
	vi p(v+1,-1),rank(v+1);
	int count=v;
	//cout<<"NCC\n";
	rep(i,1,e.size())
	{
	//	cout<<"s d "<<e[i].s<<" "<<e[i].d<<" t="<<e[i].t<<endl;
		if(e[i].t==3||e[i].t==t)
		{
			int x,y;
			x=find(p,e[i].s);
			y=find(p,e[i].d);
	//		cout<<"x y "<<x<<" "<<y<<endl;
			if(x!=y)
			{
				Union(p,rank,x,y);
				--count;
			}
		}
	}
	return count;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vector <node> v(n+1);
	vector <edge> e(m+1);
	rep(i,1,m+1)
	{
		int s,d,t;
		cin>>s>>d>>t;
		e[i].s=s;
		e[i].d=d;
		e[i].t=t;
		v[s].adj.PUB(d);
		v[s].type.PUB(t);
		v[d].adj.PUB(s);
		v[d].type.PUB(t);
	}
	//cout<<ncc(e,n,1)<<" "<<ncc(e,n,2);
	if(ncc(e,n,1)==1&&ncc(e,n,2)==1)
	{
		int c=ncc(e,n,0);
		int edges=n-c+(c-1)*2;
		cout<<m-edges;
	}
	else
		cout<<-1;

	return 0;
}
