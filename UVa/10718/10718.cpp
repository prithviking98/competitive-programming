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
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	unsigned int n,l,u;
	while(cin>>n>>l>>u)
	{
		unsigned int k=0,m=n;
		rep(i,0,32)
		{
			if((k|(1<<(31-i)))<=u)
			{
//				trace2((k&(~(1<<(31-i)))),l);
				if((n&(1<<(31-i)))==0)
				{
					k=k|(1<<(31-i));
				}
				else if(k<l)
				{
//					trace3(k,l,i);
//					trace1((l&(1<<(31-i))));
					if(l&(1<<(31-i)))
						k=k|(1<<(31-i));
//					trace2(k,l);
				}

			}
		}
		cout<<k<<endl;
	}

	return 0;
}
