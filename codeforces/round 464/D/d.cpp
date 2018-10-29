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

struct spell
{
	 char a,b;
	bool operator <(const spell &x)const
	{
		if(a==x.a)
			return b<x.b;
		return a<x.a;
	}
	bool operator ==(const spell &x)const
	{
		if(a==x.a&&b==x.b)
			return true;
		else
			return false;
	}
};

int main()
{
	ios::sync_with_stdio(0);
	string s1,s2;
	int n;
	cin>>n>>s1>>s2;
	set <spell> s;
	rep(i,0,n)
	{
		if(s1[i]!=s2[i])
		{
			spell p1,p2;
			p1.a=s1[i];
			p1.b=s2[i];
			p2.a=s2[i];
			p2.b=s1[i];
			if(!s.count(p1)&&!s.count(p2))
				s.insert(p1);
		}
	}
	cout<<s.size()<<endl;
	auto i=s.begin();
	for(;i!=s.end();++i)
	{
		cout<<(*i).a<<" "<<(*i).b<<endl;
	}
	return 0;
}
