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
	int n,m;
	cin>>n>>m;
	vi a(n),b(m);
	rep(i,0,n)
		cin>>a[i];
	rep(i,0,m)
		cin>>b[i];
	sort(a.begin(),a.end());
	rep(j,0,m)
	{
		int f=0;
		for(int k=a.size()-1;k>=1;k/=2)
			while(f+k<a.size()&&a[f+k]<=b[j])
				f+=k;
		if(f==0&&a[0]>b[j])
			cout<<0<<" ";
		else
			cout<<f+1<<" ";
	}


	return 0;
}
