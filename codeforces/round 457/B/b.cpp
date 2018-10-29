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

int main()
{
	ios::sync_with_stdio(0);
	int k;
	ll n;
	cin>>n>>k;
	vi a(82);
	ll t=n;
	int bindigits=0;
	for(int i=63;i>=0;--i)
	{
		if(t%2==1)
			bindigits++;
		a[i]=t%2;
		t/=2;
	}
	if(k<bindigits)
		cout<<"no"<<endl;
	else
	{
		int count=bindigits;
		int curmax=0;
		while(a[curmax]==0)
			curmax++;
		while(count<k)
		{
			while(a[curmax]==0)
				curmax++;
			a[curmax]--;
			a[curmax+1]+=2;
			count++;
		}
		cout<<"yes"<<endl;
		for(int i=curmax;i<82;++i)
		{
			for(int j=0;j<a[i];++j)
				cout<<63-i<<" ";
		}
		cout<<endl;
	}



	return 0;
}
