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

int n,Time;
vvi a;
vi v,low,p;
vector<pii> link;

void dfs(int r)
{
	v[r]=low[r]=Time++;

	rep(i,0,a[r].size())
	{
		int cur=a[r][i];
		if(v[cur]==-1)
		{
			p[cur]=r;
			dfs(cur);

			if(low[cur]>v[r])
				link.PUB({r,cur});
			low[r]=min(low[r],low[cur]);
		}
		else if(p[r]!=cur)
			low[r]=min(low[r],v[cur]);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int T=0;
	while(cin>>n)
	{
		T++;
		if(T>1)
			cout<<endl;
		if(n==0||n==1)
		{
			cout<<"0 critical links"<<endl;
			continue;
		}
		trace1(n);
		a.assign(n,vi(0));
		rep(i,0,n)
		{
			int cur,num,v;
			string s;
			cin>>cur;
			cin>>s;
			sscanf(s.c_str(),"(%d)",&num);
			rep(j,0,num)
			{
				cin>>v;
				a[cur].PUB(v);
				a[v].PUB(cur);
			}
		}

		tracevv(a);
		v.assign(n,-1);
		low.assign(n,-1);
		p.assign(n,-1);
		link.clear();
		Time=0;

		rep(i,0,n)
			if(v[i]==-1)
				dfs(i);
		cout<<link.size()<<" critical links"<<endl;
		sort(link.begin(),link.end());
		
		rep(i,0,link.size())
			cout<<link[i].first<<" - "<<link[i].second<<endl;
	}
	return 0;
}
