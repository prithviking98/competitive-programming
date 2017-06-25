#include <bits/stdc++.h>
 using namespace std;
 int checkprime(int i)
{
	for(int j=2;j<=sqrt(i);++j)
		if(i%j==0)
			return 0;
	return 1;
}

int main()
{
	int m,n,t,i,j;
	cin>>t;
	for(i=0;i<t;++i)
	{
		cin>>m>>n;
		for(j=m!=1?m:2;j<=n;++j)
			if(checkprime(j))
				cout<<j<<"\n";
		cout<<"\n";
	}
	return 0;
}
