#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

void divide(vector <vi>  &e, int node,int parent, set <int> &a,set <int> &b,char c)
{
	if(c=='a')
		a.insert(node);
	else
		b.insert(node);
	for(int i=0;i<e[node].size();++i)
	{
		if(e[node][i]!=parent)
		{
			if(c=='a')
				divide(e,e[node][i],node,a,b,'b');
			else
				divide(e,e[node][i],node,a,b,'a');
		}
	}
}

int main()
{
	set <int> a,b;
	int n;
	cin>>n;
	vector <vector <int> > e(n+1);
	int u,v;
	rep(i,0,n-1)
	{
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	/*rep(i,1,n+1)
	{
		cout<<i<<" : ";
		rep(j,0,e[i].size())
			cout<<e[i][j];
		cout<<endl;
	}*/
	divide(e,1,0,a,b,'a');
	ll edges;
	edges=a.size()*b.size()-(n-1);
	cout<<edges<<endl;
	return 0;
}
