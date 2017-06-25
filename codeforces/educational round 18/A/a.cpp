#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int n,dmin,count=1,i;
	cin>>n;
	vector <int> a(n);
	for(i=0;i<n;++i)
		cin>>a[i];
	sort(a.begin(),a.end());
	dmin=a[1]-a[0];
	for(i=2;i<n;++i)
	{
		if(a[i]-a[i-1]<dmin)
		{
			dmin=a[i]-a[i-1];
			count=1;
		}
		else if(a[i]-a[i-1]==dmin)
			count++;
	}
	cout<<dmin<<" "<<count;
	return 0;
}
