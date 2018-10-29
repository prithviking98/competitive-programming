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
	int hour,minute;
	cin>>hour>>minute;
	//trace2(hour,minute);
	int h,d,c,n;
	cin>>h>>d>>c>>n;
	//trace4(h,d,c,n);
	float cost1,cost2;
	cost1=ceil((float)h/n)*c;
	if(hour>=20)
	{
		cost2=cost1=0.8*cost1;
	}
	else
	{
		int time;
		time=(20-hour-1)*60+60-minute;
		//trace1(time);
		h+=d*time;
		//trace1(h);
		cost2=0.8*ceil((float)h/n)*c;
	}
	cout<<min(cost1,cost2)<<endl;
	return 0;
}
