#include <bits/stdc++.h>
#include <iostream>

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

bool hasSeven(int h,int m)
{
	if((h<10&&h%10==7)||(h>=10&&(h-10)%10==7)||(m<10&&m%10==7)||(m>=10&&(m-10)%10==7))
		return true;
	else
		return false;
}

void decrease(int x, int &h, int &m)
{
	if(x<=m)
		m-=x;
	else
	{
		if(h!=0)
			--h;
		else
			h=23;
		m=60-(x-m);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int x,h,m;
	cin>>x>>h>>m;
	int count=0;
	while(!hasSeven(h,m))
	{
		decrease(x,h,m);
		count++;
	}
	cout<<count<<endl;
	return 0;
}
