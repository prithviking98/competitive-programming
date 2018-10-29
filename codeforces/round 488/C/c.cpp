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

struct point
{
	long double x,y;
};
point a1,a2,a3,a4,b1,b2,b3,b4,c;
int l,r,u,d;

bool corner(point b)
{
	if(b.x<=r&&b.x>=l&&b.y<=u&&b.y>=d)
		return true;
	else
		return false;
}

pair<long double,long double> line(point a,point b)
{
	long double m,c;
	m=((long double)b.y-a.y)/((long double)b.x-a.x);
	c=a.y-m*a.x;
	return {m,c};
}

point foot(pair<long double,long double> line)
{
	point p;
	p.x=(line.first*(c.y+line.second)+c.x)/(1+line.first*line.first);
	p.y=line.first*p.x+line.second;
	return p;
}

bool inside(point p,pair<long double,long double> l1,pair<long double,long double> l2)
{
	int k=l1.first/l2.first;
	if(k==-1)
	{
		l1.first*=-1;
		l1.second*=-1;
	}
	if((p.x*l1.first+l1.second-p.y)*(p.x*l2.first+l2.second-p.y)<=0)
		return true;
	return false;
}


int main()
{
	ios::sync_with_stdio(0);
	cin>>a1.x>>a1.y>>a2.x>>a2.y>>a3.x>>a3.y>>a4.x>>a4.y;
	c.x=(a1.x+a2.x+a3.x+a4.x)/4;
	c.y=(a1.y+a2.y+a3.y+a4.y)/4;
	l=min(min(a1.x,a2.x),a3.x);
	r=max(max(a1.x,a2.x),a3.x);
	d=min(min(a1.y,a2.y),a3.y);
	u=max(max(a1.y,a2.y),a3.y);
//	trace4(l,r,d,u);
	cin>>b1.x>>b1.y>>b2.x>>b2.y>>b3.x>>b3.y>>b4.x>>b4.y;
	int flag=0;
	if(corner(b1)||corner(b2)||corner(b3)||corner(b4))
		flag=1;
//	trace1(flag);
	pair<long double,long double> l1,l2,l3,l4;
	l1=line(b1,b2);
	l2=line(b2,b3);
	l3=line(b3,b4);
	l4=line(b4,b1);
	long double d=(r-l)/2*sqrt((long double)2);
//	trace1(d);
	if((inside(a1,l1,l3)&&inside(a1,l2,l4))||(inside(a2,l1,l3)&&inside(a2,l2,l4))||(inside(a3,l1,l3)&&inside(a3,l2,l4))||(inside(a4,l1,l3)&&inside(a4,l2,l4))||(inside(c,l1,l3)&&inside(c,l2,l4)))
		flag=1;
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;

	return 0;
}
