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
	ll n,k;
	cin>>n>>k;
	vector<ll> a(k+1);
	rep(i,1,k+1)
	{
		cin>>a[i];
	}
	ll index,min=1000000000000000001;
	rep(i,1,k+1)
	{
		int rem=n%a[i];
		if(rem<min)
		{
			index=i;
			min=rem;
		}
	}
	ll count;
	count=n/a[index];
	cout<<index<<" "<<count<<endl;
	return 0;
}
