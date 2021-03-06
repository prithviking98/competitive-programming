#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

#define TRACE
#ifdef TRACE
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracea(a,n) rep(II,0,n) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracevv(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define tracem(a,r,c)\
	{\
	rep(II,0,r){\
		rep(JJ,0,c)\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#else
#define trace1(x)   
#define trace2(x,y)   
#define trace3(x,y,z)   
#define trace4(w,x,y,z)  
#define tracev(a) 
#define tracea(a,n)  
#define tracevv(a)  
#define tracem(a,r,c)  
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

vvi a;
vi isArt,v,low,p;
int Time,rc;

void dfs(int r,int dfroot)
{
	v[r]=Time++;
	low[r]=v[r];
	rep(i,0,a[r].size())
	{
		if(v[a[r][i]]==0)
		{
			p[a[r][i]]=r;
			if(r==dfroot)
				rc++;
			dfs(a[r][i],dfroot);
			if(low[a[r][i]]>=v[r])
				isArt[r]=1;
			low[r]=min(low[r],low[a[r][i]]);
		}
		else if(p[a[r][i]]!=a[r][i])
			low[r]=min(low[r],v[a[r][i]]);
	}
}


int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		int n;
		cin>>n;
		if(n==0)
			break;
		a.assign(n+1,vector<int>(0));
		while(1)
		{
			int t;
			cin>>t;
			if(t==0)
				break;
			string s;
			cin.ignore();
			getline(cin,s);
			istringstream is(s);
			int k;
			while(is>>k)
			{
				a[t].PUB(k);
				a[k].PUB(t);
			}
		}
		tracevv(a);
		//debug
		/*
		n=9;
		a.assign(n+1,vector<int>(0));
		a[1].PUB(2);
		a[2].PUB(1);
		a[2].PUB(3);
		a[2].PUB(7);
		a[3].PUB(2);
		a[3].PUB(4);
		a[3].PUB(9);
		a[4].PUB(3);
		a[4].PUB(5);
		a[4].PUB(8);
		a[5].PUB(4);
		a[5].PUB(6);
		a[6].PUB(5);
		a[6].PUB(7);
		a[7].PUB(6);
		a[7].PUB(2);
		a[8].PUB(4);
		a[8].PUB(9);
		a[9].PUB(8);
		a[9].PUB(3);
		*/
		Time=1;
		isArt.assign(n+1,0);
		v.assign(n+1,0);
		low.assign(n+1,0);
		p.assign(n+1,-1);
		rc=0;
		dfs(1,1);
		isArt[1]=rc>1;
		int count=0;
		rep(i,1,n+1)
			count+=isArt[i];
		cout<<count<<endl;

	}
			


	return 0;
}
