#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int start=clock();
	ios::sync_with_stdio(0);
	int n,k,q,l,r,i,j,count;
	vi t(200000);
	cin>>n>>k>>q;
	for(i=0;i<n;++i)
	{
		cin>>l>>r;
		for(j=l-1;j<=r-1;++j)
			++t[j];
	}
	for(i=0;i<q;++i)
	{
		cin>>l>>r;
		count =0;
		for(j=l-1;j<=r-1;++j)
			if(t[j]>=k)
				++count;
		cout<<count<<"\n";
	}
	int stop=clock();
	float time=(stop-start)/CLOCKS_PER_SEC;
	cout<<"time ="<<time;
	return 0;
}
