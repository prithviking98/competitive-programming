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
	int n,m;
	cin>>n>>m;
	vi a(m);
	string s;
	int zc=0;
	rep(i,0,n)
	{
		cin>>s;
		int f=0;
		rep(j,0,m)
			if(s[j]=='1')
			{
				f=1;
				a[j]++;
			}
		if(f==0)
			zc++;
	}
	int count=0;
	rep(i,0,m)
		if(a[i]==1)
			count++;
	if(zc)
		cout<<"YES"<<endl;
	else if(count>=n)
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;

	return 0;
}
