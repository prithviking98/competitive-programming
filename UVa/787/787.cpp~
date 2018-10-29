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

int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		vll a;
		ll t;
		while(cin>>t)
		{
			if(t==-999999)
				break;
			a.PUB(t);
		}
		tracev(a);
		if(a.size()==0)
			break;
		ll p=a[0],ans=a[0];
		vll dn(a.size()),dp(a.size());
		dn[0]=a[0]<0?a[0]:0;
		dp[0]=a[0]>=0?a[0]:0;
		rep(i,1,a.size())
		{
			if(a[i]<0)
			{
				if(dn[i-1]<0)
					dp[i]=a[i]*dn[i-1];
				else if(dn[i-1]==0)
					dp[i]=0;
				if(dp[i-1]>0)
					dn[i]=a[i]*dp[i-1];
				else if(dp[i-1]==0)
					dn[i]=a[i];
			}
			else if(a[i]>=0)
			{
				if(dn[i-1]<0)
					dn[i]=a[i]*dn[i-1];
				else if(dn[i-1]==0)
					dn[i]=0;
				if(dp[i-1]>0)
					dp[i]=a[i]*dp[i-1];
				else if(dp[i-1]==0)
					dp[i]=a[i];
			}
			if(dp[i]>0)
				ans=max(ans,dp[i]);
			else if(dp[i]==0&&ans<0)
				ans=max(ans,a[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
