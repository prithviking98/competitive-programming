#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector <int> men,women;
	int t,i,j,sum,k,n;
	cin>>t;
	for(i=0;i<t;++i)
	{
		cin>>n;
		sum=0;
		for(j=0;j<n;++j)
		{
			cin>>k;
			men.push_back(k);
		}
		for(j=0;j<n;++j)
		{
			cin>>k;
			women.push_back(k);
		}
		sort(men.begin(),men.end());
		sort(women.begin(),women.end());
		for(j=0;j<n;++j)
			sum+=men[j]*women[j];
		cout<<sum<<endl;
		men.clear();
		women.clear();
	}
	return 0;
}
