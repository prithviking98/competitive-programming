#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

//#define TRACE
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

#define left(i) 2*i+1
#define right(i) 2*i+2

int n,ti;
vvi a;
vi dist,el,d,tree;

void dfs(int root,int curdist)
{
	el.PUB(root);
	d[root]=++ti;
	rep(i,0,a[root].size())
	{
		int v=a[root][i];
		dist[v]=curdist+1;
		dfs(v,curdist+1);
		++ti;
		el.PUB(root);
	}
}

void build(int node,int start,int stop)
{
	if(start==stop)
	{
		tree[node]=el[start];
		return ;
	}
	int mid=(start+stop)/2;
	build(left(node),start,mid);
	build(right(node),mid+1,stop);
	tree[node]=dist[tree[left(node)]]>dist[tree[right(node)]]?tree[right(node)]:tree[left(node)];
}

int query(int node,int start,int stop,int l,int r)
{
	if(l>stop||r<start)
		return 0;
	else if(start>=l&&stop<=r)
		return tree[node];
	int mid=(start+stop)/2;
	int p1=query(left(node),start,mid,l,r);
	int p2=query(right(node),mid+1,stop,l,r);
	return dist[p1]>dist[p2]?p2:p1;
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	rep(I,0,T)
	{
		cin>>n;
		a.assign(n+1,vi(0));
		rep(i,1,n+1)
		{
			int k;
			cin>>k;
			rep(j,0,k)
			{
				int v;
				cin>>v;
				a[i].PUB(v);
			}
		}
		tracevv(a);
		el.clear();
		dist.assign(n+1,0);
		d.assign(n+1,0);
		dist[0]=INT_MAX;
		ti=-1;
		dfs(1,0);
		tracev(el);
		tracev(d);
		tracev(dist);
		int h=log2(2*el.size()-1);
		tree.assign(pow(2,h+2),0);
		build(0,0,el.size()-1);
		tracev(tree);
		int q;
		cin>>q;
		cout<<"Case "<<I+1<<":"<<endl;
		rep(i,0,q)
		{
			int u,v;
			cin>>u>>v;
			cout<<query(0,0,el.size()-1,min(d[u],d[v]),max(d[u],d[v]))<<endl;
		}
	}
	return 0;
}

