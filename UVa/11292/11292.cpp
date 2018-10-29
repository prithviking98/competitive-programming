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
	while(1)
	{
		int n,m;
		cin>>n>>m;
		if(n==0)
			break;
		vi d(n),h(m);
		rep(i,0,n)
			cin>>d[i];
		rep(i,0,m)
			cin>>h[i];
		sort(h.begin(),h.end());
		sort(d.begin(),d.end());
		auto i=h.begin();
		int k=0,sum=0;
		while(k<n)
		{
			i=lower_bound(i,h.end(),d[k]);
//			trace2(d[k],*i);
			if(i==h.end())
				break;
			sum+=*i;
			i++;
			k++;
		}
		if(k==n)
			cout<<sum<<endl;
		else
			cout<<"Loowater is doomed!"<<endl;

	}
	return 0;
}
