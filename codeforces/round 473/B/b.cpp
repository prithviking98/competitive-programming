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

int main()
{
	ios::sync_with_stdio(0);
	int n,k,m;
	cin>>n>>k>>m;
	vector <string> s(n);
	unordered_map <string,int> si;
	rep(i,0,n)
	{
		cin>>s[i];
		si[s[i]]=i;
	}
	vector<int> a(n);
	rep(i,0,n)
		cin>>a[i];
	rep(i,0,k)
	{
		int g;
		cin>>g;
		vector<int> sg;
		sg.resize(g);
		int min=INT_MAX;
		rep(i,0,g)
		{
			cin>>sg[i];
			if(a[sg[i]-1]<min)
				min=a[sg[i]-1];
		}
		rep(i,0,g)
		{
			a[sg[i]-1]=min;
		}
	}
	string t;
	ll cost=0;
	rep(i,0,m)
	{
		cin>>t;
		cost=cost+(ll)a[si[t]];
	}
	cout<<cost<<endl;



			
	return 0;
}