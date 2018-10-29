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
	int a;
	vi adj;
};

int bfs(vector<node> &v, int source, vi &a,int s)
{
	queue<pii> q;
	unordered_set<int> type;
	unordered_set<int> visited;
	type.insert(a[source]);
	q.push({source,0});
	int count=1,cost=0;
	while(!q.empty()&&count<s)
	{
		pii t=q.front();
		q.pop();
		int u=t.first;
		int d=t.second;
		if(visited.count(u)==0)
		{
			visited.insert(u);
			if(type.count(a[u])==0)
			{
				type.insert(a[u]);
				count++;
				cost+=d;
			}
			rep(i,0,v[u].adj.size())
			{

				q.push({v[u].adj[i],d+1});
			}
		}
	}
	return cost;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,m,k,s;
	cin>>n>>m>>k>>s;
	vector <node> v(n+1);
	vi a(n+1);
	rep(i,1,n+1)
		cin>>a[i];
	int u,t;
	rep(i,0,m)
	{
		cin>>u>>t;
		v[u].adj.PUB(t);
		v[t].adj.PUB(u);
	}

	rep(i,1,n+1)
		cout<<bfs(v,i,a,s)<<" ";
	cout<<endl;
	return 0;
}
