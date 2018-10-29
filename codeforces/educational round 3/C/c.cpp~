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
	int n;
	cin>>n;
	vi a(n);
	int t=0;
	rep(i,0,n)
	{
		cin>>a[i];
		t+=a[i];
	}
	sort(a.begin(),a.end());
	if(t>=n)
	{
		int l=n-(t%n);
		int m=t/n;
		int time=0;
		for(int i=0;i<l;++i)
		{
			time+=abs(m-a[i]);
		}
		for(int i=l;i<n;++i)
			time+=abs(m+1-a[i]);
		time/=2;
		cout<<time<<endl;
	}
	else
	{
		int time=0;
		rep(i,0,n)
			if(a[i]>1)
				time+=a[i]-1;
		cout<<time<<endl;
	}
			
	return 0;
}
