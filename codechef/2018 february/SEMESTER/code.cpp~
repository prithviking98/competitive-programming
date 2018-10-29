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
	vector<string> week(7);
	week[0]="monday";
	week[1]="tuesday";
	week[2]="wednesday";
	week[3]="thursday";
	week[4]="friday";
	week[5]="saturday";
	week[6]="sunday";
	while(t--)
	{
		int k;
		cin>>k;
		//cout<<k<<endl;
		vi a(7);
		rep(i,0,7)
			cin>>a[i];
		int c=0,i=-1;
		do
		{
			i++;
			i%=7;
			c+=a[i];
			//trace2(i,c);
		}while(c<k);
		cout<<week[i]<<endl;

	}
	return 0;
}
