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
	int f,m,s,mas;
	cin>>f>>m>>s>>mas;
	if(mas>2*s||s>2*mas)
	{
		cout<<-1;
		return 0;
	}
	int sc=s;
	while(sc<mas)
		++sc;
	if(sc>=m)
	{
		cout<<-1;
		return 0;
	}
	cout<<2*f<<endl<<2*m<<endl;
	cout<<sc<<endl;
	return 0;
}
