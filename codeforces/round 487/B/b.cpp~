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
	int n,p;
	cin>>n>>p;
	string s;
	cin>>s;
	int flag=0;
	rep(i,0,n-p)
	{
		if(s[i]=='.')
		{
			if(s[i+p]=='.')
			{
				s[i]='1';
				s[i+p]='0';
			}
			else
				s[i]=s[i+p]=='0'?'1':'0';
			flag=1;
			break;
		}
		else
		{
			if(s[i+p]=='.')
			{
				s[i+p]=s[i]=='0'?'1':'0';
				flag=1;
				break;
			}
			else if(s[i]!=s[i+p])
			{
				flag=1;
				break;
			}
		}
	}
	rep(i,0,n)
		if(s[i]=='.')
			s[i]='1';
	if(flag==1)	
		cout<<s<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
