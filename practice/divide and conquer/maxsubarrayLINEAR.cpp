#include <bits/stdc++.h>

using namespace std;

typedef vector <int> vi;

class subarray
{
public:
	int low,high,sum;
};

int main()
{
	int start=clock();
	subarray max;
	int n;
	cin>>n;
	vi a(n);
	for(int i=0;i<n;++i)
		cin>>a[i];
	int sum=0,r=0,l=0;
	max.low=0;
	max.high=0;
	max.sum=a[0];
	for(int i=0;i<n;++i)
	{
		if(a[i]<sum+a[i])
		{
			sum+=a[i];
			r=i;
		}
		else
		{
			sum=a[i];
			l=r=i;
		}
		if(sum>max.sum)
		{
			max.sum=sum;
			max.low=l;
			max.high=r;
		}
	}
	cout<<"max sum = "<<max.sum;
	cout<<" from index "<<max.low<<" to "<<max.high<<endl;
	int stop=clock();
	float time=(float)(stop-start)/CLOCKS_PER_SEC;
	cout<<"time = "<<time<<endl;
	return 0;
}