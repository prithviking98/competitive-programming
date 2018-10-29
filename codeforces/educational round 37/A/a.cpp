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

bool all(vi a)
{
	rep(i,1,a.size())
	{
	//	trace1(a[i]);
		if(a[i]==0)
			return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
	//	trace1(t);
		int n,k;
		cin>>n>>k;
		vi a(n+1,0);
		int temp;
		rep(i,0,k)
		{
			cin>>temp;
			a[temp]=1;
		}
		int time=1;
		rep(j,1,n+1)
		{
			if(all(a))
				break;
			int i=1;
			while(i<n)
			{
				if(a[i]==1&&a[i+1]==0)
				{
					a[i+1]=1;
					i+=2;
				}
				else if(a[i]==0&&a[i+1]==1)
				{
					a[i]=1;
					++i;
				}
				else 
					++i;
			}
			time++;
			//trace1(time);
		}
		cout<<time<<endl;
	}
	return 0;
}
