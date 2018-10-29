#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

void add(vi &BIT,int index,int val)
{
	for(int i=index;i<BIT.size();i+=(i&-i))
	{
	//cout<<"index in add "<<index<<endl;
		BIT[i]+=val;
	}
}
int sum(vi &BIT,int index)
{
	int sum=0;
	for(int i=index;i>0;i-=(i&-i))
		sum+=BIT[i];
	return sum;
}

int invcount(vi &a,int n)
{
	vi BIT(n+1);
	int count=0;
	for(int i=n-1;i>=0;--i)
	{
		//cout<<"test before sum"<<endl;
		count+=sum(BIT,a[i]-1);
		//cout<<"test before add"<<endl;
		//cout<<"a[i] in invcount "<<a[i]<<endl;
		add(BIT,a[i],1);
	}
	return count;
}
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int m;
	cin>>m;
	int l,r;
	while(m--)
	{
		cin>>l>>r;
		for(int i=l-1,j=r-1;i<j;++i,--j)
		{
			int t=a[i];
			a[i]=a[j];
			a[j]=t;
		}
		int c=invcount(a,n);
		if(c%2==0)
			cout<<"even"<<endl;
		else
			cout<<"odd"<<endl;
	}

	return 0;
}
