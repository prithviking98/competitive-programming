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

inline int left(int i)
{ 	return 2*i+1;}
inline int right(int i)
{	return 2*i+2;}
inline int parent(int i)
{	return (i-1)/2;}

void build(vector<ll> &t,const vi &a,int node,int start,int stop)
{
	if(start==stop)
		t[node]=a[start];
	else
	{
		int mid=(start+stop)/2;
		build(t,a,left(node),start,mid);
		build(t,a,right(node),mid+1,stop);
		t[node]=t[left(node)]+t[right(node)];
	}
}

ll query(const vector<ll> &t,const vi &a,int node,int start,int stop,int l,int r)
{
	if(start>=l&&stop<=r)
		return t[node];
	else if(start>r||stop<l)
		return 0;
	else
	{
		int mid=(start+stop)/2;
		ll p1,p2;
		p1=query(t,a,left(node),start,mid,l,r);
		p2=query(t,a,right(node),mid+1,stop,l,r);
		return p1+p2;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int h=ceil(log2(2*n-1));
	vector<ll> t(pow(2,h+1)+1);
	build(t,a,0,0,n-1);
	vector <ll> p(n);
	int s,f,len;
	cin>>s>>f;
	len=f-s;
	rep(i,0,n)
	{
		int l,r;
		l=i;
		r=(i+len-1)%n;
		if(r>=l)
			p[i]=query(t,a,0,0,n-1,l,r);
		else
			p[i]=query(t,a,0,0,n-1,l,n-1)+query(t,a,0,0,n-1,0,r);
	}
	ll max=-1;
	int index,time;
	rep(i,0,n)
	{
		if(p[i]>max)
		{
			index=i;
			max=p[i];
			time=s-i;
			if(time<=0)
				time+=n;
		}
		if(p[i]==max)
		{
			int temp=s-i;
			if(temp<=0)
				temp+=n;
			if(temp<time)
				time=temp;
		}
	}
	cout<<time<<endl;
	return 0;
}
