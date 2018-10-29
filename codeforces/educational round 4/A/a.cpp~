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
	int n,p,q;
	cin>>n>>p>>q;
	string s;
	cin>>s;
	int a=min(p,q);
	int b=max(p,q);
	vector<string> v;
	int i=0;
	while(i<s.size()&&(s.size()-1-i+1)/a>0)
	{
		if((s.size()-1-i+1)%b==0)
		{
			while(i<s.size()&&(s.size()-1-i+1)/b>0)
			{
				v.PUB(s.substr(i,b));
				i+=b;
			}
		}
		else
		{
			v.PUB(s.substr(i,a));
			i+=a;
		}
	}
	if(i<s.size())
		cout<<-1<<endl;
	else
	{
		cout<<v.size()<<endl;
		rep(j,0,v.size())
			cout<<v[j]<<endl;
	}

	return 0;
}
