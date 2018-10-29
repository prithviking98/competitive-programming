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
	string t;
	cin>>t;
//	trace1(t);
	vector<char> s;
	vi c;
	for(int i=0;i<t.size();)
	{
		s.PUB(t[i]);
		int j=i;
		while(j<t.size()&&t[j]==t[i])
			j++;
//		trace2(i,j);
		c.PUB(j-i);
//		trace3(t[i],s.back(),c.back());
		i=j;
	}
	int total=0;
	while(s.size()>1)
	{
		int index=0;
		int turns=((index==0||index==s.size()-1)?c[index]:c[index]/2+(c[index]%2));
		rep(i,0,s.size())
			if(turns>((i==0||i==s.size()-1)?c[i]:c[i]/2+(c[i]%2)))
			{
				turns=((i==0||i==s.size()-1)?c[i]:c[i]/2+(c[i]%2));
			}
//		trace3(m,index,turns);
		total+=turns;
		c[0]-=turns;
		c[c.size()-1]-=turns;
		rep(i,1,s.size()-1)
			c[i]-=(2*turns);
		vector <char> ns;
		vector <int> nc;
		int j=0;
		rep(i,0,s.size())
		{
			if(c[i]>0)
			{
				if(ns.size()>0&&ns.back()==s[i])
					nc[nc.size()-1]+=c[i];
				else
				{
					ns.PUB(s[i]);
					nc.PUB(c[i]);
				}
			}
		}
		s=ns;
		c=nc;
	}
	cout<<total<<endl;

	return 0;
}
