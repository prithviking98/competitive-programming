#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

struct edge
{
	int s,d,w;
};
bool comp(edge x,edge y)
{
	return x.w>y.w;
}

int find(vi &p, int x)
{
	if(p[x]==-1)
		return x;
	else
	{
		p[x]=find(p,p[x]);
		return p[x];
	}
}

void Union(vi &p, vi &rank, int x, int y)
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

vector <edge> mst(vector <edge> e,int v)
{
	vector <edge> mst;
	sort(e.begin(),e.end(),comp);
	vi p(v+1,-1),rank(v+1);
	int count=0,i=0;
	while(i<e.size()&&count<v-1)
	{
		int x,y;
		x=find(p,e[i].s);
		y=find(p,e[i].d);
		if(x!=y)
		{
			Union(p,rank,x,y);
			count++;
			edge t;
			t.s=e[i].s;
			t.d=e[i].d;
			t.w=e[i].w;
			mst.PUB(t);
		}
		i++;
	}
	return mst;
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
		vector<edge> e(m);
		rep(i,0,m)
			cin>>e[i].s>>e[i].d>>e[i].w;
		vector <edge> t=mst(e,n);
		int weight=0;
		rep(i,0,t.size())
			weight+=t[i].w;
		cout<<weight<<endl;
	}
	return 0;
}
