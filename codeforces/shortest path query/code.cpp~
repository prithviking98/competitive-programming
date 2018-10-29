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
	int c,w,d;
};

struct node
{
	vector <edge> a;
};

void dijkstra(vector<node> v, int n, int source, vi &p, vi &pc, vector<ll> &d)
{
	vector<bool> inSPT(n+1,false);
	vector< set<pi> > path(n+1);
	priority_queue <pi,vector<pi>,greater<pi> > pq;
	pq.push(make_pair(0,source));
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
			int col=(*i).c;
			int w=(*i).w;
			if(!inSPT[v])
			{
				set<pi>::iterator j=path[u].begin();
				for(;j!=path[u].end();++j)
				{
					if(col!=(*j).second)
					{
						path[v].insert(make_pair(w+d[u],col));
						if(d[v]>d[u]+w)
						{
							d[v]=d[u]+w;
							pc[v]=col;
							p[v]=u;
							pq.push(make_pair(d[v],v));
						}
					}
				}
			}
		}
	}
}
						

int main()
{
	ios::sync_with_stdio(0);
	int n,m,c;
	cin>>n>>m>>c;
	vector <node> v(n+1);
	rep(i,0,m)
	{
		int u,d,w,c;
		cin>>u>>d>>w>>c;
		edge e={c,w,d};
		v[u].a.PUB(e);
	}
	int s,q;
	cin>>s>>q;
	vi p(n+1,-1),pc(n+1,-1);
	vector<ll> d(n+1,LONG_MAX);
	d[s]=0;
	dijkstra(v,n,s,p,pc,d);
	while(q--)
	{
		int t;
		cin>>t;
		if(d[t]!=LONG_MAX)
			cout<<d[t]<<endl;
		else
			cout<<-1<<endl;
	}
	return 0;
}
