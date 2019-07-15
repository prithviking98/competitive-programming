#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

#define TRACE
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
	int T=0;
	while(true)
	{
		int n,m;
		cin>>n>>m;
		if(n==0)
			break;
		T++;
		vvi a(n,vi(m));
		rep(i,0,n)
			rep(j,0,m)
			{
				cin>>a[i][j];
				if(a[i][j]==1)
					a[i][j]=-10000;
				else
					a[i][j]=1;
				if(i>0)
					a[i][j]+=a[i-1][j];
				if(j>0)
					a[i][j]+=a[i][j-1];
				if(i>0&&j>0)
					a[i][j]-=a[i-1][j-1];
			}
		int ans=0,sum=0;
		rep(i,0,n)
			rep(j,0,m)
				rep(k,i,n)
					rep(l,j,m)
					{
						sum=a[k][l];
						if(i>0)
							sum-=a[i-1][l];
						if(j>0)
							sum-=a[k][j-1];
						if(i>0&&j>0)
							sum+=a[i-1][j-1];
						ans=max(ans,sum);
					}
		cout<<ans<<endl;
	}
	return 0;
}
