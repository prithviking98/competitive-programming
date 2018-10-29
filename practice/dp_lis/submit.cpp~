#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct member
{
	int s,b,number;
	bool operator<(const member& x) const
	{
		return s<x.s&&b<x.b;
	}
};
bool comp(const member a,const member b)
{
	if(a.s<b.s)
		return 1;
	else if(a.s==b.s)
		return a.b<b.b;
	else
		return 0;
}

struct sub
{
	int index;
	member e;
};

void finlis(const vector<member> a,const int n, vector <sub> &d, vi &p)
{
	rep(i,0,n)
	{
		int f,b;
		f=0;
		for(b=d.size()-1;b>=1;b/=2)
			while(f+b<d.size()&&d[f+b].e<a[i])
				f+=b;
		if(f==d.size()-1)
		{
			sub temp;
			temp.e=a[i];
			temp.index=i;
			p[i]=d.back().index;
			d.push_back(temp);
		}
		else
		{
			if(a[i].b<d[f+1].e.b)
			{
				p[i]=p[d[f+1].index];
				d[f+1].e=a[i];
				d[f+1].index=i;
			}
			else
				p[i]=p[d[f+1].index];
		}
	}
}
int main()
{
	int n;
	cin>>n;
	vector <member> a(n);
	rep(i,0,n)
	{
		cin>>a[i].s>>a[i].b;
		a[i].number=i+1;
	}
	sort(a.begin(),a.end(),comp);
	vi p(n);
	vector <sub> d(1);
	member temp={-1,-1};
	d[0].e=temp;
	d[0].index=-1;
	finlis(a,n,d,p);
	cout<<d.size()-1<<endl;
	int i=d.back().index;
	while(i>=0)
	{
		cout<<a[i].number<<"	";
		i=p[i];
	}
	cout<<endl;
	return 0;
}
