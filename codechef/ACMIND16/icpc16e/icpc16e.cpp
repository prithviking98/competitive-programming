#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

//#define TRACE
#ifdef TRACE
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracea(a,n) rep(II,0,n) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracevv(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define tracem(a,r,c)\
	{\
	rep(II,0,r){\
		rep(JJ,0,c)\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#else
#define trace1(x)   
#define trace2(x,y)   
#define trace3(x,y,z)   
#define trace4(w,x,y,z)  
#define tracev(a) 
#define tracea(a,n)  
#define tracevv(a)  
#define tracem(a,r,c)  
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

const ll M=1e9+7;

ll modpow(ll a,ll b)
{
	ll p=a,ans=1;
	while(b>0)
	{
		if(b%2==1)
			ans=(ans*p)%M;
		p=(p*p)%M;
		b/=2;
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		ll n,c;
		cin>>n>>c;
		ll ans=0;
		if(n%2==0)
		{
			ll pow1=(((5*(n%(M-1)))%(M-1))*(n%(M-1)))%n; //5n*n
			ll pow2=((((5*(n%(M-1)))%(M-1))*((n/2)%(M-1)))%(M-1))%(M-1);
			ll pow3=((((5*((n/2)%(M-1))%(M-1))*((n/2)%(M-1)))%(M-1)))%(M-1);
			ll q,h,non;
			q=modpow(c,pow3);
			h=(((modpow(c,pow2)-q)%M)/2)%M;
			non=((((modpow(c,pow1)-(2*q)%M)%M-q)%M)/4)%M;
			ans=(((non+q)%M)+h)%M;
		}
		else
		{
			ll pow1=((5*(n%(M-1)))%(M-1)*(n%(M-1)))%(M-1); //5n*n
//			ll pow2=(((((2*(n%(M-1)))%(M-1))*(((n-1)/2)%(M-1)))%(M-1))%(M-1)+n%(M-1))%(M-1);
			ll pow2=((((((2*(n%(M-1)))%(M-1)*(n%(M-1)))%(M-1))+(((n%(M-1))*(((n-1)/2)%(M-1)))%(M-1)))%(M-1))+(n%(M-1)))%(M-1);
			ll pow3=((((((n%(M-1))*(n%(M-1)))%(M-1))+(((((n-1)/2)%(M-1))*(((n-1)/2)%(M-1)))%(M-1)))%(M-1))+1)%(M-1);
			ll q,h,non;
			trace3(pow1,pow2,pow3);
			q=modpow(c,pow3);
			h=(((modpow(c,pow2)-q)%M)/2)%M;
			non=((((modpow(c,pow1)-(2*h)%M)%M-q)%M)/4)%M;
			trace3(q,h,non);
			ans=(((non+q)%M)+h)%M;
		}
		cout<<ans<<endl;
	}
	return 0;
}
