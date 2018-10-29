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
	int k;
	cin>>k;
	if(k>36)
		cout<<-1<<endl;
	else
	{
		vi n(18);
		int count=0,i;
		for(i=0;i<18&&count<=k;++i)
		{
			n[i]=8;
			count+=2;
		}
		if(count==k+1)
			n[i-1]=4;
		else
			n[i-1]=1;
		rep(j,i,18)
			n[j]=1;
		rep(j,0,18)
			cout<<n[j];
		cout<<endl;
	}

	return 0;
}
