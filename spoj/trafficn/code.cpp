#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct edge
{
	int d,w;
};

struct node
{
	vector<edge> a;
};

void dijkstra(vector<node> v,int n, int s, vi &d)
{
	vector <bool> inSPT(n+1,false);
	vector <int> p(n+1,-1);
	priority_queue <pi, vector <pi> , greater <pi> > pq;
	pq.push(make_pair(0,s));
	while(!pq.empty())
	{
		int u=pq.top().second;
		pq.pop();
		if(inSPT[u])
			continue;
		inSPT[u]=true;
		vector<edge>::iterator i=v[u].a.begin();
		for(;i!=v[u].a.end();++i)
		{
			int v=(*i).d;
			int w=(*i).w;
			if(!inSPT[v]&&d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				p[v]=u;
				pq.push(make_pair(d[v],v));
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	int f;
	cin>>f;
	while(f--)
	{
		int n,m,k,s,t;
		cin>>n>>m>>k>>s>>t;
		vector<node> v(n+1),rg(n+1);
		rep(i,0,m)
		{
			int u,d,w;
			cin>>u>>d>>w;
			edge e={d,w};
			v[u].a.PUB(e);
			e.d=u;
			e.w=w;
			rg[d].a.PUB(e);
		}
		vi d(n+1,INT_MAX),rd(n+1,INT_MAX);
		d[s]=0;
		rd[t]=0;
		dijkstra(v,n,s,d);
		dijkstra(rg,n,t,rd);
		int mind=d[t];
		while(k--)
		{
			int u,q,w;
			cin>>u>>q>>w;
			int nd;
			if(d[u]!=INT_MAX&&rd[q]!=INT_MAX&&(d[q]==INT_MAX||rd[u]==INT_MAX))
				nd=d[u]+w+rd[q];
			else if(d[q]!=INT_MAX&&rd[u]!=INT_MAX&&(d[u]==INT_MAX||rd[q]==INT_MAX))
				nd=d[q]+w+rd[u];
			else
				nd=min(d[q]+w+rd[u],d[u]+w+rd[q]);
			if(mind>nd)
				mind=nd;
		}
		if(mind==INT_MAX)
			cout<<-1;
		else
		cout<<mind<<endl;;
	}
	return 0;
}
