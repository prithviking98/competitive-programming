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

int c=0,n;
bitset<30> r,dp,dn;

void search(int col)
{
	if(col==n)
	{
		c++;
		return;
	}
	rep(i,0,n)
	{
		if(r[i]||dn[i+col]||dp[i+n-1-col])
			continue;
		r[i]=dn[i+col]=dp[i+n-1-col]=1;
		search(col+1);
		r[i]=dn[i+col]=dp[i+n-1-col]=0;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	rep(i,1,15)
	{
		n=i;
		r.reset();
		dp.reset();
		dn.reset();
		c=0;
		search(0);
		trace2(n,c);
	}

	return 0;
}
