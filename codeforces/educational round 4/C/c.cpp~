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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

void match(string &s,vi &m,int i,int &j)
{
	if(i==s.size()||j==s.size())
		return;
	else
	{
		int start=i,cur;
		while(s[i]=='(')
		{
			++i;
			++j;
		}
		--i;
		while(i>=start&&j<s.size())
		{
			m[i]=j;
			m[j]=i;
			--i;
			++j;
			cur=j;
			if(s[j]=='(')
			{
				match(s,m,j,j);
				if(m[cur]==-1)
					break;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	string s;
	cin>>s;
	string ss=s;
	rep(i,0,ss.size())
	{
		if(ss[i]=='{'||ss[i]=='('||ss[i]=='<'||ss[i]=='[')
			ss[i]='(';
		else
			ss[i]=')';
	}
	vi m(s.size(),-1);
	int k=0;
	match(ss,m,0,k);
	int flag=1;
	rep(i,0,s.size())
	{
		if(m[i]==-1)
		{
			flag=0;
			break;
		}
	}
	/*
	rep(i,0,m.size())
		trace2(i,m[i]);
		*/
	if(flag==0)
		cout<<"Impossible"<<endl;
	else
	{
		int count=0;
		rep(i,0,s.size())
			if(abs(s[i]-s[m[i]])>2)
				count++;
		count/=2;
		cout<<count<<endl;
	}
	return 0;
}
