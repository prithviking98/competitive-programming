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
	int n,a,b;
	cin>>n>>a>>b;
	string temp;
	cin>>temp;
	vi s(n);
       	rep(i,0,n)
	{
		if(temp[i]=='*')
			s[i]=1;
	}
	int i,j,count=0;
	for(i=0;i<n;++i)
	{
		if(s[i]==1)
			continue;
		else
		{
			for(j=i;j<n&&s[j]==0;++j);
			--j;
			if(i==j)
				continue;
			int f;
			if(a>b)
				f=1;
			else
				f=0;
			for(;i<=j;++i)
			{
				if(f)
				{
					if(a>0)
					{
						--a;
						count++;
					}
					s[i]=2;
					f=0;
				}
				else
				{
					if(b>0)
					{
						--b;
						count++;
					}
					s[i]=3;
					f=1;
				}
			}
			--i;
		}
	}
	rep(i,0,n)
	{
		if(s[i]!=0)
			continue;
		if(a>0)
		{
			a--;
			count++;
		}
		else if(b>0)
		{
			b--;
			count++;
		}
	}
	cout<<count<<endl;


	return 0;
}
