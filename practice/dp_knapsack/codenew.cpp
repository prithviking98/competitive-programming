#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct weight
{
	int w,v;
};

int findmax(const vector <weight> a, const int n,const int w,vector <vi> &d)
{
	rep(i,1,n+1)
	{
		rep(j,1,w+1)
		{
			int q;
			if(a[i-1].w>j)
				q=d[i-1][j];
			else
			{
				q=max(d[i-1][j],d[i-1][j-a[i-1].w]+a[i-1].v);
			}
			d[i][j]=q;
		}
	}
	return d[n][w];
}

int main()
{
	int n,w;
	cin>>n>>w;
	vector <weight> a(n);
	rep(i,0,n)
		cin>>a[i].w>>a[i].v;
	vector <vi> d(n+1);
	rep(i,0,n+1)
		d[i].resize(w+1);
	int maxval=findmax(a,n,w,d);
	cout<<"max="<<maxval<<endl;
	return 0;
}
