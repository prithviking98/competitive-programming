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

vi a;
int n,total,s;
vvll dp(21,vector<long long>(201));

long long solve(int pos, int sum)
{
	if(dp[pos][sum]!=-1)
		return dp[pos][sum];
	if(pos==n)
	{
		if(sum!=s)
			return dp[pos][sum]=0;
		else
			return dp[pos][sum]=1;
	}
	if(sum>s)
		return dp[pos][sum]=0;
	return dp[pos][sum]=solve(pos+1,sum)+solve(pos+1,sum+a[pos]);
}

int main()
{
	ios::sync_with_stdio(0);
	int m,t=0;
	cin>>m;
	while(m--)
	{
		t+=1;
		string line;
		if(t==1)
			cin.ignore();
		getline(cin,line,'\n');
//		trace1(line);
		a.clear();
		dp.assign(21,vector<long long>(201,-1));
		for(int i=0;i<line.size();)
		{
			int at,l,r;
			l=i;
			while(i<line.size()-1&&line[i]!=' ')
				i++;
			r=i;
			sscanf(line.substr(l,r-l+1).c_str(),"%d",&at);
//			trace2(i,at);
			a.push_back(at);
			i++;
		}
//		tracev(a);
		n=a.size();
		total = 0;
		rep(i,0,a.size())
			total+=a[i];
		if(total%2==1)
		{
			cout<<"NO"<<endl;
			continue;
		}
		s=total/2;
		int ans=solve(0,0);

		if(ans>=1)
			cout<<"YES"<<endl;
		else 
			cout<<"NO"<<endl;
	}
	return 0;
}
