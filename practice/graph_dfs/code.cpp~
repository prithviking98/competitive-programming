#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct node
{
	int p,d,f,col;
	vi adj;
};

void dfsvisit(vector <node> &v, int i, int &time)
{
	++time;
	v[i].col=1;
	v[i].d=time;
	rep(j,0,v[i].adj.size())
		if(v[v[i].adj[j]].col==0)
		{
			v[v[i].adj[j]].p=i;
			dfsvisit(v,v[i].adj[j],time);
		}
	++time;
	v[i].f=time;
}

void dfs(vector <node> &v)
{
	rep(i,0,v.size())
	{
		v[i].p=-1;
		v[i].col=0;
	}
	int time=0;
	rep(i,0,v.size())
		if(v[i].col==0)
			dfsvisit(v,i,time);
}

int main()
{
	int n;
	cin>>n;
	vector <node> v(n);
	int i=0;
	while(i<n)
	{
		int k;
		cin>>k;
		if(k==-1)
		{
			++i;
			continue;
		}
		else
			v[i].adj.push_back(k);
	}
	dfs(v);
	rep(i,0,n)
	{
		cout<<"node : "<<i<<endl;
		cout<<"parent : "<<v[i].p<<endl;
		cout<<"d : "<<v[i].d<<"		f : "<<v[i].f<<endl;
		cout<<endl;
	}
	return 0;
}
