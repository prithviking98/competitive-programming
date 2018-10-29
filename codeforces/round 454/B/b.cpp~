#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

int main()
{
	ios::sync_with_stdio(0);
	vector <vector <char> > a(10);
	rep(i,1,10)
		a[i].resize(10);
	rep(i,1,10)
		rep(j,1,10)
			cin>>a[i][j];
/*	rep(i,1,10)
	{
		rep(j,1,10)
		{
			cout<<a[i][j];
			if(j%3==0)
				cout<<" ";
		}
		cout<<endl;
		if(i%3==0)
			cout<<endl;
	}*/
	int r,c;
	cin>>r>>c;
	//cout<<r<<" "<<c<<endl;
	int x,y;
	x=(r%3)-1;
	y=(c%3)-1;
	if(x==-1)
		x=2;
	if(y==-1)
		y=2;
	//cout<<x<<" "<<y<<endl;
	int flag=0;
	rep(i,1,4)
		rep(j,1,4)
		{
			if(a[x*3+i][y*3+j]=='.')
			{
				a[x*3+i][y*3+j]='!';
				flag=1;
			}
		}
	if(flag)
	rep(i,1,10)
	{
		rep(j,1,10)
		{
			cout<<a[i][j];
			if(j%3==0)
				cout<<" ";
		}
		cout<<endl;
		if(i%3==0)
			cout<<endl;
	}
	else
	{
		rep(i,1,10)
		{
			rep(j,1,10)
			{
				if(a[i][j]=='.')
				{
					a[i][j]='!';
					cout<<a[i][j];
					if(j%3==0)
						cout<<" ";
				}
				else
				{
					cout<<a[i][j];
					if(j%3==0)
						cout<<" ";
				}
			}
			cout<<endl;
			if(i%3==0)
				cout<<endl;
		}
	}



	return 0;
}
