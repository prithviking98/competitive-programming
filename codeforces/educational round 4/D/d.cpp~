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
	int n,k;
	cin>>n>>k;
	vector<pii> e;
	int l,r;
	rep(i,0,n)
	{
		cin>>l>>r;
		e.PUB({l,-1});
		e.PUB({r,1});
	}
	sort(e.begin(),e.end());
	vector <pii> min;
	int count=0;
	rep(i,0,2*n)
	{
		if(e[i].second==-1)
		{
			count++;
			if(count==k)
				l=e[i].first;
		}
		else
		{
			count--;
			if(count==k-1)
			{
				min.PUB({l,e[i].first});
			}
		}
	}
	cout<<min.size()<<endl;
	rep(i,0,min.size())
		cout<<min[i].first<<" "<<min[i].second<<endl;
	return 0;
}
