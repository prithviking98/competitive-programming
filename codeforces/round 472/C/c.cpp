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
	int n,u;
	cin>>n>>u;
	vi e(n);
	rep(i,0,n)
		cin>>e[i];
	if(u==1)
	{
		cout<<-1<<endl;
		return 0;
	}
	long double meta=-1;
	rep(i,0,n-2)
	{
		auto t=lower_bound(e.begin()+i+1,e.end(),e[i]+u);
		int k;
		if(t==e.end())
			k=n-1;
		else if(*t>e[i]+u)
			k=t-e.begin()-1;
		else if(*t==e[i]+u)
			k=t-e.begin();
		int j=i+1;
		if(j==k||k==i)
			continue;
		long double eta=((long double)e[k]-e[j])/((long double)e[k]-e[i]);
		if(eta>meta)
			meta=eta;
	}
	printf("%0.9Lf\n",meta);
	return 0;
}
