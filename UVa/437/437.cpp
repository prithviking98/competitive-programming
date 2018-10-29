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
	int n,t=0;
	while(cin>>n)
	{
		t++;
		if(n==0)
			break;
		vi x,y,z;
		int a,b,c;
		rep(i,0,n)
		{
			cin>>a>>b>>c;
			x.PUB(a);
			x.PUB(b);
			x.PUB(c);
			y.PUB(b);
			y.PUB(c);
			y.PUB(a);
			z.PUB(c);
			z.PUB(a);
			z.PUB(b);
		}
		rep(i,0,3*n)
		{
			rep(j,0,3*n)
			{
				x.PUB(x[j]);
				y.PUB(y[j]);
				z.PUB(z[j]);
			}
		}
		vi maxh(x.size());
		rep(i,0,x.size())
			maxh[i]=z[i];
		int height=0;
		rep(i,0,x.size())
		{
			rep(j,0,i)
			{
				if((x[i]<x[j]&&y[i]<y[j])||(x[i]<y[j]&&y[i]<x[j]))
				{
					if(maxh[i]<maxh[j]+z[i])
						maxh[i]=maxh[j]+z[i];
				}
			}
			height=max(height,maxh[i]);
		}
		cout<<"Case "<<t<<": maximum height = "<<height<<endl;
	}
					


	return 0;
}
