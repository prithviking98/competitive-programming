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
		int n;
		cin>>n;
		vi a(2001);
		int k;
		rep(i,0,n)
		{
			cin>>k;
			a[k+1000]++;
		}
		ll count=0;
		for(int i=0;i<2001;++i)
		{
			if(a[i]==0)
				continue;
			for(int j=i;j<2001;++j)
			{
				if(a[j]==0)
					continue;
				if(i==j)
				{
					count+=(ll)a[i]*(a[i]-1)/2;
				}
				else if((i+j)%2==0&&a[(i+j)/2]>0)
					count+=(ll)a[i]*(ll)a[j];
			}
		}
		cout<<count<<endl;
	}	
	return 0;
}
