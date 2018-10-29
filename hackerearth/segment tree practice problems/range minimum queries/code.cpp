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

void build(vi &t,vi &a,int node, int start,int end)
{
	if(start==end)
	{
		t.at(node)=a[start];
	}
	else 
	{
		int mid=(start+end)/2;
		build(t,a,2*node+1,start,mid);
		build(t,a,2*node+2,mid+1,end);
		if(t[node*2+1]<t[node*2+2])
			t[node]=t[node*2+1];
		else
			t[node]=t[node*2+2];
	}
}

void update(vi &t,int node,int start,int end, int index,int val)
{
	if(start==end)
	{
		t[node]=val;
	}
	else
	{
		int mid=(start+end)/2;
		if(start<=index&&index<=mid)
			update(t,2*node+1,start,mid,index,val);
		else
			update(t,2*node+2,mid+1,end,index,val);
		if(t[node*2+1]<t[node*2+2])
			t[node]=t[node*2+1];
		else
			t[node]=t[node*2+2];
	}
}

int minquery(const vi &t,int node, int start,int end,int l,int r)
{
		//trace4(start,end,l,r);
		//trace2(node,t.size());
	if(start>r||end<l)
		return INT_MAX;
	else if(start>=l&&end<=r)
	{
		//trace4(start,end,l,r);
		//trace2(node,t.size());
		return t[node];
	}
	else
	{
		int mid=(start+end)/2;
		int ql=minquery(t,node*2+1,start,mid,l,r);
		int qr=minquery(t,node*2+2,mid+1,end,l,r);
		if(ql<qr)
			return ql;
		else 
			return qr;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n,q;
	cin>>n>>q;
	int h=ceil(log2(n));
	vi a(n),t(pow(2,h+1)-1);
	rep(i,0,n)
		cin>>a[i];
	build(t,a,0,0,n-1);
	//trace2(n,q);
	while(q--)
	{
		//trace1(q);
		char c;
		int l,r;
		cin>>c>>l>>r;
		//trace3(c,l,r);
		if(c=='u')
		{
			a[l-1]=r;
			update(t,0,0,n-1,l-1,r);
		}
		else
			cout<<minquery(t,0,0,n-1,l-1,r-1)<<endl;
	}
	return 0;
}
