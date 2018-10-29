#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct tank
{
	int o,n,w;
	bool operator < (const tank& x) const
	{
		if(n<x.n)
			return 1;
		else if(n==x.n)
			return o<x.o;
		else
			return 0;
	}
	void print()
	{
		printf("%d %d %d\n",o,n,w);
	}
};

bool comp(tank& a,tank& b)
{
	return a.w<b.w;
}
int findmin(const vector <tank> t, const int ntanks,int o, int n, vector < vector <vi> > &d)
{
	rep(i,0,n+1)
	{
		rep(j,0,o+1)
		{
			rep(k,1,ntanks+1)
			{
				int q;
				if(t[k-1].o>=j&&t[k-1].n>=i)
				{
					q=min(t[k-1].w,d[i][j][k-1]);
				}
				else if(t[k-1].o>=j&&t[k-1].n<i)
				{
					q=min(t[k-1].w+d[i-t[k-1].n][0][k-1],d[i][j][k-1]);
				}
				else if(t[k-1].o<j&&t[k-1].n>=i)
				{
					q=min(t[k-1].w+d[0][j-t[k-1].o][k-1],d[i][j][k-1]);
				}
				else
				{
					q=min(t[k-1].w+d[i-t[k-1].n][j-t[k-1].o][k-1],d[i][j][k-1]);
				}
				d[i][j][k]=q;
			}
		}
	}
	return d[n][o][ntanks];
}

int main()
{
	int c;
	cin>>c;
	while(c--)
	{
		int o,n,ntanks;
		cin>>o>>n;
		cin>>ntanks;
		vector <tank> t(ntanks);
		rep(i,0,ntanks)
			cin>>t[i].o>>t[i].n>>t[i].w;
		//sort(t.begin(),t.end(),comp);
		//rep(i,0,ntanks)
		//	t[i].print();
		vector < vector < vi > > d(n+1);
		rep(i,0,n+1)
			d[i].resize(o+1);
		//d[0][0]=t[0].w;
		//cout<<d[0][0]<<endl;
		rep(i,0,n+1)
			rep(j,0,o+1)
				d[i][j].resize(ntanks+1);
		rep(i,0,n+1)
			rep(j,0,o+1)
				d[i][j][0]=1000000000;		
		int minweight;
		minweight=findmin(t,ntanks,o,n,d);
		cout<<minweight<<endl;
	}
	return 0;
}
