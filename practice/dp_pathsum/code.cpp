#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int maxpath(const vector< vi > a,int r,int c, vector <vector <pair<int,int> > > &d)
{
	if(d[r][c].first||(r==0&&c==0))
	{
		return d[r][c].first;
	}
	else
	{
		if(r==0)
		{
			d[r][c].first=maxpath(a,r,c-1,d)+a[r][c];
			d[r][c].second=0;
			return d[r][c].first;
		}
		else if(c==0)
		{
			d[r][c].first=maxpath(a,r-1,c,d)+a[r][c];
			d[r][c].second=1;
			return d[r][c].first;
		}
		else
		{
			d[r][c].first=max(maxpath(a,r-1,c,d),maxpath(a,r,c-1,d))+a[r][c];
			if(d[r-1][c].first>d[r][c-1].first)
				d[r][c].second=1;
			else
				d[r][c].second=0;
			return d[r][c].first;
		}
	}
}
int main()
{
	int r,c;
	cin>>r>>c;
	vector <vector <int> > a(r);
	rep(i,0,r)
		a[i].resize(c);
	vector <vector < pair<int,int> > > d(r);
	rep(i,0,r)
		d[i].resize(c);
	rep(i,0,r)
		rep(j,0,c)
			cin>>a[i][j];
	d[0][0].first=a[0][0];
	d[0][0].second=-1;
	int pathlength=maxpath(a,r-1,c-1,d);
	cout<<"maxpath = "<<pathlength<<endl;
	/*rep(i,0,r)
	{
		rep(j,0,c)
			cout<<a[i][j]<<"\t";
		cout<<endl;
	}*/
	int i;
	int l,m;
	l=r-1;m=c-1;
	i=a[l][m];
	printf("%d : (%d,%d)\n",a[l][m],l+1,m+1);
	while(1)
	{
		if(d[l][m].second==0)
			--m;
		else
			--l;
		printf("%d : (%d,%d)\n",a[l][m],l+1,m+1);
		if(d[l][m].second==-1)
			break;
	}
	return 0;
}
