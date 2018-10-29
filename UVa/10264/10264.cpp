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
	int n;
	while(cin>>n)
	{
		vi w(1<<(n));
		int m=1<<(n);
//		trace1(m);
		rep(i,0,m)
			cin>>w[i];
//		tracev(w);
		vi p(m);
		rep(i,0,m)
		{
			rep(j,0,n)
				p[i]+=w[(i^((1<<j)))];
		}
//		tracev(p);
		int M=0;
		rep(i,0,m)
		{
			rep(j,0,n)
			{
				int t;
				if(i!=i^((1<<j)))
					t=p[i]+p[(i^((1<<j)))];
				M=max(t,M);
			}
		}
		cout<<M<<endl;
	}
	return 0;
}
