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

void update(vi &b,int val,int i)
{
	for(;i<=b.size();i+=(i&-i))
		b[i]=b[i]^val;
}

int query(vi &b,int i)
{
	int x=0;
	for(;i>0;i-=(i&-i))
		x=b[i]^x;
	return x;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n+1);
	rep(i,0,n)
		cin>>a[i+1];
	vi b(n+1);
	rep(i,1,n+1)
		update(b,a[i],i);
	vvi all(n+1),m(n+1);
	rep(i,0,n+1)
	{
		all[i].resize(n+1);
		m[i].resize(n+1);
	}
	rep(i,1,n+1)
	{
		rep(j,i,n+1)
		{
			all[i][j]=query(b,i-1)^query(b,j);
			if(i==j)
			{
				m[i][j]=all[i][j];
			}
		}
	}
	rep(k,1,n)
	{
		for(int i=1,j=1;i<n&&j+k<=n;++i,++j)
		{
			m[i][j+k]=max(max(m[i][j+k-1],m[i+1][j+k]),all[i][j+k]);
		}
	}

//	tracem(all);
//	tracem(m);
	int q;
	cin>>q;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
//		trace1((query(b,l-1)^query(b,r)));
		cout<<m[l][r]<<endl;
	}
	return 0;
}
