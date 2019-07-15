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

int a,b,solnum;
vi r(8),dp(15),dn(15),ans(8);

void search(int c)
{
	if(c==8)
	{
		//print solution
		if(solnum<10)
			cout<<" "<<++solnum<<"      ";
		else
			cout<<++solnum<<"      ";
		rep(i,0,7)
			cout<<ans[i]<<" ";
		cout<<ans[7]<<endl;
		return;
	}
	else if(c==b)
	{
		search(c+1);
		return;
	}
	for(int i=0;i<8;++i)
	{
		if(r[i]||dn[i+c]||dp[i+7-c])
			continue;
		ans[c]=i+1;
		r[i]=dn[i+c]=dp[i+7-c]=1;
		search(c+1);
		r[i]=dn[i+c]=dp[i+7-c]=0;
	}
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	for(int I=1;I<=T;++I)
	{
		cout<<"SOLN       COLUMN"<<endl;
		cout<<" #      ";
		rep(i,1,8)
			cout<<i<<" ";
		cout<<8<<endl<<endl;;
		cin>>a>>b;
		a--;
		b--;
		r.assign(8,0);
		dp.assign(15,0);
		dn.assign(15,0);
		r[a]=1;
		dp[a+(7-b)]=1;
		dn[a+b]=1;
		ans[b]=a+1;
		solnum=0;
		search(0);
		cout<<endl;

	}
	return 0;
}
