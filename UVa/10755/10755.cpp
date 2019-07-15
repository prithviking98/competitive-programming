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
	int T;
	cin>>T;
	while(T--)
	{
		int a,b,c;
		cin>>a>>b>>c;
		vector<vector<vector<ll> > > m(a,vector<vector<ll> >(b, vector<ll>(c)));
		for(int i=0;i<a;++i)
		{
			for(int j=0;j<b;++j)
			{
				for(int k=0;k<c;++k)
				{
					cin>>m[i][j][k];
					if(i>0)
						m[i][j][k]+=m[i-1][j][k];
					if(j>0)
						m[i][j][k]+=m[i][j-1][k];
					if(k>0)
						m[i][j][k]+=m[i][j][k-1];
					if(i>0&&j>0)
						m[i][j][k]-=m[i-1][j-1][k];
					if(i>0&&k>0)
						m[i][j][k]-=m[i-1][j][k-1];
					if(j>0&&k>0)
						m[i][j][k]-=m[i][j-1][k-1];
					if(i>0&&j>0&&k>0)
						m[i][j][k]+=m[i-1][j-1][k-1];
				}
			}
		}
		ll ans=LONG_MIN,sum=0;
		rep(i,0,a)
			rep(j,0,b)
				rep(k,0,c)
					rep(x,i,a)
						rep(y,j,b)
							rep(z,k,c)
							{
								sum=m[x][y][z];
								if(i>0)
									sum-=m[i-1][y][z];
								if(j>0)
									sum-=m[x][j-1][z];
								if(k>0)
									sum-=m[x][y][k-1];
								if(i>0&&j>0)
									sum+=m[i-1][j-1][z];
								if(i>0&&k>0)
									sum+=m[i-1][y][k-1];
								if(j>0&&k>0)
									sum+=m[x][j-1][k-1];
								if(i>0&&j>0&&k>0)
									sum-=m[i-1][j-1][k-1];
								ans=max(ans,sum);
							}
		cout<<ans<<endl;
		if(T>0)
			cout<<endl;
	}
	return 0;
}
