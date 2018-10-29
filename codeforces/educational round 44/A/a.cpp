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
	int n;
	cin>>n;
	vi ip(n/2);
	rep(i,0,n/2)
		cin>>ip[i];
	sort(ip.begin(),ip.end());
	vi bp(n/2),wp(n/2);
	rep(i,0,n/2)
	{
		bp[i]=2*i+1;
		wp[i]=2*i+2;
		//trace2(bp[i],wp[i]);
	}
	int wm=0,bm=0;
	rep(i,0,n/2)
	{
		bm+=abs(bp[i]-ip[i]);
		wm+=abs(wp[i]-ip[i]);
	}
	if(wm<bm)
		cout<<wm<<endl;
	else
		cout<<bm<<endl;


	return 0;
}
