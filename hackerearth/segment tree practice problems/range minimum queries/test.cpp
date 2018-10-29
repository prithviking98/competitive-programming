
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

void foo(vi &a)
{
	a[3]=10;
}

int main()
{
	ios::sync_with_stdio(0);
	vi a(5);
	a={1,2,3,4,5};
	rep(i,0,5)
		trace1(a[i]);
	a[8]=5;
	cout<<a[8];
	a.at(10)=4;
	foo(a);
	rep(i,0,5)
		trace1(a[i]);
	return 0;
}
