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
vvi a,w;
vi d,p;

void dijkstra(int s)
{
	vi in(n+1,0);
	in[1]=0;
	priority_queue<pii, vector<pii> ,greater<pii> > q;
	q.push({0,1});
	while(!q.empty())
	{
		pii t=q.top();
		q.pop();
		int r=t.second;
		int dc=t.first;
		if(in[r])
			continue;
		in[r]=1;
		rep(i,0,a[r].size())
		{
			int cur=a[r][i];
			if(d[cur]==INT_MAX|| d[cur]>dc+w[r][i])
			{
				d[cur]=dc+w[r][i];
				p[cur]=r;
				q.push({dc+w[r][i],cur});
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int Case=0;
	while(1)
	{
		Case++;
		cin>>n>>m;
		if(n==0)
			break;
		a.clear();
		w.clear();
		d.clear();
		a.resize(n+1);
		w.resize(n+1);
		d.resize(n+1);
		p.resize(n+1);
		rep(i,0,m)
		{
			int u,v,l;
			cin>>u>>v>>l;
			a[u].push_back(v);
			a[v].PUB(u);
			w[u].PUB(l);
			w[v].push_back(l);
		}
		rep(i,1,n+1)
		{
			d[i]=INT_MAX;
			p[i]=-1;
		}
		d[1]=0;
		dijkstra(1);
		int index=1,md=0;
		rep(i,1,n+1)
			if(d[i]>md)
			{
				md=d[i];
				index=i;
			}
		int u,v;
		u=v=0;
		double ld;
		ld=0;
		rep(i,1,n+1)
		{
			rep(j,0,a[i].size())
			{
				if(p[i]==a[i][j]||p[a[i][j]]==i)
					continue;
				int x,y;
				x=i; y=a[i][j];
				if(d[x]<d[y])
				{
					x=y;
					y=i;
				}
				if(ld<(d[y]+w[i][j]+d[x])/2.0)
				{
					ld=(d[y]+w[i][j]+d[x])/2.0;
					u=min(x,y);
					v=max(x,y);
				}
			}
		}
		if(Case>1)
			printf("\n");
		printf("System #%d\n",Case);
		if(ld<=d[index])
		{
			//last domino to fall is key domino index
			printf("The last domino falls after %0.1f seconds, at key domino %d.\n",(double)d[index],index);
		}
		else 
		{
			printf("The last domino falls after %0.1f seconds, between key dominoes %d and %d.\n",ld,u,v);
		}

	}
	printf("\n");

	return 0;
}
