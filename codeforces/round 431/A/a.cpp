#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n,flag;
	flag=0;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int i=0,s=0,e=0;
	while(e<n)
	{
		if(a[e]%2==1)
		{
			if(e!=n-1)
			{
				if(a[e+1]%2==1)
				{
					s=e=e+1;
				}
			}
			else if(e==n-1)
			{
				flag=1;
				break;
			}
		}
		else
			e+=2;
	}
	if(flag)
		cout<<"yes"<<endl;
	else
		cout<<"no"<<endl;
	return 0;
}
