#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int m,n;
	cin>>n>>m;
	vector <vector <int> > a(n);
	rep(i,0,n)
		a[i].resize(m);
	rep(i,0,n)
		rep(j,0,m)
			cin>>a[i][j];
	rep(i,0,n)
	{
		rep(j,0,m)
			cout<<a[i][j]<<"\t";
		cout<<endl;
	}
	cout<<a.size()<<a[0].size()<<endl;
	return 0;
}
