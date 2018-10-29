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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

struct node
{
	vi a;
	int visited;
};

int bfs(vector<node> &v, int source)
{
	rep(i,0,v.size())
		v[i].visited=0;
	queue <pii> q;
	q.push({1000,0});
	while(!q.empty())
	{
		pii t=q.front();
		q.pop();
		if(!v[t.first].visited)
		{
			v[t.first].visited=1;
			rep(i,0,v[t.first].a.size())
				q.push({v[t.first].a[i],t.second+1});
		}
		else
		{
			if(t.first==source)
				return t.second;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	vi a(1001);
	int count=0;
	rep(i,0,k)
	{
		int j;
		cin>>j;
		if(a[j]==0)
			count++;
		a[j]=1;
	}
	vi da;
	rep(i,0,1001)
		if(a[i]==1)
			da.PUB(i-n);
	if(da.front()*da.back()>0)
	{
		cout<<-1<<endl;
		return 0;
	}

	vector <node> v(2002);

	rep(i,0,2002)
	{
		rep(j,0,da.size())
		{
			//trace2(i,da[j]);
			if(da[j]+i<=2001&&da[j]+i>=0)
				v[i].a.PUB(da[j]+i);
		}
	}

	int ans=bfs(v,1000);
	cout<<ans<<endl;

	return 0;
}
