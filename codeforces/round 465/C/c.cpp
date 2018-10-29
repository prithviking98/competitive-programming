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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

inline double dist(double x,double y,double a,double b)
{
	return sqrt(pow(x-a,2)+pow(y-b,2));
}
int main()
{
	ios::sync_with_stdio(0);
	double r,x,a,y,b;
	cin>>r>>x>>y>>a>>b;
	if(dist(x,y,a,b)>r)
	{
		cout<<x<<" "<<y<<" "<<r<<endl;
	}
	else
	{
		double s=dist(x,y,a,b);
		double xw,yw,rw;
		if(s==0)
		{
			xw=x-r/2;
			yw=y;
			rw=r/2;
		}
		else
		{
		xw=(((r+s)/2*x)-(r-s)/2*a)/s;
		yw=(((r+s)/2*y)-(r-s)/2*b)/s;
		rw=(r+s)/2;
		}
		printf("%0.9f %0.9f %0.9f\n",xw,yw,rw);
	}
		
	return 0;
}
