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
	int n,t;
	cin>>n>>t;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int rem=t;
	int days;
	rep(i,0,n)
	{
		int rt=86400-a[i];
		if(rt>=rem)
		{
			days=i+1;
			break;
		}
		else
			rem-=rt;
	}
	cout<<days;
	
	return 0;
}
