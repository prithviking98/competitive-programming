#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

class voucher
{
public:
	int l,r,duration;
	ll cost;
	void calcdur()
	{
		duration=r-l+1;
	}
	void disp()
	{
		cout<<l<<" "<<r<<" "<<duration<<" "<<cost<<endl;
	}
};	

int comp(voucher a,voucher b)
{
	if(a.duration<b.duration)
		return 1;
	else if(a.duration==b.duration)
		return a.cost>b.cost;
	else 
		return 0;
}

int inter(voucher a,voucher b)
{
	if(a.r>b.l||b.r>a.l)
		return 0;
	else 
		return 1;
}

int main()
{
	int n,x,i,j,b,f,flag=0;
	ll cost=3000000000,temp;
	cin>>n>>x;
	vector <voucher> v(n);
	for(i=0;i<n;++i)
	{
		cin>>v[i].l>>v[i].r>>v[i].cost;
		v[i].calcdur();
	}
	sort(v.begin(),v.end(),comp);
	/*for(i=0;i<n;++i)
	{
		cout<<v[i].l<<" "<<v[i].r<<" "<<v[i].cost<<endl;
	}*/
	for(i=0;i<n;++i)
	{
		f=0;
		for(b=n-1;b>=1;b/=2)
			while(b+f<n&&v[i].duration+v[b+f].duration<=x&&!inter(v[i],v[b+f])&&b+f!=i)
				f+=b;
		if(v[f].duration+v[i].duration==x&&!inter(v[i],v[f]))
		{
			flag=1;
			temp=v[f].cost+v[i].cost;
			if(temp<cost)
				cost=temp;
		}
	}
	if(flag)
		cout<<cost<<endl;
	else 
		cout<<-1;
	return 0;
}
