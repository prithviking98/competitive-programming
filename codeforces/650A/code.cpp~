#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

class point
{
public:
	ll x,y;
};

int compx(point a,point b)
{
	if(a.x<b.x)
		return 1;
	else if(a.x==b.x)
		return a.y<b.y;
	else 
		return 0;
}

int compy(point a,point b)
{
	if(a.y<b.y)
		return 1;
	else if(a.y==b.y)
		return a.x<b.x;
	else 
		return 0;
}

int main()
{
	ios::sync_with_stdio(0);
	ll n,i,j,same=1,pairs=0,s,f,b,count,sub=0;
	cin>>n;
	vector <point> a(n);
	rep(i,0,n)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a.begin(),a.end(),compx);

	for(i=0;i<n-1;)
	{
		while(a[i].x==a[i+1].x)
		{
			if(a[i].y==a[i+1].y)
			{
				++same;
				++i;
			}
			else
				break;
		}
		sub+=same*(same-1)/2;
		++i;
		same=1;
	}
	//cout<<sub<<endl;

	i=0;
	while(i<n)
	{
		s=i;
		f=i;
		for(b=n-1-i;b>=1;b/=2)
		{
			while(f+b<n&&a[f+b].x==a[s].x)
				f+=b;
		}
		count=f-s+1;
		pairs+=(count*(count-1)/2);
		i=f+1;
	}
	sort(a.begin(),a.end(),compy);
	i=0;
	while(i<n)
	{
		s=i;
		f=i;
		for(b=n-1-i;b>=1;b/=2)
		{
			while(f+b<n&&a[f+b].y==a[s].y)
				f+=b;
		}
		count=f-s+1;
		pairs+=(count*(count-1)/2);
		i=f+1;
	}
	//cout<<pairs<<" "<<sub<<endl;
	pairs-=sub;
	cout<<pairs<<endl;
	return 0;
}
