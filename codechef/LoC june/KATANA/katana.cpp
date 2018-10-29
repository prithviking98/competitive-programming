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

int n;
vi a(1e6),t(pow(2,ceil(log2(2e6))+1));
vvi Index(1e4+1),Next(1e4+1);

void build(int node,int start,int stop)
{
	if(start==stop)
	{
		t[node]=a[start];
//		trace3(node,start,a[start]);
		return;
	}
	int mid=(start+stop)/2;
	build(left(node),start,mid);
	build(right(node),mid+1,stop);
	t[node]=min(t[left(node)],t[right(node)]);
//	trace2(node,t[node]);
}

int query(int node,int start,int stop,int l,int r)
{
	if(start>r||stop<l)
		return 1e4+1;
	else if(start>=l&&stop<=r)
		return t[node];
	int mid=(start+stop)/2;
	int p1=query(left(node),start,mid,l,r);
	int p2=query(right(node),mid+1,stop,l,r);
	return min(p1,p2);
}

int cut(int l,int r)
{
//	trace2(l,r);
	if(l==r)
		return 1;
	else if(l>r)
		return 0;
	int m=query(0,0,n-1,l,r);
//	trace1(m);
	int f=0;
	for(int b=n-1;b>=1;b/=2)
		while(f+b<Index[m].size()&&Index[m][f+b]<l)
			f+=b;
	if(Index[m][f]<l)
		f++;
//	trace1(Index[m][f]);
	int i=max(l,f==0?l:Next[m][f-1]),j=Index[m][f],count=1;
	while(i<=r)
	{
//		trace3(f,i,j);
		count+=cut(i,j-1);
		i=Next[m][f];
		if(f==Index[m].size()-1&&Index[m][f]<r)
		{
			++f;
			j=r+1;
		}
		else if(f<Index[m].size()-1)
			j=Index[m][++f];
		else
			break;
	}
//	trace3(l,r,count);
	return count;
}


int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	rep(i,0,n)
	{
		cin>>a[i];
		if(i==0||a[i-1]!=a[i])
			Index[a[i]].PUB(i);
	}
	int i=0,j;
	while(i<n)
	{
		j=i;
		while(j<n&&a[j]==a[i])
			++j;
		Next[a[i]].PUB(j);
		i=j;
	}
//	rep(i,1,4)
//	{
//		tracev(Index[i]);
//		tracev(Next[i]);
//	}

	build(0,0,n-1);
	cout<<cut(0,n-1)<<endl;
	return 0;
}
