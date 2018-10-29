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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vector<ll> t(n),b(m);
	rep(i,0,n)
		cin>>t[i];
	rep(i,0,m)
		cin>>b[i];
	sort(t.begin(),t.end());
	sort(b.begin(),b.end());
	ll max,min;
	max=t[n-1]*b[m-1];
	min=t[0]*b[0];
	if(max>min)
	{
		max=t[n-2]*b[m-1];
		if(max>min)
			cout<<max<<endl;
		else
			cout<<min<<endl;
	}
	else
	{
		min=t[1]*b[0];
		if(max>min)
			cout<<max<<endl;
		else
			cout<<min<<endl;
	}
	return 0;
}
