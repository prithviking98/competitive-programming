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
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		queue <pii> q;
		int l,r;
		pii p;
		rep(i,0,n)
		{
			cin>>l>>r;
			p={l,r};
			q.push(p);
		}
		int time=0;
		while(!q.empty())
		{
			time++;
			if(q.front().first<=time&&q.front().second>=time)
			{
				cout<<time<<" ";
				q.pop();
			}
			else if(q.front().second<=time)
			{
				cout<<0<<" ";
				q.pop();
				time--;
			}
		}
		cout<<endl;
	}
			
	return 0;
}
