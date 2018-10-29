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
	vector<string> s(n);
	rep(i,0,n)
		cin>>s[i];
	vi v(n);
	int flag=0;
	rep(i,0,n)
	{
		if(v[i])
			continue;
		flag=0;
		v[i]=1;
		rep(j,i+1,n)
		{
			if(v[j])
				continue;
			flag=0;
			int t=0;
			rep(k,0,m)
			{
				if(!t&&(s[j][k]=='#'&&s[i][k]=='#'))
					t=1;
			}
			if(t)
			{
				if(s[j]==s[i])
					v[j]=1;
				else
				{
					flag=1;
					break;
				}

			}
		}
		if(flag)
			break;
	}
	if(flag)
		cout<<"No"<<endl;
	else
		cout<<"Yes"<<endl;


	return 0;
}
