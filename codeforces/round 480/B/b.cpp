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
	int n,k;
	cin>>n>>k;
//	trace2(n,k);
	vector<vector<char>> a(4);
	rep(i,0,4)
		a[i].resize(n);
	rep(i,0,4)
		rep(j,0,n)
			a[i][j]='.';
	if(k%2==0)
	{
		rep(i,1,3)
			rep(j,1,k/2+1)
				a[i][j]='#';
		cout<<"YES"<<endl;
		rep(i,0,4)
		{
			rep(j,0,n)
				cout<<a[i][j];
			cout<<endl;
		}
	}
	else
	{
		if(k<=n-2)
		{
			rep(i,n/2-k/2,n/2+k/2+1)
				a[1][i]='#';
		}
		else
		{
			rep(i,1,n-1)
				a[1][i]='#';
			rep(i,0,(k-(n-1))/2+1)
			{
				a[2][1+i]='#';
				a[2][n-2-i]='#';
			}
		}
		cout<<"YES"<<endl;
		rep(i,0,4)
		{
			rep(j,0,n)
				cout<<a[i][j];
			cout<<endl;
		}
	}

	return 0;
}
