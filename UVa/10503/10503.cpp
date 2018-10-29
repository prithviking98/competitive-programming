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

pii beg,last;
vector<pii> dom,line;
bitset<16> in;
int n,m,flag;

void search()
{
	if(flag)
		return;
	if(line.size()==n+1)
	{
		if(line.back().second==last.first)
			flag=1;
		return;
	}
	rep(i,0,m)
	{
		if(in[i]||(dom[i].first!=line.back().second&&dom[i].second!=line.back().second))
			continue;
		in[i]=1;
		if(dom[i].first==line.back().second)
			line.PUB(dom[i]);
		else
			line.PUB({dom[i].second,dom[i].first});
		search();
		line.POB();
		in[i]=0;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	while(1)
	{
		cin>>n;
		if(n==0)
			break;
		cin>>m;
		cin>>beg.first>>beg.second;
		cin>>last.first>>last.second;
		dom.resize(m);
		rep(i,0,m)
			cin>>dom[i].first>>dom[i].second;
		line.clear();
		in.reset();
		line.PUB(beg);
		flag=0;
		search();
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
