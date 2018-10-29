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
	vi c(26);
	int n=s.size();
	rep(i,0,n)
		c[s[i]-'a']++;
	for(int i=25;i>=0;--i)
	{
		if(c[i]%2==1)
		{
			int j;
			for( j=0;j<=i;++j)
				if(c[j]%2==1)
					break;
			c[i]--;
			c[j]++;
		}
	}
	string p=s;
	int l=0,r=n-1;
	rep(i,0,26)
	{
		int j;
		for(j=0;j<c[i]/2;++j)
		{
			p[l+j]=(char)(i+'a');
			p[r-j]=(char)(i+'a');
		}
		l+=j;
		r-=j;
		if(c[i]%2==1)
		{
			p[n/2]=(char)(i+'a');
		}
	}
	cout<<p<<endl;

	return 0;
}
