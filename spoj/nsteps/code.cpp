#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n,x,y;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		cin>>x>>y;
		if(x>=0&&y>=0)
		{
		if(y==x)//greater than zero
		{
			if(y%2==0)
				cout<<2*y<<endl;
			else
				cout<<2*y-1<<endl;
		}
		else if(y==x-2)
		{
			if(y%2==0)
				cout<<2*(y+1)<<endl;
			else
				cout<<2*y+1<<endl;
		}
		else cout<<"No Number\n";
		}
		else
			cout<<"Np Number\n";
	}
	return 0;
}
