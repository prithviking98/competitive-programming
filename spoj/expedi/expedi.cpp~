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
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vector <pii> a(n);
		rep(i,0,n)
			cin>>a[i].first>>a[i].second;
		int l,p;
		cin>>l>>p;
		rep(i,0,n)
			a[i].first=l-a[i].first;
		sort(a.begin(),a.end());
		int i=0,stops=0,r=p;
		priority_queue <int> pq;
		while(i<n&&r<l)
		{
			for(;i<n&&a[i].first<=r;++i)
			{
				pq.push(a[i].second);
			}
			if(pq.empty())
				break;
			stops++;
			r+=pq.top();
			pq.pop();
		}
		if(r<l)
			cout<<-1<<endl;
		else
			cout<<stops<<endl;
	}
	return 0;
}
