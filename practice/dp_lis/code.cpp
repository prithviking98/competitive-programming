#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct sub
{
	int e,index;
};

void finlis(const vi a,const int n, vector <sub> &d, vi &p)
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
			if(a[i]<d[f+1].e)
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
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	vi p(n);
	vector <sub> d(1);
	d[0].e=-1;
	d[0].index=-1;
	finlis(a,n,d,p);
	cout<<"LIS length = "<<d.size()-1<<endl;
	int i=d.back().index;
	while(i>=0)
	{
		cout<<a[i]<<"	";
		i=p[i];
	}
	cout<<endl;
	return 0;
}
