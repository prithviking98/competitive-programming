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
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		vvi l(s.size()),r(s.size());
		int n=s.size();
		ll sum=0;
		rep(i,0,s.size())
		{
			l[i].resize(26);
			rep(j,0,26)
				l[i][j]=0;
			l[i][s[i]-'a']=1;
			if(i==0)
				continue;
			rep(j,0,26)
			{
				l[i][j]+=l[i-1][j];
				if(j<s[i]-'a')
					sum+=l[i][j];
			}
		}
		for(int i=s.size()-1;i>=0;--i)
		{
			r[i].resize(26);
			rep(j,0,26)
				r[i][j]=0;
			r[i][s[i]-'a']=1;
			if(i==n-1)
				continue;
			rep(j,0,26)
				r[i][j]+=r[i+1][j];
		}
		ll mtotal=LLONG_MAX;
		rep(i,0,s.size())
		{
			int ol=0,og=0,v=s[i]-'a';
			rep(j,0,v)
				ol+=l[i][j];
			rep(j,v+1,26)
				og+=r[i][j];
			rep(j,0,26)
			{
				int x=abs(v-j);
				int nl=0,ng=0;
				rep(k,0,j)
					nl+=l[i][k];
				rep(k,j+1,26)
					ng+=r[i][k];
				ll total=sum-ol-og+nl+ng+x;
				if(v!=j)
					total--;
				mtotal=min(total,mtotal);
			}
		}
		cout<<mtotal<<endl;
	}
	return 0;
}
