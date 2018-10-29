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
	string s;
	cin>>t;
	while(t--)
	{

		cin>>s;
		int count=0;
		vi a(4,0);
		for(int i=0;i<s.size()-3;++i)
		{
			for(int j=0;j<4;++j)
				if(i+j<s.size())
				{
					if(s[i+j]=='c')
					{
						if(!a[0])
							a[0]=1;
					}
					else if(s[i+j]=='h')
					{
						if(!a[1])
							a[1]=1;
					}
					else if(s[i+j]=='e')
					{
						if(!a[2])
							a[2]=1;
					}
					else if(s[i+j]=='f')
					{
						if(!a[3])
							a[3]=1;
					}
					else
					{
						i=i+j;
						break;
					}

				}
			int sum=0;
			rep(j,0,4)
			{
				sum+=a[j];
				a[j]=0;
			}
			if(sum==4)
				++count;
		}
		if(count)
			cout<<"lovely "<<count<<endl;
		else
			cout<<"normal"<<endl;
	}
	return 0;
}
