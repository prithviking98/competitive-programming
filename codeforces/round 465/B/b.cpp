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
	string s;
	cin>>n>>s;
	int x=0,y=0,k=0,count=0;
	rep(i,0,n)
	{
		if(x<y)
			k=-1;
		else if(x>y)
			k=1;
		if(s[i]=='U'||s[i]=='u')
			y++;
		else
			x++;
		if(k==-1&&(x>y))
			count++;
		else if(k==1&&(x<y))
			count++;
	}
	cout<<count<<endl;
		
	return 0;
}
