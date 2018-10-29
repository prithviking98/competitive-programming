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

int sum,maxsum,a[8][8];
bitset<15> r,dp,dn;

void search(int col)
{
	if(col==8)
	{
		if(sum>maxsum)
			maxsum=sum;
		return;
	}
	rep(i,0,8)
	{
		if(r[i]||dn[i+col]||dp[i+7-col])
			continue;
		r[i]=dn[i+col]=dp[i+7-col]=1;
		sum+=a[i][col];
		search(col+1);
		sum-=a[i][col];
		r[i]=dn[i+col]=dp[i+7-col]=0;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	int K;
	cin>>K;
	while(K--)
	{
		r.reset();
		dp.reset();
		dn.reset();
		sum=maxsum=0;
		rep(i,0,8)
			rep(j,0,8)
				cin>>a[i][j];
		search(0);
		int t=maxsum,count=0;
		while(t)
		{
			t/=10;
			count++;
		}
		t=5-count;
		rep(i,0,t)
			cout<<" ";
		cout<<maxsum<<endl;
	}

	return 0;
}
