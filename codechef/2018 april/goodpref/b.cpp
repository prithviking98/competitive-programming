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
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		int n;
		cin>>s>>n;
		vi marg(s.size());
		int a=0,b=0;
		ll count=0;
		rep(i,0,s.size())
		{
			if(s[i]=='a')
				a++;
			else
				b++;
			if(a>b)
				count++;
			marg[i]=a-b;
		}
		int surp=a-b;
		if(surp==0)
			count+=count*(n-1);
		else
		for(ll k=1;k<n;++k)
		{
			rep(i,0,s.size())
			{
				marg[i]+=surp;
				if(marg[i]>0)
					count++;
			}
			int f=0,j;
			for(j=0;j<s.size();++j)
			{
				if(marg[j]>0)
				{
					if(f==-1)
						break;
					else
						f=1;
				}
				else if(marg[j]<0)
				{
					if(f==1)
						break;
					else
						f=-1;
				}
			}
			if(j==s.size())
			{
				if(surp>0)
				{
					count+=s.size()*(n-k-1);
				}
				break;
			}
		}
		cout<<count<<endl;
	}
	return 0;
}
