#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

int main()
{
	ios::sync_with_stdio(0);
	int a,b,c;
	cin>>a>>b>>c;
	if(a==1||b==1||c==1)
		cout<<"yes"<<endl;
	else if((a==2&&b==2)||(a==2&&c==2)||(b==2&&c==2))
		cout<<"yes"<<endl;
	else if(a==3&&b==3&&c==3)
		cout<<"yes"<<endl;
	else if((a==4&&b==4&&c==2)||(a==4&&c==4&&b==2)||(b==4&&c==4&&a==2))
		cout<<"yes"<<endl;
	else
		cout<<"no"<<endl;

	return 0;
}
