#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll product(ll n,ll b,ll i)
{
	if(i<0)
		return -1;
	ll p=((n%b+i*b)*((n-i*b)/b));
	return p;
}

int main()
{
	ll n,b,i,f;
	int t,j;
	cin>>t;
	//cout<<t<<endl;
	for(j=0;j<t;++j)
	{
		cin>>n>>b;
		//cout<<n<<"\t"<<b<<endl;
		i=0;
		for(f=n/b;f>=1;f/=2)
		{
			while(i+f<=n/b&&(product(n,b,i+f)>product(n,b,i+f-1)))
				i+=f;
		}
		//cout<<i<<endl;
		cout<<product(n,b,i)<<"\n";
	}
	return 0;
}
