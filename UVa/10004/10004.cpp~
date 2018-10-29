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

int n,l,isBP;
vvi a;
vi v;

void bfs(int r,int c)
{
	v[r]=c;
	queue<int> q;
	q.push(r);
	while(!q.empty()&&isBP)
	{
		r=q.front();
		c=v[r];
		q.pop();
		rep(i,0,a[r].size())
		{
			if(v[a[r][i]]==0)
			{
				q.push(a[r][i]);
				v[a[r][i]]=c==1?2:1;
			}
			else if(v[a[r][i]]==c)
			{
				trace4(r,c,a[r][i],v[a[r][i]]);
				isBP=0;
				break;
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		cin>>n;
		if(n==0)
			break;
		a.assign(n,vector<int>(0));
		cin>>l;
		rep(i,0,l)
		{
			int u,v;
			cin>>u>>v;
			a[u].PUB(v);
			a[v].PUB(u);
		}
		tracevv(a);
		v.assign(n,0);
		tracev(v);
		isBP=1;
		rep(i,0,n)
			if(!v[i])
				bfs(i,1);
		if(isBP)
			cout<<"BICOLORABLE."<<endl;
		else
			cout<<"NOT BICOLORABLE."<<endl;
	}
	return 0;
}
