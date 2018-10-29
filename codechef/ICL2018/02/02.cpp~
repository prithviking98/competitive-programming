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

inline int conv(char a)
{
	return a-'a'+1;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		string s;
		cin>>s;
		sort(s.rbegin(),s.rend());
		int p=n*k;
		rep(i,0,n)
		{
			if(conv(s[i])>2*k)
			{
				p=p-2*k+conv(s[i]);
				//trace3(i,s[i],conv(s[i]));
			}
			else 
				break;
		}
		int g=__gcd(p,k);
		int a=p/g;
		int b=k/g;
		cout<<a<<" "<<b<<endl;
	}


	return 0;
}
