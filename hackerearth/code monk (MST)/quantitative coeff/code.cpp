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
{	return x.w<y.w;}

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

vector <edge> mst(vector<edge> e,int v)
{
	vector <edge> mst;
	vi p(v+1,-1),rank(v+1);
	sort(e.begin(),e.end(),comp);
	int count=0,i=0;
	while(i<e.size()&&count<v-1)
	{
		int x,y;
		x=find(p,e[i].s);
		y=find(p,e[i].d);
		if(x!=y)
		{
			Union(p,rank,x,y);
			mst.PUB(e[i]);
			count++;
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
		int m,n;
		cin>>n>>m;
		vector<edge> e(m);
		rep(i,0,m)
			cin>>e[i].s>>e[i].d>>e[i].w;
		vector <edge> mint=mst(e,n);
		ll weight=1;
		rep(i,0,mint.size())
			weight=((weight%(1000000000+7))*mint[i].w)%(1000000000+7);
		cout<<weight;
	}
	return 0;
}
