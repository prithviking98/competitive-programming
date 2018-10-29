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
	cin>>n>>m;
	if(n==1&&m>0)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	else if(m<n-1||(ll)m>(ll)n*(n-1)/2)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	vvi g(n+1);
	int count=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=i+1;j<n+1;++j)
		{
			if(__gcd(i,j)==1)
			{
//				trace2(i,j);
				g[i].PUB(j);
				count++;
			}
			if(count==m)
				break;
		}
		if(count==m)
			break;
	}
	if(count<m)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	cout<<"Possible"<<endl;
	rep(i,1,n+1)
		rep(j,0,g[i].size())
			cout<<i<<" "<<g[i][j]<<endl;
	return 0;
}
