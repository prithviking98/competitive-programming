#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vi a(n);
		rep(i,0,n)
			cin>>a[i];
		int mini=0;
		rep(i,0,n)
			if(a[i]<a[mini])
				mini=i;
		cout<<mini+1<<endl;
	}

	return 0;
}
