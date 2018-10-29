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
	rep(i,1,w+1)
	{
		rep(j,1,n+1)
		{
			int q;
			if(a[j-1].w>i)
				q=d[i][j-1];
			else
			{
				q=max(d[i][j-1],d[i-a[j-1].w][j-1]+a[j-1].v);
			}
			d[i][j]=q;
		}
	}
	return d[w][n];
}

int main()
{
	int n,w;
	cin>>n>>w;
	vector <weight> a(n);
	rep(i,0,n)
		cin>>a[i].w>>a[i].v;
	vector <vi> d(w+1);
	rep(i,0,w+1)
		d[i].resize(n+1);
	int maxval=findmax(a,n,w,d);
	cout<<"max="<<maxval<<endl;
	return 0;
}
