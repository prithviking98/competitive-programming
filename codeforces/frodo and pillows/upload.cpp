#include <iostream>
#include <vector>

using namespace std;

long long unsigned int *a;
long long unsigned int pillows,n;

void add(int);

int main()
{
	long long unsigned m,k;
	cin>>n>>m>>k;
	a=new long long unsigned int[n];
	pillows=m-n;
	while(pillows>0)
		add(k-1);
	cout<<a[k-1]+1;
	return 0;
}

void add(int k)
{
	if(k==0)
	{
		if((k+1!=n)&&(a[k]==a[k+1]))
		{
			++a[k];
			--pillows;
		}
		else
			add(k+1);
	}
	else if(k==n-1)
	{
		if(a[k]==a[k-1])
		{
			++a[k];
			--pillows;
		}
		else
			add(k-1);
	}
	else
	{
		if((a[k]==a[k+1])&&(a[k]==a[k-1]))
		{
			a[k]++;
			--pillows;
		}
		else if(a[k]>a[k+1])
			add(k+1);
		else
			add(k-1);
	}
}
