#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class subarray
{
public:
	int low,high,sum;
};

subarray MaxCrossingSubarray(vi a,int low,int high)
{
	int mid=(low+high)/2;
	int ls,rs,l,r;
	l=mid;
	r=mid+1;
	ls=a[l];
	rs=a[r];
	int sum =0;
	for(int i=l;i>=low;--i)
	{
		sum+=a[i];
		if(sum>ls)
		{
			ls=sum;
			l=i;
		}
	}
	sum=0;
	for(int i=r;i<=high;++i)
	{
		sum+=a[i];
		if(sum>rs)
		{
			rs=sum;
			r=i;
		}
	}
	subarray max;
	max.low=l;
	max.high=r;
	max.sum=ls+rs;
	return max;
}

subarray MaxSubarray(vi a,int low,int high)
{
	subarray max;
	if(low==high)
	{
		max.low=low;
		max.high=high;
		max.sum=a[low];
	}
	else
	{
		int mid=(low+high)/2;
		subarray left,right,cross;
		left=MaxSubarray(a,low,mid);
		right=MaxSubarray(a,mid+1,high);
		cross=MaxCrossingSubarray(a,low,high);
		if(left.sum>=right.sum&&left.sum>=cross.sum)
			max=left;
		else if(right.sum>=left.sum&&right.sum>=cross.sum)
			max=right;
		else
			max=cross;
	}
	return max;
}

int main()
{
	int start=clock();
	int n;
	cin>>n;
	vector <int> a(n);
	for(int i=0;i<n;++i)
		cin>>a[i];
	subarray max;
	max=MaxSubarray(a,0,n-1);
	cout<<"max sum ="<<max.sum;
	cout<<" from index "<<max.low<<" to "<<max.high<<endl;
	int stop=clock();
	float time=(float)(stop-start)/CLOCKS_PER_SEC;
	cout<<"time = "<<time<<endl;
	return 0;
}
