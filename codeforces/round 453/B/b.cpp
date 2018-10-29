#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

struct node
{
	vi adj;
};

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vector <node> v(n+1);
	int t;
	rep(i,2,n+1)
	{
		cin>>t;
		v[t].adj.PUB(i);
	}
	vi c(n+1);
	rep(i,0,n)
		cin>>c[i+1];
	int count=0;
	rep(i,1,n+1)
	{
		rep(j,0,v[i].adj.size())
			if(c[i]!=c[v[i].adj[j]])
				count++;
	}
	cout<<count+1;

	return 0;
}
