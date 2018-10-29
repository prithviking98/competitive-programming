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
	vi a(2*n);
	vi p(2*n);
	rep(i,0,2*n)
		cin>>a[i];
//	tracev(a);
	rep(i,0,2*n)
	{
		rep(j,0,2*n)
		{
			if(i!=j&&a[i]==a[j])
			{
				p[i]=j;
			}
		}
	}
//	tracev(p);
	int m=0;
	rep(i,0,2*n)
	{
		int temp=a[i];
		if(p[i]<i-1)
		{
			int j=i-1;
			while(a[j]!=temp)
			{
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
				j--;
				m++;
			}
		}
	}
	cout<<m<<endl;
	return 0;
}
