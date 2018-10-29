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
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int find(vi &p,int u)
{
	return (p[u]==-1?u:p[u]=find(p,p[u]));
}

int Union(vi &p,vi &r,vi &c,int u,int v)
{
	int x,y;
	x=find(p,u);
	y=find(p,v);
	if(x==y)
		return c[x];
	else if(r[x]>=r[y])
	{
		p[y]=x;
		c[x]+=c[y];
		if(r[x]==r[y])
			r[x]++;
		return c[x];
	}
	else
	{
		p[x]=y;
		c[y]+=c[x];
		return c[y];
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int f;
		cin>>f;
		unordered_set<string> s;
		unordered_map<string,int> m;
		vi p(2e5+1,-1),r(2e5+1),c(2e5+1,1);
		int count=0;
		while(f--)
		{
			string a,b;
			cin>>a>>b;
			if(s.count(a)==0)
			{
				s.insert(a);
				count++;
				m[a]=count;
			}
			if(s.count(b)==0)
			{
				s.insert(b);
				count++;
				m[b]=count;
			}
			int size=Union(p,r,c,m[a],m[b]);
			cout<<size<<endl;
		}
	}
	return 0;
}
