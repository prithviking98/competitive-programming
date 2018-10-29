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
	string s;
	cin>>s;
	int m;
	cin>>m;
	while(m--)
	{
		int l,r,k;
		cin>>l>>r>>k;
		l--;
		r--;
		k=k%(r-l+1);
		string ts=s;
		for(int i=l;i<=r;++i)
		{
			ts[((i+k-l)%(r-l+1))+l]=s[i];
		}
		s=ts;
	}
	cout<<s<<endl;

	return 0;
}
