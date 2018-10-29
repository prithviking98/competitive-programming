#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

ll maxsubarrayl(const vector <ll> &d,const int i, vector<ll>& lmaxendi)
{
	ll s;
	if(i==0)
	{
		lmaxendi[i]=d[i];
		return d[i];
	}
	if(d[i]+lmaxendi[i-1]>d[i])
		s=d[i]+lmaxendi[i-1];
	else
		s=d[i];
	lmaxendi[i]=s;
	return s;
}

ll minsubarrayl(const vector<ll> &d,const int i, vector <ll>& lminendi)
{
	ll s;
	if(i==0)
	{
		lminendi[0]=d[0];
		return d[0];
	}
	if(d[i]+lminendi[i-1]<d[i])
		s=d[i]+lminendi[i-1];
	else
		s=d[i];
	lminendi[i]=s;
	return s;
}

ll maxsubarrayr(const vector <ll> &d,const int i, vector<ll>& rmaxendi)
{
	ll s;
	if(i==d.size()-1)
	{
		rmaxendi[i-1]=d[i];
		return d[i];
	}
	if(d[i]+rmaxendi[i]>d[i])
		s=d[i]+rmaxendi[i];
	else
		s=d[i];
	rmaxendi[i-1]=s;
	return s;
}

ll minsubarrayr(const vector<ll> &d,const int i, vector <ll>& rminendi)
{
	ll s;
	if(i==d.size()-1)
	{
		rminendi[i-1]=d[i];
		return d[i];
	}
	if(d[i]+rminendi[i]<d[i])
		s=d[i]+rminendi[i];
	else
		s=d[i];
	rminendi[i-1]=s;
	return s;
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

		vector <ll> lmaxendi(n-1),lminendi(n-1),lmax(n-1),lmin(n-1);
		priority_queue <ll> pqmax;
		priority_queue <ll, vector <ll> , greater<ll> > pqmin;
		rep(i,0,n-1)
		{
			pqmax.push(maxsubarrayl(d,i,lmaxendi));
			lmax[i]=pqmax.top();
			pqmin.push(minsubarrayl(d,i,lminendi));
			lmin[i]=pqmin.top();
			//cout<<pqmax.top()<<" l "<<pqmin.top()<<endl;
		}
		priority_queue <ll> pqmaxr;
		priority_queue <ll, vector <ll> , greater<ll> > pqminr;
		vector <ll> rminendi(n-1),rmaxendi(n-1),rmax(n-1),rmin(n-1);
		for(int i=n-1;i>=1;--i)
		{
			pqmaxr.push(maxsubarrayr(d,i,rmaxendi));
			rmax[i-1]=pqmaxr.top();
			pqminr.push(minsubarrayr(d,i,rminendi));
			rmin[i-1]=pqminr.top();
			//cout<<pqmaxr.top()<<" r "<<pqmin.top()<<endl;
		}
		ll temp;
		rep(i,0,n-1)
		{
			temp=max(abs(lmax[i]-rmin[i]),abs(lmin[i]-rmax[i]));
			delishmax=max(delishmax,temp);
		}
		cout<<delishmax<<endl;
	}
	return 0;
}
