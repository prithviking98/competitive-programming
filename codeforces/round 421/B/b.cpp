
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
int main()
{
	int n,a,i,v1,v2,v3;
	double ang,diff,min;
	cin>>n>>a;
	//cout<<a<<endl;
	vector <point> v(n);
	rep(i,0,n)
	{
		v[i].r=1;
		v[i].t=(2*PI/n)*i;
		v[i].calcxy();
	}

	v1=1;
	v2=2;
	v3=3;
	ang=180/PI*angle(v[0],v[1],v[2]);
	min=abs((double)a-ang);
	for(i=0;i<=n-3;++i)
	{
		ang=180/PI*angle(v[0],v[1],v[2+i]);
		//cout<<ang<<endl;
		diff=abs((double)a-ang);
		//cout<<diff<<endl<<min<<endl;
		if(diff<min)
		{
			v3=3+i;
			min=diff;
		}
	}
	cout<<v1<<" "<<v2<<" "<<v3<<endl;
	return 0;
}
