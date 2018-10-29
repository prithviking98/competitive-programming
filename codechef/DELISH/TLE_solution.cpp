#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

ll maxsubarray(const vector <ll> &d,const int start)
{
	ll s,p;
	s=0;
	p=d[start];
	rep(i,start,stop+1)
	{
		s=max(d[i],d[i]+s);
		p=max(p,s);
	}
	return p;
}

ll minsubarray(const vector<ll> &d,const int start,const int stop)
{
	ll s,p;
	s=0;
	p=d[start];
	rep(i,start,stop+1)
	{
		s=min(d[i],d[i]+s);
		p=min(p,s);
	}
	return p;
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		ll delishmax;
		delishmax=-10000000000000;
		cin>>n;
		vector<ll> d(n);
		rep(i,0,n)
			cin>>d[i];
		rep(i,0,n-1)
		{
			ll lmax,lmin,rmax,rmin,temp;
			lmax=maxsubarray(d,0,i);
			lmin=minsubarray(d,0,i);
			rmax=maxsubarray(d,i+1,n-1);
			rmin=minsubarray(d,i+1,n-1);
			//printf("%d %d %d %d\n",lmax,lmin,rmax,rmin);
			ll delish1,delish2;
			delish1=abs(lmax-rmin);
			delish2=abs(rmax-lmin);
			if(delish1>delish2)
				temp=delish1;
			else 
				temp=delish2;
			//cout<<"temp= "<<temp<<endl;
			//delishmax=max(temp,delishmax);
			if(temp>delishmax)
			{
				delishmax=temp;
				//cout<<"delish ="<<delishmax<<endl;
			}
		}
		cout<<delishmax<<endl;
	}
	return 0;
}
