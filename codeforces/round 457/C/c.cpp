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

struct edge
{
	int u,v,w;
};

bool isPrime(ll n)
{
	for(int i=2;i<=sqrt(n);++i)
		if(n%i==0)
			return false;
	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	ll mstw=2,sp;
	sp=2;
	vector <edge> e;
	edge t={1,n,2};
	e.PUB(t);
	rep(i,2,n-1)
	{
		t={1,i,1};
		e.PUB(t);
		mstw++;
	}
	int w=1;
	while(!isPrime(mstw+w))
		w++;
	t={1,n-1,w};
	e.PUB(t);
	mstw+=w;
	int count=n-1;
		for(int i=2;i<=n;++i)
		{
			for(int j=i+1;j<=n;++j)
			{
				t={i,j,w+5};
				e.PUB(t);
				count++;
				if(count==m)
					break;
			}
			if(count==m)
				break;
		}
	cout<<sp<<" "<<mstw<<endl;
	rep(i,0,m)
		cout<<e[i].u<<" "<<e[i].v<<" "<<e[i].w<<" "<<endl;


	
	
	return 0;
}
