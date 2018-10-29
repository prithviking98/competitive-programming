
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n,i,first,second,last,flag=1;
	first=second=last=0;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	i=0;
	while(i<n-1)
	{
		if(a[i]<a[i+1])
		{
			if(second||last)
			{
				flag=0;
				break;
			}
			first=1;
			++i;
		}
		else if(a[i]==a[i+1])
		{
			if(last)
			{
				flag=0;
				break;
			}
			second=1;
			++i;
		}
		else if(a[i]>a[i+1])
		{
			last=1;
			++i;
		}
	}
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
