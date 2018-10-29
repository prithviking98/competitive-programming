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
	int n,a,b;
	cin>>n>>a>>b;
	int  maxcakes=0;
	if(a<=b)
	{
		int i;
		if(b>=n)
			i=1;
		else
			i=n-b;
		while(i<n&&i<=a)
		{
			int curmin, x=a/i,y=b/(n-i);
			curmin=min(x,y);
			if(curmin>maxcakes)
				maxcakes=curmin;
		//	cout<<i<<endl;
			++i;
		}
	}
	else
	{
		int i;
		if(a<n)
			i=n-a;
		else
			i=1;
		while(i<n&&i<=b)
		{
			int curmin,x=b/i,y=a/(n-i);
			curmin=min(x,y);
			if(curmin>maxcakes)
				maxcakes=curmin;
			++i;
		}
	}
	cout<<maxcakes<<endl;


	return 0;
}
