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

bool comp(char &a,char &b)
{
	if(a<b&&abs(a-b)==1)
		return true;
	return false;
}
int main()
{
	ios::sync_with_stdio(0);
	string s;
	cin>>s;
	string ans=s;
	int o,t,z;
	o=0;
	z=0;
	t=0;
	int j=0;
	rep(i,0,s.size())
	{
		if(s[i]=='1')
			o++;
		else if(s[i]=='2')
			t++;
		else if(s[i]=='0'&&t==0)
			z++;
		else if(s[i]=='0'&&t!=0)
		{

			rep(k,j,j+z)
				ans[k]='0';
			j=j+z;
			rep(k,j,j+o)
				ans[k]='1';
			j=j+o;
			rep(k,j,j+t)
				ans[k]='2';
			j+=t;
			o=0;
			z=1;
			t=0;
		}
		trace4(ans,z,o,t);
	}
	rep(k,j,j+z)
		ans[k]='0';
	j=j+z;
	rep(k,j,j+o)
		ans[k]='1';
	j=j+o;
	rep(k,j,j+t)
		ans[k]='2';
	j+=t;
	cout<<ans<<endl;
	return 0;
}
