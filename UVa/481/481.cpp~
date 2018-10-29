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

void print(vi &a,vi &p, int i)
{
	if(i==-1)
		return;
	print(a,p,p[i]);
	cout<<a[i]<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	vi a;
	while(cin>>t)
	{
		a.PUB(t);
	}
	int n=a.size();
	vi d,index,p(n,-1);
	rep(i,0,n)
	{
		int f=-1;
		for(int b=d.size();b>=1;b/=2)
			while(f+b<d.size()&&d[f+b]<a[i])
				f+=b;
		if(f==d.size()-1)
		{
			if(d.size()>0)
				p[i]=index.back();
			d.PUB(a[i]);
			index.PUB(i);
		}
		else
		{
			if(f==-1)
				p[i]=-1;
			else
				p[i]=index[f];
			if(d[f+1]>=a[i])
			{
				d[f+1]=a[i];
				index[f+1]=i;
			}
		}
	}
	cout<<d.size()<<endl;
	cout<<"-"<<endl;
	int i=index.back();
	print(a,p,i);
	return 0;
}
