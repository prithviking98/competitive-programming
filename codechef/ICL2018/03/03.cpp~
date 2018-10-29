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
	int t;
	cin>>t;
	while(t--)
	{
		int x,y,n,s,e,w,p;
		cin>>x>>y>>n>>s>>e>>w>>p;
		//trace3(x,y,p);
		//trace4(n,s,e,w);
		p-=x*e+y*n;
		int length;
		length=x+y;
		int c=n+s+e+w;
		vi a(2);
		a={n+s,e+w};
		sort(a.rbegin(),a.rend());
		int l=a[0]/__gcd(a[0],a[1])*a[1];
		while(p>0)
		{
			if(p%a[0]==0)
			{
				length+=2*p/a[0];
				p=0;
			}
			else if(p%a[1]==0)
			{
				if(p>=l)
				{
					length+=2*l/a[0];
					p-=l;
				}
				length+=2*p/a[1];
				p=0;
			}
			else if(p>=a[0])
			{
				length+=2;
				p-=a[0];
			}
			else 
				p=-1;
		}
		if(p==0)
			cout<<length<<endl;
		else
			cout<<-1<<endl;
	}
	return 0;
}
