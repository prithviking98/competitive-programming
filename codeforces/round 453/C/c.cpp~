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
	int h;
	cin>>h;
	vi a(h+1);
	rep(i,0,h+1)
		cin>>a[i];
//	rep(i,0,h+1) cout<<a[i];
	int flag=0;
	rep(i,0,h)
		if(a[i]>1&&a[i+1]>1)
			flag=1;
	if(flag)
	{
		cout<<"ambiguous"<<endl;
		int n=0;
		rep(i,0,h+1)
			n+=a[i];
		int cur=0;
		rep(i,0,h+1)
		{
			rep(j,0,a[i])
				cout<<cur<<" ";
			cur+=a[i];
		}
		cout<<endl;
		cur=0;
		int first=1;
		rep(i,0,h+1)
		{
			if(first&&a[i]!=1&&a[i-1]!=1)
			{
				cout<<cur-1<<" ";
				rep(j,0,a[i]-1)
					cout<<cur<<" ";
				cur+=a[i];
				first=0;
			}
			else
			{
				rep(j,0,a[i])
					cout<<cur<<" ";
				cur+=a[i];
			}
		}
		cout<<endl;
	}
	else
		cout<<"perfect"<<endl;

	return 0;
}
