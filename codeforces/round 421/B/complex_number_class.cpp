
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
#define PI 3.1415926535
typedef long long ll;
typedef vector<int> vi;

class point 
{
public:
	double r,t,x,y;
	point()
	{
		r=1;
		t=0;
		x=1;
		y=0;
	}
	void calcxy()
	{
		x=r*cos(t);
		y=r*sin(t);
	}
	void calcrt()
	{
		r=sqrt(x*x+y*y);
		t=atan2(y,x);
	}
};

double angle(point v1,point v2,point v3)
{
	point a,b;
	a.x=v1.x-v2.x;
	a.y=v1.y-v2.y;
	a.calcrt();
	b.x=v3.x-v2.x;
	b.y=v3.y-v2.y;
	b.calcrt();
	double angle;
	//cout<<"b and a angles "<<180/PI*b.t<<" "<<180/PI*a.t<<endl;
	angle=abs(b.t-a.t);
	if(angle>PI)
		angle=2*PI-angle;
	return angle;
}
