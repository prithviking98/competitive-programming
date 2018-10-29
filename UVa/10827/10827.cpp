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

vvi a;
int total(int i,int j,int k,int l)
{
	int sum=a[k][l];
	if(i>0)
		sum-=a[i-1][l];
	if(j>0)
		sum-=a[k][j-1];
	if(i>0&&j>0)
		sum+=a[i-1][j-1];
	return sum;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		a.resize(n);
		rep(i,0,n)
			a[i].resize(n);
		rep(i,0,n)
			rep(j,0,n)
			cin>>a[i][j];
		rep(i,0,n)
			rep(j,0,n)
			{
				if(i>0)
					a[i][j]+=a[i-1][j];
				if(j>0)
					a[i][j]+=a[i][j-1];
				if(i>0&&j>0)
					a[i][j]-=a[i-1][j-1];
			}
		int ans=INT_MIN;
		rep(i,0,n)
			rep(j,0,n)
				for(int k=i;;)
				{
					for(int l=j;;)
					{
						int sum;
						if(i<=k&&j<=l)
							sum=total(i,j,k,l);
						else if(i<=k&&j>l)
							sum=total(i,j,k,n-1)+total(i,0,k,l);
						else if(i>k&&j<=l)
							sum=total(i,j,n-1,l)+total(0,j,k,l);
						else if(i>k&&j>l)
							sum=total(i,j,n-1,n-1)+total(0,0,k,l)+total(i,0,n-1,l)+total(0,j,k,n-1);
						if(ans<sum)
							ans=sum;
						l=(l+1)%n;
						if(l==j)
							break;
					}
					k=(k+1)%n;
					if(k==i)
						break;
				}
		cout<<ans<<endl;
	}
	return 0;
}
