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
	int n,m;
	cin>>n>>m;
	vi a(n+1);
	rep(i,1,n+1)
		cin>>a[i];
	a.PUB(m);
	tracev(a);
	vi os(n+2),es(n+2);
	int odd=0;
	for(int i=n;i>=0;--i)
	{
		if(i%2==1)
		{
			es[i]=es[i+1]+a[i+1]-a[i];
			os[i]=os[i+1];
		}
		else
		{
			os[i]=os[i+1]+a[i+1]-a[i];
			es[i]=es[i+1];
		}
	}
	tracev(os);
	tracev(es);
	int total=0,mtotal=os[0];
	rep(i,0,n+1)
	{
		if(i%2==0)
			total+=a[i+1]-a[i];
		if(a[i+1]-a[i]==1)
			continue;
		if(i%2==0)
		{
			trace1(total);
			int t=total-1+es[i+1];
			trace3(i,a[i],t);
			mtotal=max(t,mtotal);
		}
		else
		{
			trace1(total);
			int t=total-1+a[i+1]-a[i]+es[i+1];
			trace3(i,a[i],t);
			mtotal=max(t,mtotal);
		}
	}
	cout<<mtotal<<endl;
	return 0;
}
