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
	int t;
	cin>>t;
	rep(i,1,t+1)
	{
		int n;
		cin>>n;
		string s;
		cin>>s;
		vi a(n,-1);
		rep(i,0,n)
			a[i]=s[i]=='.'?0:-1;
		int count=0,l=0,r=0;
		while(l<n)
		{
			while(r<n&&s[r]=='.')
				r++;
			if((r-l)%3==0)
			{
				count=count+(r-l)/3;
				l=r+1;
				r=l;
			}
			else if((r-l)%3==1)
			{
				count=count+(r-l)/3+1;
				l=r+2;
				r=l;
			}
			else
			{
				count=count+(r-l)/3+1;
				l=r+1;
				r=l;
			}
		}
		cout<<"Case "<<i<<": "<<count<<endl;
	}
	return 0;
}
