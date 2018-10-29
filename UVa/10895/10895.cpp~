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

int main()
{
	ios::sync_with_stdio(0);
	int m,n;
	while(cin>>m>>n)
	{
	vvi a(m+1);
	vvi ai(m+1);
	vvi at(n+1),ati(n+1);
	rep(i,1,m+1)
	{
		int t;
		cin>>t;
		a[i].resize(t);
		ai[i].resize(t);
		rep(j,0,t)
			cin>>ai[i][j];
		rep(j,0,t)
			cin>>a[i][j];
		rep(j,0,t)
		{
			ati[ai[i][j]].PUB(i);
			at[ai[i][j]].PUB(a[i][j]);
		}
	}
	cout<<n<<" "<<m<<endl;
	rep(i,1,n+1)
	{
		cout<<at[i].size();
		if(at[i].size()==0)
		{
			cout<<endl<<endl;
			continue;
		}
		rep(j,0,at[i].size())
			cout<<" "<<ati[i][j];
		cout<<endl;
		cout<<at[i][0];
		rep(j,1,at[i].size())
			cout<<" "<<at[i][j];
		cout<<endl;
	}
	}
	return 0;
}
