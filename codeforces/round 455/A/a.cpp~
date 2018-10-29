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
	string first,last;
	cin>>first>>last;
	string pf=first.substr(0,1);
	string pl=last.substr(0,1);
	string l,s;
	l=pf+pl;
	rep(i,1,first.size()+1)
	{
		pf=first.substr(0,i);
		s=pf+pl;
		if(s<l)
			l=s;
	}
	cout<<l;
	return 0;
}
