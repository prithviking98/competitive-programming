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

unordered_set<int> prime={2,3,5,7,11,13,17,19,23,29,31};
vector<string> sol;
int n;
bitset<17> in;
vi p;

void search()
{
	if(p.size()==n)
	{
		if(prime.count(p[n-1]+1)==0)
			return;
		string a,b,c;
		rep(i,0,p.size())
		{
			int t=p[i];
			b="";
			c="a";
			while(t)
			{
				c[0]='0'+(t%10);
				t/=10;
				b=c+b;
			}
			if(i<p.size()-1)
				a=a+b+" ";
			else
				a=a+b;
		}
		sol.PUB(a);
		return;
	}
	rep(i,2,n+1)
	{
		if(in[i])
			continue;
		if(prime.count(i+p.back())==0)
			continue;
		in[i]=1;
		p.PUB(i);
		search();
		in[i]=0;
		p.POB();
	}
}


int main()
{
	ios::sync_with_stdio(0);
	int t=0;
	while(cin>>n)
	{
		t++;
		p.clear();
		in.reset();
		sol.clear();
		in[1]=1;
		p.PUB(1);
		search();
		if(t>1)
			cout<<endl;
		cout<<"Case "<<t<<":"<<endl;
//		trace1(sol.size());
		rep(i,0,sol.size())
			cout<<sol[i]<<endl;
	}
	return 0;
}
