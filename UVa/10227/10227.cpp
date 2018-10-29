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

void Union(vi &p,vi &r,int u,int v)
{
	int x,y;
	x=find(p,u);
	y=find(p,v);
	if(x==y)
		return ;
	else if(r[x]>r[y])
		p[y]=x;
	else if(r[y]>r[x])
		p[x]=y;	
	else
	{
		p[x]=y;
		r[y]++;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int k;
	cin>>k;
	while(k--)
	{
		int p,t;
		cin>>p>>t;
		vector<bitset<101> > op(p+1);
		vi par(p+1,-1),r(p+1);
		cin.ignore();
		string s;
		while(getline(cin,s)&&!s.empty())
		{
			int u,v;
			sscanf(s.c_str(),"%d %d",&u,&v);
			op[u][v]=1;
//			trace2(u,op[u]);
		}
		for(int i=1;i<=p;++i)
		{
			if(i>1&&par[i]!=-1)
				continue;
			rep(j,i+1,p+1)
			{
//				trace2(i,j);
				if(op[i]==op[j])
				{
					Union(par,r,i,j);
				}
			}
		}
		int count=0;
		rep(i,1,p+1)
			if(par[i]==-1)
				count++;
		cout<<count<<endl;
		if(k>0)
			cout<<endl;
	}

	return 0;
}
