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
	int n;
	cin>>n;
	vi s(n),c(n);
	rep(i,0,n)
		cin>>s[i];
	rep(i,0,n)
		cin>>c[i];
	vi ic(n,INT_MAX);
	rep(i,1,n)
	{
		int min=INT_MAX;
		for(int j=i-1;j>=0;--j)
		{
			if(s[j]<s[i])
			{
				if(c[j]<min)
					min=c[j];
			}
		}
		if(min<INT_MAX)
			ic[i]=min+c[i];
		else
			ic[i]=INT_MAX;
	}
	vi fc(n,INT_MAX);
	rep(i,2,n)
	{
		int min=INT_MAX;
		for(int j=i-1;j>=1;--j)
		{
			if(s[j]<s[i])
			{
				if(ic[j]<min)
					min=ic[j];
			}
		}
		if(min<INT_MAX)
			fc[i]=min+c[i];
	}
	int min=INT_MAX;
	rep(i,2,n)
		if(fc[i]<min)
			min=fc[i];
	if(min<INT_MAX)
		cout<<min<<endl;
	else
		cout<<-1<<endl;

	return 0;
}
