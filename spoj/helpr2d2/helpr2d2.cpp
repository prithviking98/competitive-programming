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
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int k,n;
		cin>>k;
		cin>>n;
		int count=0,r,V;
		char c;
		string line;
		cin.ignore();
		vi v;
		while(count<n)
		{
			getline(cin,line,'\n');
//			trace1(line);
			if(line[0]=='b')
			{
				sscanf(line.c_str(),"%c %d %d",&c,&r,&V);
				count+=r;
				rep(i,0,r)
					v.PUB(V);
			}
			else
			{
				sscanf(line.c_str(),"%d",&V);
				v.PUB(V);
				count++;
			}
		}
//		tracev(v);
		multiset<pii> s;
		rep(i,0,1e5+5)
			s.insert({i,k});
		rep(i,0,n)
		{
//			trace1(i);
			auto j=s.lower_bound({-1,v[i]});
			int index,vol;
			index=(*j).first;
			vol=(*j).second-v[i];
			s.erase(j);
			s.insert({index,vol});
		}
		int w=0;
		count=0;
		for(auto i=s.begin();i!=s.end();++i)
			if((*i).first<k)
			{
				count++;
				w+=(*i).first;
			}
		cout<<count<<" "<<w<<endl;
	}
	return 0;
}
