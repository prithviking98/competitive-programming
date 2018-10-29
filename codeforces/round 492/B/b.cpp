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
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
/==/	trace1(n);
	vi a(n+1);
	rep(i,1,n+1)
		cin>>a[i];
	vi t(n+1);
	t[0]=INT_MAX;
	rep(i,1,n+1)
	{
		int q=a[i];
		int c=0;
		for(int b=q/n;b>=1;b/=2)
			while((c+b)*n<=q)
				c+=b;
		if(c*n<q&&i<=(q-c*n))
			c++;
		t[i]=c*n+i;
//		trace3(c,t[i],i);
	}
	int m=INT_MAX,index=0;
	rep(i,1,n+1)
		if(m>t[i])
		{
			m=t[i];
			index=i;
		}
	cout<<index<<endl;
	return 0;
}
