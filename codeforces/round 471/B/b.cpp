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
	vi a(26);
	int count=0;
	rep(i,0,s.size())
	{
		if(a[s[i]-'a']==0)
			count++;
		++a[s[i]-'a'];
	}
	if(count>4||count==1)
		cout<<"No"<<endl;
	else if(count==4)
		cout<<"Yes"<<endl;
	else if(count==2)
	{
		int tc=0;
		rep(i,0,26)
			if(a[i]>=2)
				tc++;
		if(tc==2)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	else if(count==3)
	{
		int tc=0;
		rep(i,0,26)
			if(a[i]>=2)
				tc++;
		if(tc>=1)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}


	return 0;
}
