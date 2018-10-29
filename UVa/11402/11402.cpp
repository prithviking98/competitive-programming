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

#define left(i) 2*i+1
#define right(i) 2*i+2

void build(vi &tree,vi &a,int node,int start,int stop)
{
	if(start==stop)
		tree[node]=a[start];
	else
	{
		int mid=(start+stop)/2;
		build(tree,a,left(node),start,mid);
		build(tree,a,right(node),mid+1,stop);
		tree[node]=tree[left(node)]+tree[right(node)];
	}
}

void propogate(vi &tree,vi &lazy,int node,int start,int stop)
{
	if(lazy[node]==0||lazy[node]==1)
	{
		tree[node]=lazy[node]*(stop-start+1);
		if(start<stop)
		{
			lazy[left(node)]=lazy[node];
			lazy[right(node)]=lazy[node];
		}
		lazy[node]=-1;
	}
	else if(lazy[node]==2)
	{
		tree[node]=(stop-start+1)-tree[node];
		if(start<stop)
		{
			if(lazy[left(node)]==-1)
				lazy[left(node)]=lazy[right(node)]=2;
			else if(lazy[left(node)]==0)
				lazy[left(node)]=lazy[right(node)]=1;
			else if(lazy[left(node)]==1)
				lazy[left(node)]=lazy[right(node)]=0;
			else if(lazy[left(node)]==2)
				lazy[left(node)]=lazy[right(node)]=-1;
		}
		lazy[node]=-1;
	}
}

void update(vi &tree, vi &a,vi &lazy,int node, int start,int stop,int l,int r,int u)
{

//	cout<<"in pdate"<<endl;
//	trace3(node,start,stop);
//	trace2(tree[node],u);
	propogate(tree,lazy,node,start,stop);
	if(start>r||stop<l)
		return;
	if(start>=l&&stop<=r)
	{
		if(u==0||u==1)
		{
			tree[node]=u*(stop-start+1);
			if(start==stop)
				a[start]=u;
			else if(start<stop);
				lazy[left(node)]=lazy[right(node)]=u;
		}
		else
		{
			tree[node]=stop-start+1-tree[node];
			if(start<stop)
			{
				if(lazy[left(node)]==-1)
					lazy[left(node)]=lazy[right(node)]=2;
				else if(lazy[left(node)]==0)
					lazy[left(node)]=lazy[right(node)]=1;
				else if(lazy[left(node)]==1)
					lazy[left(node)]=lazy[right(node)]=0;
				else if(lazy[left(node)]==2)
					lazy[left(node)]=lazy[right(node)]=-1;
			}
			else
				a[start]=1-a[start];
		}
	}
	else
	{
		int mid=(start+stop)/2;
		update(tree,a,lazy,left(node),start,mid,l,r,u);
		update(tree,a,lazy,right(node),mid+1,stop,l,r,u);
		tree[node]=tree[left(node)]+tree[right(node)];
	}
//	trace1(tree[node]);
}

int query(vi &tree, vi &a,vi &lazy,int node, int start,int stop,int l,int r)
{
	propogate(tree,lazy,node,start,stop);
	if(start>r||stop<l)
		return 0;
	if(start>=l&&stop<=r)
		return tree[node];
	else
	{
		int mid=(start+stop)/2;
		int p1=query(tree,a,lazy,left(node),start,mid,l,r);
		int p2=query(tree,a,lazy,right(node),mid+1,stop,l,r);
		return p1+p2;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	rep(i,0,T)
	{
		int m;
		cin>>m;
		string s,st;
		int t;
		while(m--)
		{
			cin>>t>>st;
			rep(i,0,t)
				s+=st;
		}
		vi a;
		rep(i,0,s.size())
			a.PUB(s[i]-'0');
		int n=a.size();
		int h=log2(2*n-1);
		vi tree(2*pow(2,h+1));
		vi lazy(tree.size(),-1);
		build(tree,a,0,0,n-1);
//		tracev(tree);
		int q;
		cin>>q;
		int l,r;
		char c;
		cout<<"Case "<<i+1<<":"<<endl;
//		tracev(a);
		int gq=0;
		while(q--)
		{
			cin>>c>>l>>r;
//			trace3(c,l,r);
			if(c=='F')
				update(tree,a,lazy,0,0,n-1,l,r,1);
			else if(c=='E')
				update(tree,a,lazy,0,0,n-1,l,r,0);
			else if(c=='I')
				update(tree,a,lazy,0,0,n-1,l,r,2);
			else if(c=='S')
			{
				int k=query(tree,a,lazy,0,0,n-1,l,r);
				gq++;
				cout<<"Q"<<gq<<": "<<k<<endl;
			}
			//tracev(tree);
		}
	}
	return 0;
}
