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
	vi p(n),c(n);
	map<int,int> m;
	rep(i,0,n)
	{
		cin>>p[i];
		m[p[i]]=i;
	}
	rep(i,0,n)
		cin>>c[i];
	sort(p.begin(),p.end());
	vi maxc;
	vll sum(n);
	rep(i,0,n)
		sum[i]=c[i];
	rep(i,0,n)
	{
		if(i==0)
			continue;
		if(k==0)
			break;
		if(maxc.size()<k)
			maxc.PUB(c[m[p[i-1]]]);
		else
			maxc[0]=max(maxc[0],c[m[p[i-1]]]);
		sort(maxc.begin(),maxc.end());
		rep(j,0,maxc.size())
			sum[m[p[i]]]+=(ll)maxc[j];
	}
	rep(i,0,n)
		cout<<sum[i]<<" ";
	cout<<endl;
	return 0;
}
