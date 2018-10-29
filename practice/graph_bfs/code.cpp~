#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define pb(i) push_back(i)
typedef long long ll;
typedef vector<int> vi;

struct node
{
	int col,d,p;
	vi adj;
};

void bfs(vector <node> & v, int s)
{
	v[s].p=-1;
	v[s].d=0;
	rep(i,0,v.size())
		v[i].col=0;
	queue <int> q;
	q.push(s);
	while(q.size()>0)
	{
		int i=q.front();
		q.pop();
		rep(j,0,v[i].adj.size())
		{
			if(v[v[i].adj[j]].col==0)
			{
				v[v[i].adj[j]].col=1;
				v[v[i].adj[j]].p=i;
				v[v[i].adj[j]].d=v[i].d+1;
				q.push(v[i].adj[j]);
			}
		}
		v[i].col=1;
	}
}

void printpath(vector <node> v,int start,int stop)
{
	if(start==stop)
		cout<<stop<<" -> ";
	else
	{
		printpath(v,start,v[stop].p);
		cout<<stop<<" -> ";
	}
}
int main()
{
	int n;
	cin>>n;
	vector <node> v(n);
	int i=0;
	int k;
	while(i<n)
	{
		cin>>k;
		if(k==-1)
		{
			++i;
		}
		else
		{
			v[i].adj.pb(k);
		}
	}
	bfs(v,0);
	rep(i,0,n)
	{
		cout<<"node :"<<i<<endl;
		cout<<"distance :"<<v[i].d<<endl;
		cout<<"parent :"<<v[i].p<<endl;
		cout<<endl;
	}
	printpath(v,0,7);
	return 0;
}
