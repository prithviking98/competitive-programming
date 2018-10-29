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

inline int P(int i)
{
	if(i==0)
		return -1;
	else
		return (i-1)/2;
}

inline int L(int i)
{
	return 2*i+1;
}

inline int R(int i)
{
	return 2*i+2;
}

void build(vi &t,vi &a,int node,int start,int stop)
{
	if(start==stop)
		a[start]=node;
	else
	{
		int mid=(start+stop)/2;
		build(t,a,L(node),start,mid);
		build(t,a,R(node),mid+1,stop);
	}
}

void update(vi &t,vi &a,int node,int start,int stop,int l,int r,int w)
{
	if(start>=l&&stop<=r)
	{
		if(t[node]==0)
			t[node]=w;
		else
		{
			if(start==stop)
			{
				if(node==a[t[node]])
					t[node]=w;
			}
			else if(start<stop)
			{
				int mid=(start+stop)/2;
				update(t,a,L(node),start,mid,start,mid,t[node]);
				update(t,a,R(node),mid+1,stop,mid+1,stop,t[node]);
				t[node]=w;
			}
		}
	}
	else if(start>r||stop<l)
		return;
	else
	{
		int mid=(start+stop)/2;
		update(t,a,L(node),start,mid,l,r,w);
		update(t,a,R(node),mid+1,stop,l,r,w);
	}
}

int query(vi &t,int node,int i)
{
	if(node==-1)
		return 0;
	else if(t[node]!=0&&t[node]!=i)
		return t[node];
	else
		return query(t,P(node),i);
}

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vi a(n+1);
	int h=log2(2*n+1);
	vi t((int)pow(2,h+1)-1);
	build(t,a,0,1,n);
	int l,r,w;
	while(m--)
	{
		cin>>l>>r>>w;
		update(t,a,0,1,n,l,r,w);
	}
	rep(i,1,n+1)
		cout<<query(t,a[i],i)<<" ";
	cout<<endl;
	return 0;
}
