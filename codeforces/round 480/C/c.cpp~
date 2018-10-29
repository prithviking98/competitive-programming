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

bool comp(const vi &x,const vi &y)
{
	rep(i,0,x.size())
	{
		if(x[i]!=y[i])
			return x[i]<y[i];
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	vi p(n);
	rep(i,0,n)
		cin>>p[i];
	vi a(256,-1);
	rep(i,0,n)
	{
//		trace2(i,p[i]);
		if(a[p[i]]==-1)
		{
			int j;
			for( j=p[i];j>=0&&j>=p[i]-k+1&&(a[j]==-1||a[j]>=p[i]-k+1);j--);
			int low;
			if(j==p[i])
				low=j;
			else if(a[j+1]!=-1)
				low=a[j+1];
			else
				low=j+1;
//			trace2(j,low);
			for(j=p[i];j>=low;--j)
				a[j]=low;
			p[i]=a[p[i]];

		}
		else
		{
			p[i]=a[p[i]];
		}
	}

	rep(i,0,n)
		cout<<p[i]<<" ";
	cout<<endl;
	return 0;
}
