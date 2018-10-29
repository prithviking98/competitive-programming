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
	int n;
	cin>>n;
	int l=n;
	int layers=0;
	for(int i=1;i<=l;++i)
	{
		int j=0;
		for(;j<i;++j)
		{
			if(l==i+j)
			{
				layers+=j+1;
				break;
			}
		}
		if(j==i)
			layers+=j;
	}
	cout<<layers<<endl;
	return 0;
}
