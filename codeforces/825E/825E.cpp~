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


int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vvi rev(n+1);
	vi out(n+1);
	rep(i,0,m)
	{
		int u,v;
		cin>>u>>v;
		out[u]++;
		rev[v].PUB(u);
	}
	priority_queue<int> pq;
	rep(i,1,n+1)
		if(out[i]==0)
			pq.push(i);
	vi label(n+1);
	int l=n;;
	while(!pq.empty())
	{
		int u=pq.top();
//		trace1(u);
		pq.pop();
		label[u]=l;
		--l;
		rep(i,0,rev[u].size())
		{
			out[rev[u][i]]--;
			if(out[rev[u][i]]==0)
				pq.push(rev[u][i]);
		}
	}
	rep(i,1,n+1)
		cout<<label[i]<<" ";
	cout<<endl;
	return 0;
}
