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
	vector <string> color(6),name(6);
	color[0]="purple"; name[0]="Power";
	color[1]="green"; name[1]="Time";
	color[2]="blue"; name[2]="Space";
	color[3]="orange"; name[3]="Soul";
	color[4]="red"; name[4]="Reality";
	color[5]="yellow"; name[5]="Mind";
	int n;
	cin>>n;
	vector<string> seen(n);
	rep(i,0,n)
		cin>>seen[i];
	vi a(6);
	rep(i,0,n)
		rep(j,0,6)
			if(seen[i]==color[j])
				a[j]=1;
	cout<<6-n<<endl;
	rep(i,0,6)
		if(a[i]==0)
			cout<<name[i]<<endl;
	return 0;
}
