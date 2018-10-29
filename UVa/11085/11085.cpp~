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

vvi sol;
vi row(8),a(8);
bitset<15> r(0),dn(0),dp(0);

void search(int col)
{
	if(col==8)
	{
		sol.PUB(row);
		return;
	}
	rep(i,0,8)
	{
		if(r[i]||dn[i+col]||dp[i+7-col])
			continue;
		r[i]=dn[i+col]=dp[i+7-col]=1;
		row[col]=i;
		search(col+1);
		r[i]=dn[i+col]=dp[i+7-col]=0;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int t=0;
	search(0);
//	trace1(sol.size());
//	tracem(sol);
	while(cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4]>>a[5]>>a[6]>>a[7])
	{
		rep(i,0,8)
			a[i]--;
//		tracev(a);
		t++;
		int minmoves=INT_MAX;
		rep(i,0,sol.size())
		{
			int moves=0;
			rep(j,0,8)
				if(sol[i][j]!=a[j])
					moves++;
//			trace1(moves);
			minmoves=min(moves,minmoves);
		}
		cout<<"Case "<<t<<": "<<minmoves<<endl;
	}
	return 0;
}
