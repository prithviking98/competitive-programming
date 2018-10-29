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
		int n,m;
		cin>>n>>m;
		vi a(n*m);
		int s=n*m;
		rep(i,0,s)
			cin>>a[i];
		sort(a.rbegin(),a.rend());
		int cy=0,geno=0;
		rep(i,0,s)
		{
			if(i%2==0)
				cy+=a[i];
			else 
				geno+=a[i];
		}
		if(cy>geno)
			cout<<"Cyborg"<<endl;
		else if(geno>cy)
			cout<<"Geno"<<endl;
		else
			cout<<"Draw"<<endl;
	}
	return 0;
}
