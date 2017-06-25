#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n,count;
	cin>>n;
	while(n!=0)
	{
		count=n*(n+1)*(2*n+1)/6;
		cout<<count<<endl;
		cin>>n;
	}
	cout<<endl;
	return 0;
}
