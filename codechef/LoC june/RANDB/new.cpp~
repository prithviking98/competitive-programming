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

int main()
{
	ios::sync_with_stdio(0);
	int _t;
	const double eps=1e-6;
	cin>>_t;
	while(_t--)
	{
		ll R,r,p,alpha,t;
		cin>>R>>r>>p>>alpha>>t;
		alpha=alpha%360;
		double avi,avo;
		avi=p/(double)(R-r)*180;
		avo=p/(double)(R+r)*180;
//		trace2(avi,avo);
		double period=360/avi+360/avo;
		ll cycles=0;
		for(;cycles*period<t;++cycles);
		cycles--;
//		trace1(cycles);
		ll in=0;
		double time=cycles*period;
		double pos=(cycles*alpha*2)%360;
		if(t<time+360/avi)
		{
			pos=(t-time)*avi+pos;
		}
		else if(t<time+360/avi+360/avo)
		{
			pos=((int)pos+alpha)%360;
			in=1;
			pos=pos-(t-time-360/avi)*avo;
			if(pos<0)
				pos+=360;
		}
		else 
		{
			pos=((int)pos+2*alpha)%360;
			in=0;
			pos=pos+(t-time-period)*avi;
		}
		printf("%Ld %0.6lf\n",in,pos);
	}
	return 0;
}
