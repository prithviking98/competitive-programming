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
	int n,m;
	int _t=0;
	while(cin>>n>>m)
	{
		_t++;
		vvi a(n),s(n-m+1),sum(n);
		rep(i,0,n)
		{
			a[i].resize(n);
			sum[i].resize(n);
		}
		rep(i,0,n-m+1)
			s[i].resize(n-m+1);
		for(int i=n-1;i>=0;--i)
			rep(j,0,n)
			{
				cin>>a[i][j];
				sum[i][j]=a[i][j];
			}
		rep(i,0,n)
			rep(j,0,n)
			{
				if(i>0)
					sum[i][j]+=sum[i-1][j];
				if(j>0)
					sum[i][j]+=sum[i][j-1];
				if(i>0&&j>0)
					sum[i][j]-=sum[i-1][j-1];
			}
		rep(i,m-1,n)
			rep(j,m-1,n)
			{
				int r,c;
				r=i-m+1;
				c=j-m+1;
				s[r][c]=sum[i][j];
				if(r>0)
					s[r][c]-=sum[r-1][j];
				if(c>0)
					s[r][c]-=sum[i][c-1];
				if(r>0&&c>0)
					s[r][c]+=sum[r-1][c-1];
			}
		if(_t>1)
			cout<<endl;
		ll total=0;
		for(int i=n-m;i>=0;--i)
			rep(j,0,n-m+1)
			{
				cout<<s[i][j]<<endl;
				total+=s[i][j];
			}
		cout<<total<<endl;
	}
	return 0;
}
