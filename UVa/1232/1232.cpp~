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

#define left(n) 2*n+1
#define right(n) 2*n+2

int olap(vi &t,vi &uni,int node,int start,int stop,int l,int r,int h)
{
	if(stop<l||start>r)
		return 0;
	else if(stop<=r&&start>=l)
	{
		if(t[node]<=h)
		{
			t[node]=h;
			uni[node]=1;
			return stop-start+1;
		}
		else if(t[node]>h&&uni[node])
			return 0;
		else
		{
			int mid=(start+stop)/2;
			int olap1=olap(t,uni,left(node),start,mid,l,r,h);
			int olap2=olap(t,uni,right(node),mid+1,stop,l,r,h);
			return olap1+olap2;
		}
	}
	else
	{
		if(t[node]<=h&&uni[node])
		{
			uni[node]=0;
			if(start<stop)
			{
				t[left(node)]=t[node];
				uni[left(node)]=1;
				t[right(node)]=t[node];
				uni[right(node)]=1;
			}
			t[node]=h;
			int mid=(start+stop)/2;
			int olap1=olap(t,uni,left(node),start,mid,l,r,h);
			int olap2=olap(t,uni,right(node),mid+1,stop,l,r,h);
			return olap1+olap2;
		}
		else if(t[node]>h&&uni[node])
			return 0;
		else if(!uni[node])
		{
			if(h>t[node])
				t[node]=h;
			int mid=(start+stop)/2;
			int olap1=olap(t,uni,left(node),start,mid,l,r,h);
			int olap2=olap(t,uni,right(node),mid+1,stop,l,r,h);
			return olap1+olap2;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int c;
	cin>>c;
	while(c--)
	{
		int leaf=100001;
		int total=2*leaf-1;
		int height=log2(total);
		int power=2*pow(2,height+1);	
		vi tree(power),uni(power,1);
		int n;
		cin >>n;
		if(n==0)
			break;
		int o=0;
		while(n--)
		{
			int l,r,h;
			cin>>l>>r>>h;
			o+=olap(tree,uni,0,0,99999,l-1,r-2,h);
		}
		cout<<o<<endl;
	}
		

	return 0;
}
