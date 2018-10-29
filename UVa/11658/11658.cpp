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

int n,x,s;
vi a(105);
vector<vector<double> > dp(105);

double search(int index,int sum)
{
	if(dp[index][sum]!=-1)
		return dp[index][sum];
	if(index==n)
	{
		if(sum<5000)
			return 0;
		double t=(double)s/sum*100;
		return t;
	}
	dp[index][sum]=search(index+1,sum+a[index]);
	if(index==x)
		return dp[index][sum];
	return dp[index][sum]=max(dp[index][sum],search(index+1,sum));
}
int main()
{
	ios::sync_with_stdio(0);
	rep(i,0,105)
		dp[i].resize(10005);
	while(cin>>n>>x)
	{
		if(n==0)
			break;
		x--;
		float f;
		rep(i,0,n)
		{
			cin>>f;
			a[i]=f*100;
		}
		s=a[x];
		trace1(n);
		tracea(a,n);
		rep(i,0,n+1)
			rep(j,0,10001)
				dp[i][j]=-1;
//		int ans=search(0,0);
		double fans=search(0,0);
//		int temp=ans;
//		vi b(5);
//		int i=0;
//		while(temp>0)
//		{
//			b[i]=temp%10;
//			temp/=10;
//			i++;
//		}
//		if(b[4]!=0)
//			cout<<b[4];
//		if(b[3]!=0||b[4]!=0)
//			cout<<b[3];
//		cout<<b[2]<<"."<<b[1]<<b[0]<<endl;
//		cout<<ans<<endl;
//		cout<<ans/100<<"."<<ans%100<<endl;
		printf("%0.2f\n",fans);
	}
	return 0;
}
