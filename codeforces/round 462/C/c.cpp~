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
typedef vector<int> vi;
typedef pair<int,int> pii;

struct sub
{
	int index,e;
};

void lis(const vi &a, const int n, vector<sub> &d, vi &p,vi &l)
{
	rep(i,0,n)
	{
		int f=0;
		for(int b=d.size()-1;b>=1;b/=2)
			while(f+b<d.size()&&d[f+b].e<a[i])
				f+=b;
		if(f==d.size()-1)
		{
			sub t;
			t.e=a[i];
			t.index=i;
			p[i]=d.back().index;
			l[i]=d.size();
			d.PUB(t);
		}
		else
		{
			if(a[i]<d[f+1].e)
			{
				d[f+1].e=a[i];
				d[f+1].index=i;
			}
			p[i]=d[f].index;
			l[i]=f+1;
		}
	}
}

void dis(const vi &a, const int shift, vector<sub> &d, vi &p,vi &l)
{
	rep(i,0,a.size()-shift)
	{
		int f=0;
		for(int b=d.size()-1;b>=1;b/=2)
			while(f+b<d.size()&&d[f+b].e>a[i+shift])
				f+=b;
		if(f==d.size()-1)
		{
			sub t;
			t.e=a[i+shift];
			t.index=i+shift;
			p[i]=d.back().index;
			l[i]=d.size();
			d.PUB(t);
		}
		else
		{
			if(a[i+shift]>d[f+1].e)
			{
				d[f+1].e=a[i+shift];
				d[f+1].index=i+shift;
			}
			p[i]=d[f].index;
			l[i]=f+1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int left,right;
	int max=0;
	rep(i,0,n)
	{
		int f=i;
		for(int b=n-1-f;b>=1;b/=2)
			while(f+b<n&&a[f]<=a[i])
				f+=b;
		int length=f-i+1;
		if(length>max)
		{
			left=i;
			right=f;
			max=left-right+1;
		}
	}
	for(int i=left,j=right;i<=(left+right)/2;++i,--j)
	{
		int t=a[i];
		a[i]=a[j];
		a[j]=t;
	}
	vi p(n),l(n);
	vector <sub> d(1);
	d[0].e=-1;
	d[0].index=-1;
	lis(a,n,d,p,l);
	cout<<d.size()-1<<endl;
	/*
	int max=0;
	rep(i,0,n)
	{
		d.clear();
		sub t={-1,-1};
		d.PUB(t);
		vi dl(n-i-1),dp(n-i-1);
		dis(a,i+1,d,dp,dl);
		int f=0;
		for(int b=d.size()-1;b>=1;b/=2)
			while(f+b<d.size()&&d[f+b].e>=a[i])
				f+=b;
		int length=f+l[i];
		if(length>max)
			max=length;
	}
	cout<<max<<endl;
	*/

	return 0;
}
