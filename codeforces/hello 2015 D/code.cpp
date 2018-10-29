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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

struct node
{
	vi a,c,w;
};

struct pqnode
{
	int v,c,w;
	bool operator <(const pqnode &x) const
	{
		return w<x.w;
	}
	bool operator >(const pqnode &x)  const
	{
		return w>x.w;
	}
	bool operator ==(const pqnode &x) const
	{
		return w==x.w;
	}
};

void shortestPath(vector <node> &v,vector <ll> &d,int s)
{
	vector <int> pc(v.size(),-1);
	vector <int> inSPT(v.size(),0);
	priority_queue< pqnode, vector<pqnode>, greater<pqnode> > pq;
	pqnode temp;
	temp.v=s;
	temp.w=0;
	temp.c=-1;
	pq.push(temp);
	while(!pq.empty())
	{
		temp=pq.top();
		pq.pop();
		int u=temp.v;
		int pct=temp.c;
		int dt=temp.w;
		if(inSPT[u]==2||(inSPT[u]==1&&temp.c==pc[u]))
			continue;
		inSPT[u]++;
		//trace1(u);
		rep(i,0,v[u].a.size())
		{
			int dest,w,c;
			dest=v[u].a[i];
			w=v[u].w[i];
			c=v[u].c[i];
			//trace3(dest,w,c);
			if(c!=pct)
			{
				if(d[dest]>dt+w)
				{
					d[dest]=dt+w;
					pc[dest]=c;
					temp.v=dest;
					temp.w=d[dest];
					temp.c=c;
					pq.push(temp);
				}
				else
				{
					temp.v=dest;
					temp.w=dt+w;
					temp.c=c;
					pq.push(temp);
				}
			}
		}
	}
}


int main()
{
	ios::sync_with_stdio(0);
	int n,m,c,s,q;
	cin>>n>>m>>c;
	vector<node> v(n+1);
	int u,dest,col,w;
	rep(i,0,m)
	{
		cin>>u>>dest>>w>>col;
		v[u].a.PUB(dest);
		v[u].w.PUB(w);
		v[u].c.PUB(col);
	}
	cin>>s>>q;
	vector <ll> d(n+1,LLONG_MAX);
	d[s]=0;
	shortestPath(v,d,s);
	rep(i,0,q)
	{
		cin>>dest;
		if(d[dest]==LLONG_MAX)
			cout<<-1<<endl;
		else
			cout<<d[dest]<<endl;;
	}

	return 0;
}
