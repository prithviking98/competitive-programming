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

int n;
vvi a;
vi v,path;
bool isFound;

void dfs(int r,int dist)
{
	v[r]=1;
	for(int i=0;i<a[r].size()&&isFound==false;++i)
	{
		if(a[r][i]!=1&&v[a[r][i]])
			continue;
		else if(a[r][i]==1)
		{
			if(dist==n)
			{
				isFound=true;
				for(int i=0;i<n;++i)
					cout<<path[i]<<" ";
				cout<<1<<endl;
			}
			else
				continue;
		}

		path.push_back(a[r][i]);
		dfs(a[r][i],dist+1);
		path.pop_back();
	}
	v[r]=0;
}

int main()
{
	ios::sync_with_stdio(0);
	string s(10,' ');
	while(getline(cin,s,'\n'))
	{
		sscanf(s.c_str(),"%d",&n);
		a.clear();
		a.resize(n+1);
		v.clear();
		v.resize(n+1);
		//trace1(n)
		while(1)
		{
			getline(cin,s,'\n');
			if(s[0]=='%')
				break;
			int u,v;
			sscanf(s.c_str(),"%d %d",&u,&v);
			//trace2(u,v);
			a[u].push_back(v);
			a[v].push_back(u);
		}
		isFound=false;
		path.push_back(1);
		dfs(1,1);
		path.pop_back();
		if(isFound==false)
			cout<<"N"<<endl;
	}

	return 0;
}
