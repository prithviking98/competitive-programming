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
	vvi a(n);
	rep(i,0,n)
		a[i].resize(m);
	rep(i,0,n)
	{
		string s;
		cin>>s;
		rep(j,0,m)
		{
			if(s[j]=='*')
				a[i][j]=-1;
			else if (s[j]=='.')
				a[i][j]=0;
			else
				a[i][j]=s[j]-'0';
		}
	}
	int flag=0;
	rep(i,0,n)
	{
		rep(j,0,m)
		{
			if(a[i][j]==-1)
				continue;
			int count=0;
			int l,r,u,d;
			if(j==0)
				l=0;
			else
				l=j-1;
			if(j==m-1)
				r=j;
			else
				r=j+1;
			if(i==0)
				u=i;
			else
				u=i-1;
			if(i==n-1)
				d=i;
			else
				d=i+1;
			rep(p,u,d+1)
				rep(q,l,r+1)
					if(a[p][q]==-1)
						count++;
			if(count!=a[i][j])
			{
				flag=1;
				break;
			}
		}
		if(flag)
			break;
	}
	if(flag)
		cout<<"NO"<<endl;
	else
		cout<<"YES"<<endl;
	return 0;
}
