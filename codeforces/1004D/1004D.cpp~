#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

//#define TRACE
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

inline int func(int r,int c,int i,int j, int k)
{
	int v=4*k;
	if(i<k&&j>=k)
	{
		v=v-(k-i)*2+1;
	}
	else if(i>=k&&j<k)
	{
		v=v-(k-j)*2+1;
	}
	else if(i<k&&j<k)
	{
		if(i+j>=k-1)
			v=v-(k-i)*2+1-(k-j)*2+1;
		else
			v=v-(k-i)*2+1-(k-j)*2+1+(k-1-i-j);
	}
	int ri=r-1-i;
	int rj=c-1-j;
	if(ri<k&&rj>=k)
	{
		v=v-(k-ri)*2+1;
	}
	else if(ri>=k&&rj<k)
	{
		v=v-(k-rj)*2+1;
	}
	else if(ri<k&&rj<k)
	{
		if(ri+rj>=k-1)
			v=v-(k-ri)*2+1-(k-rj)*2+1;
		else
			v=v-(k-ri)*2+1-(k-rj)*2+1+(k-1-ri-rj);
	}
	if(i+rj<k-1)
		v=v+k-1-i-rj;
	if(j+ri<k-1)
		v=v+k-1-j-ri;
	trace4(r,c,i,j);
	trace2(k,v);
	return v;
}
int main()
{
	ios::sync_with_stdio(0);
	int t,k;
	cin>>t;
	vi a(t+1);
	int small=INT_MAX,large=0;
	rep(i,0,t)
	{
		cin>>k;
		a[k]++;
		if(k&&a[k]>4*k)
		{
			cout<<-1<<endl;
			return 0;
		}
		large=max(large,k);
		if(k)
			small=min(small,k);
	}
	tracev(a);
	if(a[0]!=1)
	{
		cout<<-1<<endl;
		return 0;
	}
	int r,c,flag;
	for(r=1;r*r<=t;++r)
	{
		if(t%r!=0)
			continue;
		c=t/r;
		rep(i,0,(r+1)/2)
			rep(j,0,(c+1)/2)
			{
				if(i+j!=small&&r-1-i+c-1-j!=large)
					continue;
				flag=1;
				rep(k,1,t+1)
				{
					if(a[k]!=func(r,c,i,j,k))
					{
						flag=0;
						break;
					}
				}
				if(flag)
				{
					cout<<r<<" "<<c<<endl;
					cout<<i+1<<" "<<j+1<<endl;
					return 0;
				}
			}
	}
	cout<<-1<<endl;
	return 0;
}
