#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n;
	cin>>n;
	vi a(n+1);
	rep(i,1,n+1)
		cin>>a[i];
	float e=1/1000000;
	int flag=0;
	rep(k,1,n+1)
	{
	rep(i,k+1,n+1)
	{
		float m,c1,c2;
		m=((float)a[i]-a[k])/(i-1);
		c1=a[k]-m;
		c2=c1;
		//cout<<"m,c1="<<m<<" "<<c1<<endl;
		int j=1;
		for(;j<n+1;++j)
		{
			if(abs(a[j]-(m*j+c1))<e&&j<i)
				break;
			if(abs(a[j]-(m*j+c1))>e)
			{
				//cout<<j<<" ";
				if(c2==c1)
				{
					c2=a[j]-m*j;
					//cout<<"c2 "<<c2;
				}
				else
				{
					if(abs(a[j]-(m*j+c2))>e)
						break;
				}
			}
			//cout<<endl;
		}
		if(j==n+1&&abs(c2-c1)>e)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		break;
	}
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
