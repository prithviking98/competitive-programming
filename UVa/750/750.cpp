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

int a,b,Count;
vector<string> s;
string sol;
bitset<15> r,dp,dn;

void search(int col)
{
	if(col==8)
	{
		s.PUB(sol);
		return;
	}
	if(col!=b)
		rep(i,0,8)
		{
			if(r[i]||dn[i+col]||dp[i+7-col])
				continue;
			r[i]=dn[i+col]=dp[i+7-col]=1;
			string t="0";
			t[0]+=(i+1);
			sol=sol+t;
			search(col+1);
			sol=sol.substr(0,sol.size()-1);
			r[i]=dn[i+col]=dp[i+7-col]=0;
		}
	else
	{
		if(r[a]||dn[a+col]||dp[a+7-col])
			return;
		else
		{
			r[a]=dn[a+col]=dp[a+7-col]=1;
			string t="0";
			t[0]+=(a+1);
			sol=sol+t;
			search(col+1);
			sol=sol.substr(0,sol.size()-1);
			r[a]=dn[a+col]=dp[a+7-col]=0;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>a>>b;
		a--;
		b--;
		r.reset();
		dp.reset();
		dn.reset();
		s.clear();
		sol.clear();
		search(0);
		sort(s.begin(),s.end());
		cout<<"SOLN       COLUMN"<<endl;
		cout<<" #      ";
		rep(i,0,7)
			cout<<i+1<<" ";
		cout<<8<<endl<<endl;
		rep(i,0,s.size())
		{
			if(i<9)
				cout<<" "<<i+1<<"      ";
			else
				cout<<i+1<<"      ";
			rep(j,0,7)
				cout<<s[i][j]<<" ";
			cout<<s[i][7]<<endl;
		}
		if(T>0)
			cout<<endl;
	}
	return 0;
}
