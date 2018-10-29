#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct sausage
{
	int x,y,r;
};

int oncrust(sausage s,int r,int d)
{
	if(2*s.r>d)
		return 0;
	else
	{
		float dist=sqrt(s.x*s.x+s.y*s.y);
		//cout<<dist<<endl;
		if((dist>=s.r+r-d)&&(dist<=r-s.r))
			return 1;
		else
			return 0;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int r,d;
	int n;
	int count=0;
	cin>>r>>d>>n;
	vector <sausage> s(n);
	for(int i=0;i<n;++i)
		cin>>s[i].x>>s[i].y>>s[i].r;
	rep(i,0,n)
		if(oncrust(s[i],r,d))
				++count;
	cout<<count<<endl;
	return 0;
}
