
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
	cout<<10<<endl;
	rep(i,0,10)
	{
		cout<<17576;
		char s[3];
		rep(j,0,3)
			s[j]='a';
		rep(x,0,26)
		{
			s[0]+=x;
			rep(y,0,26)
			{
				s[1]+=y;
				rep(z,0,26)
				{
					s[2]+=z;
					cout<<s<<" ";
				}
			}
		}
		rep(x,0,26)
		{
			s[0]+=x;
			rep(y,0,26)
			{
				s[1]+=y;
				rep(z,0,26)
				{
					s[2]+=z;
					cout<<s<<" ";
				}
			}
		}
		cout<<endl;
	}

	return 0;
}