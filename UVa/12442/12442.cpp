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

int dfs(int i, vi &count,vi &a,vi &v,int &cycle)
{
	if(v[i]&&count[i]==0)
	{
		cycle=1;
		return 0;
	}
	if(count[i]!=0)
		return count[i];
	v[i]=1;
	return count[i]=1+dfs(a[i],count,a,v,cycle);
}

void resolve(int i,vi &count,vi &a)
{
	if(count[a[i]]>count[i])
	{
		count[i]=count[a[i]];
		return;
	}
	resolve(a[i],count,a);
	if(count[a[i]]>count[i])
	{
		count[i]=count[a[i]];
		return;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	rep(i1,0,T)
	{
		int n;
		cin>>n;
		vi a(n);
		rep(i,0,n)
		{
			int u,v;
			cin>>u>>v;
			a[u-1]=v-1;
		}
		vi count(n),v(n),vc(n);
		int cycle;
		rep(i,0,n)
		{
			if(count[i]!=0)
				continue;
			cycle=0;
			count[i]=dfs(i,count,a,v,cycle);
			if(cycle==1)
			resolve(i,count,a);
		}

		int m=0,ans;
		rep(i,0,n)
		{
//			trace2(count[i],i);
			if(m<count[i])
			{
//				trace1(i);
				m=count[i];
				ans=i+1;
			}
		}
		cout<<"Case "<<i1+1<<": "<<ans<<endl;
	}
	return 0;
}
