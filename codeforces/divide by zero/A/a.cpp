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
	string s;
	cin>>s;
	int flag=1;
	vi count(3);
	rep(i,0,s.size())
		if(s[i]=='a')
			count[0]++;
	if(count[0]==0)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	rep(i,count[0],s.size())
		if(s[i]=='b')
			count[1]++;
	if(count[1]==0)
	{
		cout<<"NO"<<endl;
		return 0;
	}
	rep(i,count[0]+count[1],s.size())
		if(s[i]=='c')
			count[2]++;
	if(count[0]+count[1]+count[2]<s.size())
	{
		cout<<"NO"<<endl;
		return 0;
	}

	if(count[2]==count[1]||count[2]==count[0])
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
