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
	int n,a,b;
	cin>>n>>a>>b;
	if(min(a,b)>1)
		cout<<"NO"<<endl;
	else if(n==2&&a==1&&b==1)
		cout<<"NO"<<endl;
	else if(n==3&&a==1&&b==1)
		cout<<"NO"<<endl;
	else
	{
		vvi p(n);
		rep(i,0,n)
			p[i].resize(n);
		int t=max(a,b);
		t=n-t;
		rep(i,0,t)
		{
			p[i][i+1]=1;
			p[i+1][i]=1;
		}
//		tracem(p);
//		trace1(a);
		if(a==1)
		{
			rep(i,0,n)
				rep(j,0,n)
				{
					if(i!=j&&!p[i][j])
						p[i][j]=1;
					else if(p[i][j])
						p[i][j]=0;
				}
		}
		cout<<"YES"<<endl;
		rep(i,0,n)
		{
			rep(j,0,n)
				cout<<p[i][j];
			cout<<endl;
		}
	}
	return 0;
}
