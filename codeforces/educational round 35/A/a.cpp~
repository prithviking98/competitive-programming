#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int min=INT_MAX;
	int index=0;
	rep(i,0,n)
		if(a[i]<=min)
		{
			min=a[i];
			index=i;
		}
	int prevind=index,curind;
	int dmin=n;
	for(int i=prevind-1;i>=0;--i)
	{
		if(a[i]==min)
		{
			curind=i;
			int d=prevind-curind;
			if(d<dmin)
				dmin=d;
			prevind=curind;
		}
	}
	cout<<dmin<<endl;

	return 0;
}
