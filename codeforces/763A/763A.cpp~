#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PB push_back
typedef long long ll;
typedef vector<int> vi;

struct node
{
	vi a;
	int col,vf;
	vi ann;
};
int isAnnoying(vector <node> &,int,int);

int canRoot(vector <node> &v,int r)
{
	int deg=v[r].a.size();
	int f=1;
	rep(i,0,deg)
	{
		if(isAnnoying(v,v[r].a[i],r))
		{
			f=0;
			break;
		}
	}
	return f;
}

int isAnnoying(vector <node> &v,int p,int r)
{
	rep(i,0,v[p].a.size())
	{
		int j=v[p].a[i];
		if(j!=r)
		{
			if(v[p].ann[i]==-1)
				v[p].ann[i]=isAnnoying(v,j,p);
			if(v[p].ann[i]==1)
				return 1;
			else if(v[p].ann[i]==0)
			{
				if(v[p].col!=v[j].col)
					return 1;
			}
		}	
	}
	return 0;
}


int main()
{
	int n;
	cin>>n;
	vector <node> v(n);
	int a,b;
	rep(i,0,n-1)
	{
		cin>>a>>b;
		v[b-1].a.PB(a-1);
		v[a-1].a.PB(b-1);
		v[b-1].ann.PB(-1);
		v[a-1].ann.PB(-1);
	}
	rep(i,0,n)
		cin>>v[i].col;
	int f=-1;
	rep(i,0,n)
	{
		if(canRoot(v,i))
		{
			f=i;
			break;
		}
	}
	if(f+1)
		cout<<"YES"<<endl<<f+1<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
