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
	if(p[u]==-1)
		return u;
	else
	{
		p[u]=find(p,p[u]);
		return p[u];
	}
}

void Union(vi &p,vi &rank,int u,int v)
{
	if(u==v)
		return ;
	int x,y;
	x=find(p,u);
	y=find(p,v);
	if(x==y)
		return;
	if(rank[x]>rank[y])
		p[y]=x;
	else if(rank[y]>rank[x])
		p[x]=y;
	else
	{
		p[y]=x;
		rank[x]++;
	}
}


int main()
{
	ios::sync_with_stdio(0);
	int t;
//	scanf("%d\n",&t);
	cin>>t;
	while(t--)
	{
		int n;
//		scanf("%d\n",&n);
		cin>>n;
		vi p(n+1,-1),r(n+1,0);
		char c;
		int u,v;
		int s=0,f=0;
		string st;
		cin.ignore();
		while(1)
		{
			if(!getline(cin,st)||st.empty())
				break;
//			trace1(st);
			sscanf(st.c_str(),"%c %d %d",&c,&u,&v);
			if(c=='c')
			{
				Union(p,r,u,v);
			}
			else
			{
//				trace2(u,find(p,u));
//				trace2(v,find(p,v));
				if(find(p,u)==find(p,v))
					s++;
				else
					f++;
			}
		}
		cout<<s<<","<<f<<endl;
		if(t>0)
			cout<<endl;
	}
	return 0;
}
