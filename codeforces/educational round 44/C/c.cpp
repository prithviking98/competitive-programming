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
	int n,k,l;
	cin>>n>>k>>l;
	int m=n*k;
	vector<ll> a(m);
	rep(i,0,m)
		cin>>a[i];
	sort(a.begin(),a.end());
	int b=a[0]+l;
	int count;
	rep(i,0,m)
	{
		if(a[i]>b)
			break;
		count++;
	}
	if(count<n)
	{
		cout<<0<<endl;
		return 0;
	}
	else if(count==m)
	{
		ll vol=0;
		for(int i=0;i<m;i+=k)
			vol+=a[i];
		cout<<vol<<endl;
	}
	else
	{
		if(k==1)
		{
			cout<<0<<endl;
			return 0;
		}
		int s=(count-n)/(k-1);
		ll vol=0;
		for(int i=0;i<s*k;i+=k)
			vol+=a[i];
		rep(i,0,n-s-1)
			vol+=a[count-1-i];
		vol+=a[s*k];
		cout<<vol<<endl;
	}


	return 0;
}
