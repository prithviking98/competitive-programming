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

ll pol(vll &a,ll j)
{
	ll x=1;
	ll sum=0;
	rep(i,0,a.size())
	{
		sum+=a[i]*x;
		x*=j;
	}
	return sum;
}
int main()
{
	ios::sync_with_stdio(0);
	ll T;
	cin>>T;
	while(T--)
	{
		ll n;
		cin>>n;
//		trace1(n);
		vll a(n+1);
		rep(j,0,n+1)
			cin>>a[j];
//		tracev(a);
		ll d,k;
		cin>>d>>k;
		ll curv,curi;
		curi=1;
		ll i=1;
		while(1)
		{
			curv=pol(a,i);
//			trace1(curv);
			if(k>=curi&&k<curi+i*d)
			{
				cout<<curv<<endl;
				break;
			}
			else
			{
				curi=curi+i*d;
				i++;
			}
		}
	}
	return 0;
}
