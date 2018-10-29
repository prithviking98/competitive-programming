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
	int n,m;
	cin>>n>>m;
	vector <int> a(n),b(n);
	rep(i,0,n)
		cin>>a[i]>>b[i];
	if(a[0]>0)
		cout<<"NO";
	else
	{
		int i=1;
		int flag=1;
		int cur=0;
		while(i<n)
		{
			if(a[i]<=b[cur]&&b[i]>=b[cur])
			{
				cur=i;
				++i;
			}
			else if(a[i]<=b[cur]&&b[i]<b[cur])
				++i;
			else if(a[i]>b[cur])
			{
				flag=0;
				break;
			}
		}
		if(flag==1)
		{
			if(b[cur]<m)
				flag=0;
		}
		if(flag)
		 	cout<<"YES";
		else
			cout<<"NO";
	}
		
	return 0;
}
