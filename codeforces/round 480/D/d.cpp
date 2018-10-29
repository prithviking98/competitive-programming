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
		return;
	if(r[x]>r[y])
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
	int n;
	cin>>n;
	vll a(n);
	rep(i,0,n)
		cin>>a[i];
	vi p(n,-1),r(n,0);
	rep(i,0,n)
	{
		rep(j,i+1,n)
		{
			if(a[i]*a[j]>0&&sqrt((long double)a[i]*a[j])==floor(sqrt((long double)a[i]*a[j])))
				Union(p,r,i,j);
		}
	}
	vi count(n+1);
	rep(i,0,n)
	{
		rep(j,i,n)
		{
			if(i==j)
			{
				count[1]++;
				continue;
			}
			count[unique]++;
		}
	}
	rep(i,1,n+1)
		cout<<count[i]<<" ";
	cout<<endl;

	return 0;
}
