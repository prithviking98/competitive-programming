#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> pii;

vi dsum,psum,dxr,dxrm,dxrmd,pxrmd,pxr,pxrm;
vector<pii> dgads,pgads;

bool comp(const pii &x,const pii &y)
{
	return x.second<y.second;
}

int check(ll d,ll x,ll s,ll k)
{
	if(x>dgads.size()||k-x>pgads.size())
		return 0;
	if(x!=0&&x!=k)
	{
		if(dsum[x-1]*dxrm[d]+psum[k-x-1]*pxrm[d]<=s)
		{
			/*
			trace2(d,x);
			trace4(dsum[x-1],dxrm[d],psum[k-x-1],pxrm[d]);
			ll total=dsum[x-1]*dxrm[d]+psum[k-x-1]*pxrm[d];
			trace1(total);
			*/
			return 1;
		}
		else
			return 0;
	}
	else if(x==0)
	{
		if(psum[k-1]*pxrm[d]<=s)
			return 1;
		else 
			return 0;
	}
	else if(x==k)
	{
		if(dsum[k-1]*dxrm[d]<=s)
			return 1;
		else 
			return 0;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	ll n,m,k,s;
	cin>>n>>m>>k>>s;
	dxr.resize(n);
	pxr.resize(n);
	dxrm.resize(n);
	pxrm.resize(n);
	dxrmd.resize(n);
	pxrmd.resize(n);
	ll min=INT_MAX, md=-1;
	rep(i,0,n)
	{
		cin>>dxr[i];
		if(min>dxr[i])
		{
			min=dxr[i];
			md=i+1;
		}
		dxrm[i]=min;
		dxrmd[i]=md;
	}
	min=INT_MAX;
	md=-1;
	rep(i,0,n)
	{
		cin>>pxr[i];
		if(min>pxr[i])
		{
			min=pxr[i];
			md=i+1;
		}
		pxrm[i]=min;
		pxrmd[i]=md;
	}
	rep(i,0,m)
	{
		ll t,p;
		cin>>t>>p;
		if(t==1)
			dgads.PUB({i+1,p});
		else
			pgads.PUB({i+1,p});
	}
	dsum.resize(dgads.size());
	psum.resize(pgads.size());
	sort(dgads.begin(),dgads.end(),comp);
	sort(pgads.begin(),pgads.end(),comp);
	if(dgads.size()>0)
	dsum[0]=dgads[0].second;
	rep(i,1,dgads.size())
		dsum[i]=dsum[i-1]+dgads[i].second;
	if(pgads.size()>0)
	psum[0]=pgads[0].second;
	rep(i,1,pgads.size())
		psum[i]=psum[i-1]+pgads[i].second;

	ll x=0,minday=n+1,dnum,pnum,dday,pday;
	for(;x<=k;++x)
	{
		ll f=n,b=n;
		for(;b>=1;b/=2)
			while(f-b>=0&&check(f-b,x,s,k)==1)
				f-=b;
		if(f+1<minday)
		{
			minday=f+1;
			dnum=x;
			pnum=k-x;
			dday=dxrmd[f];
			pday=pxrmd[f];
		}
	}
	if(minday==n+1)
		cout<<-1<<endl;
	else
	{
		cout<<minday<<endl;
		rep(i,0,dnum)
			cout<<dgads[i].first<<" "<<dday<<endl;
		rep(i,0,pnum)
			cout<<pgads[i].first<<" "<<pday<<endl;
	}
	return 0;
}
