
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

void printchar(int i,int j)
{
	cout<<(char)(10*i+j);
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		vi d(10);
		rep(i,0,s.size())
		{
			int n=s[i]-48;
			if(d[n]==0)
				d[n]=1;
			else if(d[n]==1)
				d[n]=2;
		}
		if(d[6])
		{
			for(int i=5;i<=9;++i)
			{
				if(d[6]==1&&i==6)
					continue;
				if(d[i])
					printchar(6,i);
			}
		}
		if(d[7])
		{
			rep(i,0,10)
			{
				if(d[7]==1&&i==7)
					continue;
				if(d[i])
					printchar(7,i);
			}
		}
		if(d[8])
		{
			rep(i,0,10)
			{
				if(d[8]==1&&i==8)
					continue;
				if(d[i])
					printchar(8,i);
			}
		}
		if(d[9]&&d[0])
			printchar(9,0);
		cout<<endl;
	}
	return 0;
}
