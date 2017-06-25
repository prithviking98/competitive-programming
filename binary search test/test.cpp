#include <iostream>
using namespace std;
int main()
{
	int k,n,x;
	int b;
	x=16;
	k=0;
	n=7;
	int a[n];
	for(int i=0;i<n;++i)
		a[i]=10+i;
	for(x=10;x<=10+n;++x)
	{
		k=0;
		for(b=n-1;b>=1;b/=2)
		{
			while(k+b<=n-1&&a[(int)(k+b)]<=x)
				k=k+b;
		}
		if(a[k]==x)
			cout<<"element found at "<<k<<endl;
		else
			cout<<"not found\n";
	}
	return 0;
}
