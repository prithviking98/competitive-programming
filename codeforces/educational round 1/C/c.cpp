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
typedef pair<int,int> pi;

const long double PI=2*3.141592654;

struct vec
{
	int x,y,index;
	long double angle;
	bool operator <(vec &x)
	{
		return angle<x.angle;
	}
	bool operator ==(vec &x)
	{
		return angle==x.angle;
	}
};

void calc(vec &v)
{
	long double cos=(long double)(v.x)/sqrt((long double)(v.x*v.x+v.y*v.y));
	long double hcos=sqrt((cos+1.0)/2.0);
	if(v.y<0)
		hcos=-hcos;
	long double angle=acos(hcos);
	v.angle=4*angle;
}

pair<long double,pi> _diff(vector<vec> &v,int i)
{
	long double n,p;
	pair<long double,pi> min;
	if(i==0)
	{
		n=v[i+1].angle-v[i].angle;
		p=v[v.size()-1].angle-v[i].angle;
		if(n>2*PI/2)
			n=2*PI-n;
		if(p>2*PI/2)
			p=2*PI-p;
		if(p>n)
		{
			min.first=n;
			min.second={i,i+1};
		}
		else
		{
			min.first=p;
			min.second={i,v.size()-1};
		}
	}
	else if(i==v.size()-1)
	{
		n=v[i].angle-v[0].angle;
		p=v[i].angle-v[i-1].angle;

		if(n>2*PI/2)
			n=2*PI-n;
		if(p>2*PI/2)
			p=2*PI-p;
		if(p>n)
		{
			min.first=n;
			min.second={i,0};
		}
		else
		{
			min.first=p;
			min.second={i,i-1};
		}
	}
	else
	{
		n=v[i+1].angle-v[i].angle;
		p=v[i].angle-v[i-1].angle;
		if(n>2*PI/2)
			n=2*PI-n;
		if(p>2*PI/2)
			p=2*PI-p;
		if(p>n)
		{
			min.first=n;
			min.second={i,i+1};
		}
		else
		{
			min.first=p;
			min.second={i,i-1};
		}
	}
	return min;
}


int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vector<vec> v(n);
	rep(i,0,n)
	{
		cin>>v[i].x>>v[i].y;
		v[i].index=i+1;
		calc(v[i]);
	}
	sort(v.begin(),v.end());
	rep(i,0,n)
	{
		trace4(i,v[i].x,v[i].y,v[i].angle);
	}
	pair<long double,pi> min;
	min.first=2*PI;
	rep(i,0,n)
	{
		pair<long double,pi> diff=_diff(v,i);
		if(diff.first<min.first)
		{
			min=diff;
		}
	}
	cout<<v[min.second.first].index<<" "<<v[min.second.second].index<<endl;
	
	return 0;
}
