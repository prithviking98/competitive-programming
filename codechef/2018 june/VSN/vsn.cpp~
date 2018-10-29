#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define printv(a) cout<<#a<<".x="<<a.x<<" "<<#a<<".y="<<a.y<<" "<<#a<<".z="<<a.z<<endl
#define eps 1e-7

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

struct vec
{
	long double x,y,z;
	vec operator  -(const vec & a) const
	{
		vec b;
		b.x=x-a.x;
		b.y=y-a.y;
		b.z=z-a.z;
		return b;
	}
	long double operator !() const
	{
		double d;
		d=sqrt(x*x+y*y+z*z);
		return d;
	}
	vec operator *(const vec& a) const
	{
		vec c;
		c.x=y*a.z-z*a.y;
		c.y=x*a.z-z*a.x;
		c.z=x*a.y-y*a.x;
		return c;
	}
	vec operator ++() const
	{
		vec a;
		long double d=!(*this);
		a.x=x/d;
		a.y=y/d;
		a.z=z/d;
		return a;
	}
};

vec p,q,d,c;
long double r;

long double sd(long double t)
{
	vec qt={q.x+d.x*t,q.y+d.y*t,q.z+d.z*t};
	vec k=qt-c;
	return !(k*(++(qt-p)));
}
	
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		long double x,y,z;
		cin>>x>>y>>z;
		p={x,y,z};
		cin>>x>>y>>z;
		q={x,y,z};
		cin>>x>>y>>z;
		d={x,y,z};
		cin>>x>>y>>z;
		c={x,y,z};
		cin>>r;
		if(sd(0)<sd(eps))
		{
			long double t=0,b=1e9;
			for(;b>=eps;b/=2)
				while(t+b<1e9&&sd(t+b)<=r)
					t+=b;
			t+=eps;
			printf("%0.6Lf\n",t);
		}
		else
		{
			long double t=0,b=1e9;
			for(;b>=eps;b/=2)
				while(t+b<1e9&&sd(t+b)>sd(t+b+eps))
					t+=b;
			t+=eps;
			b=1e9;
			for(;b>=eps;b/=2)
				while(t+b<1e9&&sd(t+b)<=r)
					t+=b;
			t+=eps;
			printf("%0.6Lf\n",t);
		}
	}
	trace3(sizeof(float),sizeof(double),sizeof(long double));

	return 0;
}
