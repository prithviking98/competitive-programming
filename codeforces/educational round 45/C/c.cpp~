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

int check(string s)
{
	vector<char> stack;
	rep(i,0,s.size())
	{
		if(s[i]=='(')
			stack.PUB('(');
		else 
		{
			if (stack.empty())
				return 1;
			stack.POB();
		}
	}
	if(stack.empty())
		return 0;
	return -1;
}
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vector<string> s(n);
	rep(i,0,n)
		cin>>s[i];
	vi open(3e5+1),close(3e5+1);
	int balcount=0;
	rep(i,0,n)
	{
		int b=check(s[i]);
		if(b==0)
			balcount++;
		if(b==-1)
		{
			int op=0,flag=0;;
			rep(j,0,s[i].size())
			{
				if(s[i][j]=='(')
					op++;
				else
					op--;
				if(op<0)
				{
					flag=1;
					break;
				}
			}
			if(flag)
				continue;
			open[op]++;
		}
		else
		{
			int cl=0,flag=0;
			for(int j=s[i].size()-1;j>=0;--j)
			{
				if(s[i][j]==')')
					cl++;
				else
					cl--;
				if(cl<0)
				{
					flag=1;
					break;
				}
			}
			if(flag)
				continue;
			close[cl]++;
		}
	}
	ll p=0;
	p=(ll)balcount*balcount;
	rep(i,1,3e5+1)
	{
//		if(open[i]&&close[i])
//			trace3(i,open[i],close[i]);
		p=p+(ll)open[i]*close[i];
	}
	cout<<p<<endl;
	return 0;
}
