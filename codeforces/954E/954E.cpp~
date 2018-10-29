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

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

struct tap
{
	ll t,w;
};

bool comp(tap &a,tap &b)
{
	if(a.t!=b.t)
		return a.t>b.t;
	else
		return a.w>b.w;
}
int main()
{
	ios::sync_with_stdio(0);
	const long double eps=1e-7;
	int n,t;
	cin>>n>>t;
	vector <tap> a(n);
	rep(i,0,n)
		cin>>a[i].w;
	rep(i,0,n)
		cin>>a[i].t;
	sort(a.begin(),a.end(),comp);
	long double sum=0,water=0;
	rep(i,0,n)
	{
		sum+=a[i].t*a[i].w;
		water+=a[i].w;
	}
	int i;
	if(sum/water-t<-eps)
	{
		i=n-1;
//		cout<<"test less"<<endl;
		while(i>=0&&abs(sum/water-t)>eps)
		{
//			trace2(sum/water,t);
			long double f=0;
			long double w=a[i].w;
			for(long double b=a[i].w;b>=eps;b/=2)
				while(b+f<=w&&(sum-a[i].t*(b))/(water-b)<t&&(abs((sum-a[i].t*(b))/(water-b)-t)<=abs(sum/water-t)))
				{
					f+=b;
					sum-=a[i].t*b;
					water-=b;
				}
			i--;
		}
		printf("%0.6Lf\n",water);
	}
	else if(sum/water-t>eps)
	{
		i=0;
		while(i<n&&abs(sum/water-t)>eps)
		{
//			trace3(i,sum/water,t);
			long double f=0.0;
			long double w=a[i].w;
			for(long double b=w;b>=eps;b/=2)
			{
//				trace1(b);
				while(b+f<=w&&(sum-a[i].t*(b))/(water-b)>t&&(abs((sum-a[i].t*(b))/(water-b)-t)<=abs(sum/water-t)))
				{
					f+=b;
//					trace1(f);
					sum-=a[i].t*b;
					water-=b;
//					trace2(sum,water);
				}
			}
			i++;
		}
		printf("%0.6Lf\n",water);
	}
	else
	{
//		cout<<"test"<<endl;
		cout<<water<<endl;
		return 0;
	}
	return 0;
}
