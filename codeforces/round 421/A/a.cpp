
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int c,v0,v1,a,l;
	int days,pos;
	pos=0;
	days=1;
	cin>>c>>v0>>v1>>a>>l;
	while(pos<c)
	{
		if(days==1)
		{
			pos=v0;
			days++;
		}
		else if(days!=1&&(v0+(days-1)*a<v1))
		{
			pos=pos-l+v0+(days-1)*a;
			++days;
		}
		else
		{
			pos=pos-l+v1;
			++days;
		}
	}
	cout<<days-1<<endl;
	return 0;
}