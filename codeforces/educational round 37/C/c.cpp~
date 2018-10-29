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
	int n;
	cin>>n;
	vi a(n+1),m(n+1);
	rep(i,1,n+1)
		cin>>a[i];
	string s;
	cin>>s;
	rep(i,0,n-1)
		m[i+1]=s[i]-'0';
//	rep(i,1,n+1)
//		trace2(a[i],m[i]);
	int i=1;
	while(i<=n)
	{
		//trace1(i);
		if(m[i]==0&&a[i]!=i)
			break;
		else if(m[i]==0&&a[i]==i)
			++i;
		else if(m[i]==1)
		{
			int j=i;
			while(j<=n&&m[j]==1)
				++j;
			if(j==n+1)
				j=n;
			int t=i,flag=0;
			while(t<=j)
			{
				if(!(a[t]>=i&&a[t]<=j))
				{
					flag=1;
					break;
				}
				++t;
			}
			if(flag)
				break;
			i=j+1;
		}
	}
	if(i<n+1)
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;

	return 0;
}
