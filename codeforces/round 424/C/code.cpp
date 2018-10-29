
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int i,j,k,n,maxsum,minsum,bmax=-4000000,bmin=4000000;
	cin>>k>>n;
	vi a(k),b(n);
	rep(i,0,k)
		cin>>a[i];
	rep(i,0,n)
	{
		cin>>b[i];
		if(b[i]>bmax)
			bmax=b[i];
		if(b[i]<bmin)
			bmin=b[i];
	}
	int p,s;
	s=0;
	p=a[0];
	rep(i,0,k)
	{
		s=max(a[i],a[i]+s);
		p=max(s,p);
	}
	maxsum=p;
	s=0;
	p=a[0];
	rep(i,0,k)
	{
		s=min(a[i],a[i]+s);
		p=min(p,s);
	}
	minsum=p;
	//printf("%d %d\n",maxsum,minsum);
	int low,high;
	high=bmax-minsum;
	low=bmin-maxsum;
	int count=0,score;
	for(int x=low;x<=high;++x)
	{
		rep(i,0,n)
		{
			score=x;
			rep(j,0,k)
			{
				score+=a[j];
				if(b[i]==score)
					break;
			}
			if(j==k)
				break;
		}
		if(i==n)
			++count;
	}
	cout<<count<<endl;
	return 0;
}
