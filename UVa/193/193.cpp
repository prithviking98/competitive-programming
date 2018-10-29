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

int n,m,k,black,maxblack;
vvi v(101);
vi col(101),sol;

void search(int index)
{
	if(index==n+1)
	{
//		trace1(black);
//		rep(i,1,n+1) trace2(i,col[i]);
		if(maxblack<black)
		{
			maxblack=black;
			sol=col;
		}
		return;
	}
//	trace1(index);
	search(index+1);
	int flag=0;
	rep(i,0,v[index].size())
	{
//		trace3(index,i,v[index][i]);
		if(col[v[index][i]]==1)
		{
			flag=1;
			break;
		}
	}
	if(flag)
		return;
//	trace1(index);
	col[index]=1;
	black++;
	search(index+1);
	col[index]=0;
	black--;
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>m;
	while(m--)
	{
		cin>>n>>k;
		rep(i,1,n+1)
			v[i].clear();
		int u,t;
		rep(i,0,k)
		{
			cin>>u>>t;
			v[u].PUB(t);
			v[t].PUB(u);
		}
		black=0;
		maxblack=0;
		rep(i,0,n+1)
			col[i]=0;
		search(1);
		cout<<maxblack<<endl;
		int flag=1;
//		rep(i,1,n+1) trace2(i,sol[i]);
		rep(i,1,n+1)
			if(sol[i]==1)
			{
				if(flag)
				{
					flag=0;
					cout<<i;
				}
				else
					cout<<" "<<i;
			}
		cout<<endl;
	}
	return 0;
}
