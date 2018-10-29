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
	ll n;
	cin>>n;
	vector<pair<ll,int> > a;
	rep(i,0,n)
	{
		ll u,v;
		cin>>u>>v;
		a.PUB({u,-1});
		a.PUB({v,1});
	}
	sort(a.begin(),a.end());
	rep(i,0,2*n)
		trace3(i,a[i].first,a[i].second);
	ll k=0;
	vll count(n+1);
	rep(i,0,2*n)
	{
		if(a[i].second==-1)
		{
			if(i>0)
				count[k]+=(a[i].first-a[i-1].first);
			if(i>0&&a[i-1].second==1)
				count[k]--;
			trace1(-1);
			trace2(k,count[k]);
			k++;
		}
		else
		{
			trace1(1);
			count[k]+=(a[i].first-a[i-1].first+1);
			if(a[i-1].second==1)
				count[k]--;
			trace2(k,count[k]);
			k--;
		}
	}
	rep(i,1,n+1)
		cout<<count[i]<<" ";
	cout<<endl;
	return 0;
}
