#include <bits/stdc++.h>

using namespace std;

#define P(i) (i-1)/2
#define L(i) 2*i+1
#define R(i) 2*(i+1)

typedef vector<int> vi;

void maxheapify(vi & a,int i,int size)
{
	int l,r,largest,temp;
	l=L(i);
	r=R(i);
	if(r<size&&a[r]>a[i])
		largest=r;
	else
		largest=i;
	if(l<size&&a[l]>a[largest])
		largest=l;
	if(largest!=i)
	{
		temp=a[i];
		a[i]=a[largest];
		a[largest]=temp;
		maxheapify(a,largest,size);
	}
}

void buildmaxheap(vi &a)
{
	for(int i=a.size()/2-1;i>=0;--i)
		maxheapify(a,i,a.size());
}

void heapsort(vi &a)
{
	int temp;
	for(int i=a.size()-1;i>=1;--i)
	{
		temp=a[i];
		a[i]=a[0];
		a[0]=temp;
		maxheapify(a,0,i);
	}
}
int main()
{
	int n,row,j,begin;
	cin>>n;
	vi a(n);
	for(int i=0;i<n;++i)
		cin>>a[i];
	buildmaxheap(a);
	cout<<"\n";
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<" ";
	cout<<"\n\n";
	j=0;
	for(int i=1;j<a.size();++i)
	{
		row=pow(2,i-1);
		begin=pow(2,i-1)-1;
		//cout<<row<<" "<<begin;
		for(j=pow(2,i-1)-1;j<begin+row&&j<a.size();++j)
		{
			cout<<a[j]<<"	";
		}
		cout<<endl;
	}

	heapsort(a);
	cout<<"\n";
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<" ";
	cout<<"\n";

	cout<<"\n";
	j=0;
	for(int i=1;j<a.size();++i)
	{
		row=pow(2,i-1);
		begin=pow(2,i-1)-1;
		//cout<<row<<" "<<begin;
		for(j=pow(2,i-1)-1;j<begin+row&&j<a.size();++j)
		{
			cout<<a[j]<<"	";
		}
		cout<<endl;
	}
	return 0;
}
