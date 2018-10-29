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

void update(vi &b,int x,int v)
{
	for(;x<b.size();x+=(x&-x))
		b[x]+=v;
}

void update(vi &b,int l,int r,int v)
{
	update(b,l,v);
	update(b,r+1,-v);
}


int query(vi &b,int a)
{
	int sum=0;
	for(;a>0;a-=(a&-a))
		sum+=b[a];
	return sum;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,u;
		cin>>n>>u;
		vi b(n+1);
		rep(i,0,u)
		{
			int l,r,v;
			cin>>l>>r>>v;
			update(b,l+1,r+1,v);
		}
		int q;
		cin>>q;
		rep(i,0,q)
		{
			int a;
			cin>>a;
			cout<<query(b,a+1)<<endl;
		}
	}
	return 0;
}
