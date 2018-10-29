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
	string u,l;
	cin>>u>>l;
	int b=0;
	rep(i,0,l.length()-1)
	{
		int count=0;
		if(l[i]=='X')
			count++;
		if(l[i+1]=='X')
			count++;
		if(u[i]=='X')
			count++;
		if(u[i+1]=='X')
			count++;
		if(count<=1)
		{
			b++;
			if(l[i]=='X')
				l[i+1]=u[i]=u[i+1]='X';
			else if(u[i]=='X')
				u[i+1]=l[i]=l[i+1]='X';
			else if(u[i+1]=='X')
				l[i+1]=l[i]=u[i]='X';
			else if(l[i+1]=='X')
				u[i+1]=l[i]=u[i]='X';
			else
				u[i+1]=l[i]=u[i]='X';
		}

	}
	cout<<b<<endl;
	return 0;
}
