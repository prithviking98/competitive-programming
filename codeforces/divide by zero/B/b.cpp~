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

int main()
{
	ios::sync_with_stdio(0);
	int n,k,l;
	cin>>n>>k>>l;
	vi a(n),b(n),d(n);
	rep(i,0,n)
		cin>>a[i];
	rep(i,0,n)
		cin>>b[i];
	rep(i,0,n)
		d[i]=abs(a[i]-b[i]);
	int s=min(k,l);
	int m=max(k,l);
	sort(d.rbegin(),d.rend());
	int next=a[0];
	rep(i,0,n)
		if(d[i]<d[0])
		{
			next=d[i];
			break;
		}

	int flag=1,count=0;
	while(flag)
	{
		for(int i=0;i<n&&(d[0]!=next?d[i]>next:d[i]>=next);++i)
		{
			if(count==s)
			{
				flag=0;
				break;
			}
			d[i]-=2;
			count++;
		}
		if(flag==0)
			break;
		if(d[0]<next)
		{
			next=d[0];
			sort(d.rbegin(),d.rend());
		}
		else if(d[0]==next)
		{
			rep(i,0,n)
				if(d[i]<a[0])
				{
					next=d[i];
					break;
				}
		}
	}
	
	sort(d.rbegin(),d.rend());
	next=a[0];
	rep(i,0,n)
		if(d[i]<d[0])
		{
			next=d[i];
			break;
		}
	flag=1,count=0;
	m=m-s;
	while(flag)
	{
		for(int i=0;i<n&&(d[0]!=next?d[i]>next:d[i]>=next);++i)
		{
			if(count==m)
			{
				flag=0;
				break;
			}
			d[i]-=1;
			count++;
		}
		if(flag==0)
			break;
		if(d[0]<next)
		{
			next=d[0];
			sort(d.rbegin(),d.rend());
		}
		else if(d[0]==next)
		{
			rep(i,0,n)
				if(d[i]<d[0])
				{
					next=d[i];
					break;
				}
		}
	}
	ll e=0;
	rep(i,0,n)
	{
		//trace2(d[i],i);
		e+=((ll)d[i]*d[i]);
	}
	cout<<e<<endl;
	return 0;
}
