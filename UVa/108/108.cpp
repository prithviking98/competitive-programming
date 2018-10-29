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
	int n;
	cin>>n;
	vvi a(n),sum(n);
	rep(i,0,n)
	{
		a[i].resize(n);
		sum[i].resize(n);
	}
	rep(i,0,n)
		rep(j,0,n)
			cin>>a[i][j];
	tracevv(a);
	rep(i,0,n)
	{
		rep(j,0,n)
		{
			sum[i][j]=a[i][j];
			trace3(i,j,sum[i][j]);
			if(i>0)
				sum[i][j]+=sum[i-1][j];
			if(j>0)
				sum[i][j]+=sum[i][j-1];
			if(i>0&&j>0)
				sum[i][j]-=sum[i-1][j-1];
			trace1(sum[i][j]);
		}
	}
	int ans=-127*10000;
	rep(i,0,n)
		rep(j,0,n)
			rep(k,i,n)
				rep(l,j,n)
				{
					int s=sum[k][l];
					trace1(s);
					if(i>0)
						s-=sum[i-1][l];
					if(j>0)
						s-=sum[k][j-1];
					if(i>0&&j>0)
						s+=sum[i-1][j-1];
					trace4(i,j,k,l);
					trace1(s);
					ans=max(ans,s);
				}
	cout<<ans<<endl;
	return 0;
}
