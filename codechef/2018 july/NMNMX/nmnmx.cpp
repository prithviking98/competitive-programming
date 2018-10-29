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

int n,k;
vi a;
vvi coeff;
const int M=1e9+7;

void compute()
{
	coeff[0][0]=1;
	rep(i,1,n+1)
	{
		coeff[0][i]=0;
		coeff[i][0]=1;
	}
	rep(i,1,n+1)
	{
		rep(j,1,n+1)
		{
			if(j>i)
				coeff[i][j]=0;
			else
				coeff[i][j]=(coeff[i-1][j]+coeff[i-1][j-1])%(M-1);
		}
	}
}

int power(int a,int p)
{
	int prod=1,x=a;
	while(p>0)
	{
		if(p%2==1)
			prod=((ll)prod*x)%M;
		x=((ll)x*x)%M;
		p/=2;
	}
	return prod;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		a.resize(n);
		coeff.resize(n+1);
		rep(i,0,n+1)
			coeff[i].resize(n+1);
		rep(i,0,n)
			cin>>a[i];
		sort(a.begin(),a.end());
		compute();
		int ans=1,pow;
		rep(i,0,n)
		{
			pow=(coeff[n-1][k-1]-coeff[i][k-1]-coeff[n-i-1][k-1])%(M-1);
			pow=pow<0?pow+(M-1):pow;
			ans=((ll)ans*power(a[i],pow))%M;
		}
		cout<<ans<<endl;
	}
	return 0;
}
