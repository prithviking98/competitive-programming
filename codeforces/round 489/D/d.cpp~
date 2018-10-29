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

bool isOverflow(ll a,ll b)
{
	if(a>INT_MAX/(long double)b)
		return true;
	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	ll n,k;
	cin>>n>>k;
	vi a(n);
	rep(i,0,n) cin>>a[i];
	vi p;
	p.PUB(-1);
	rep(i,0,n)
		if(a[i]>1)
			p.PUB(i);
	p.PUB(n);
//	tracev(p);
	ll count=0;
	rep(i,0,n)
	{
		int f=0;
		for(int b=p.size()-1;b>=1;b/=2)
			while(f+b<p.size()&&p[f+b]<i)
				f+=b;
		if(p.size()&&p[f]<i)
			f++;
		int j;
		j=f;
//		trace2(i,j);
		ll prod,sum;
		sum=a[i];
		prod=a[i];
//		trace2(prod,sum);
		while(prod<2e18+1&&prod>0)
		{
			if(p[j]==i)
			{
				if(k==1)
					count++;
				j++;
				continue;
			}
			ll r=prod-k*sum;
			ll ones=a[i]==1?p[j]-max(i,p[j-1]):p[j]-max(i,p[j-1])-1;
			if(r>=0&&r<=ones*k&&(r%k==0))
				count++;
//			trace1(count);
			if(j==p.size()-1)
				break;
//			trace2(j,p[j]);
			if(isOverflow(prod,a[p[j]]))
					break;
			prod=prod*a[p[j]];
			sum=sum+a[p[j]]+p[j]-max(i,p[j-1])-1;
//			trace2(prod,sum);
			j++;

		}
	}
	cout<<count<<endl;
	return 0;
}
