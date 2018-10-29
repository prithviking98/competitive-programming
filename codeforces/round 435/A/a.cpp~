#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n,x;
	cin>>n>>x;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	sort(a.begin(),a.end());
	int count=0;
	int i;
	for(i=0;i<n&&a[i]<x;++i)
		count++;
	int step=x-count;
	if(a[i]==x)
		step++;
	cout<<step<<endl;
	return 0;
}
