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
	vi a(n);
	int sum=0;
	rep(i,0,n)
	{
		cin>>a[i];
		sum+=a[i];
	}
	int count=0,k=ceil(sum/2),day;
	rep(i,0,n)
	{
		count+=a[i];
		if(count>=k)
		{
			day=i+1;
			break;
		}
	}
	cout<<day<<endl;
	return 0;
}
