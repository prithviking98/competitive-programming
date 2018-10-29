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

const int M=1e9+7;

int power(int a,int p)
{
	int pow=1,x=a;
	while(p>0)
	{
		if(p%2==1)
			pow=((ll)pow*x)%M;
		p/=2;
		x=((ll)x*x)%M;
	}
	return pow;
}

int gcd(int a, int b,int &x,int &y)
{
	if(a==0)
	{
		x=0;
		y=1;
		return b;
	}
	if(b==0)
	{
		y=0;
		x=1;
		return a;
	}
	int x1,y1;
	int g=gcd(b,a%b,x1,y1);
	x=y1;
	y=x1-a/b*y1;
	return g;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	int t=n,count=0;
	while(t%2==0)
	{
		t/=2;
		count++;
	}
	int num,den;
	num=(power(2,n-1-count)-t)%M;
	num=num<0?num+M:num;
	den=power(2,n-1-count);
//	trace2(num,den);
	int a,b;
	gcd(M,den,a,b);
	int ans=((ll)num*b)%M;
	ans=ans<0?ans+M:ans;
	cout<<ans<<endl;
	return 0;
}
