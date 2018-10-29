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

vll b1(100005,0),b2(100005,0);
ll n,c;

void update(vll &b,ll x,ll v)
{
	for(;x<=n;x+=(x&-x))
		b[x]+=v;
}
void update(ll l,ll r,ll v)
{
	update(b1,l,v);
	update(b1,r+1,-v);
	update(b2,l,v*(l-1));
	update(b2,r+1,-v*r);
}

ll query(vll &b,ll p)
{
	ll sum=0;
	for(;p>0;p-=(p&-p))
		sum+=b[p];
	return sum;
}

ll query(ll p)
{
	return query(b1,p)*p-query(b2,p);
}

ll query(ll l,ll r)
{
	return query(r)-query(l-1);
}
int main()
{
	ios::sync_with_stdio(0);
	ll t;
	cin>>t;
	while(t--)
	{
		cin>>n>>c;
		rep(i,0,c)
		{
			ll k,p,q,v;
			cin>>k;
			if(k==0)
			{
				cin>>p>>q>>v;
				update(p,q,v);
			}
			else
			{
				cin>>p>>q;
				printf("%lld\n",query(p,q));
			}
		}
	}
	return 0;
}
