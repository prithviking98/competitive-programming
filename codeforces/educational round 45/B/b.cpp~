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
	vi a(1e6+1);
	rep(i,0,n)
	{
		int t;
		cin>>t;
		a[t]++;
	}
	vi eater(1e6+1);
	int sum=a.back();
	for(int i=1e6-1;i>=1e6-k;--i)
	{
		eater[i]=sum;
		sum+=a[i];
	}
	for(int i=1e6-k-1,j=1e6;i>0;--i,--j)
	{
		sum-=a[j];
		eater[i]=sum;
		sum+=a[i];
	}
	sum=0;
	rep(i,1,1e6+1)
		if(eater[i]==0)
			sum+=a[i];
	cout<<sum<<endl;
	return 0;
}
