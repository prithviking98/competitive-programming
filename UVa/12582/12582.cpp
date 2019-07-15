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

void dfsFill(int pos,vi &s,vi &v,vvi &a)
{
	if(v[s[pos]])
		return;
	v[s[pos]]=1;
	for(int i=pos+1;s[i]!=s[pos];i++)
	{
		if(v[s[i]])
			continue;
		a[s[pos]].PUB(s[i]);
		a[s[i]].PUB(s[pos]);
		dfsFill(i,s,v,a);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	rep(t,0,T)
	{
		string S;
		cin>>S;
		vi s(S.size());
		rep(i,0,S.size())
			s[i]=S[i]-'A';

		vi v(26);
		vvi a(26);
		dfsFill(0,s,v,a);
		cout<<"Case "<<t+1<<endl;
		rep(i,0,26)
		{
			if(a[i].size()==0)
				continue;
			char c='A'+i;
			cout<<c<<" = "<<a[i].size()<<endl;
		}
	}
	return 0;
}
