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

vi a(100);

int cut(int l,int r,int b)
{
//	trace3(l,r,b);
	if(l==r-1)
		return 0;
	vi e(r-l+1),o(r-l+1);
	int n=r-l+1;
	int k=0;
	rep(i,l,r+1)
	{
		if(a[i]%2==1)
		{
			if(k==0)
			{
				o[k]=1;
				e[k]=0;
				k++;
			}
			else
			{
				o[k]=o[k-1]+1;
				e[k]=e[k-1];
				k++;
			}
		}
		else
		{
			if(k==0)
			{
				o[k]=0;
				e[k]=1;
				k++;
			}
			else
			{
				o[k]=o[k-1];
				e[k]=e[k-1]+1;
				k++;
			}
		}
	}
//	tracev(e);
//	tracev(o);
	int m=200,index=0;
	rep(i,0,n-1)
	{
		if(e[i]==o[i])
		{
			int cost=abs(a[l+i]-a[l+i+1]);
			if(cost<m)
			{
				m=cost;
				index=l+i;
			}
		}
	}
	if(m>b)
		return 0;
	else
		return 1+max(cut(l,index,b-m),cut(index+1,r,b-m));
}

int main()
{
	ios::sync_with_stdio(0);
	int n,b;
	cin>>n>>b;
	rep(i,0,n)
		cin>>a[i];
	cout<<cut(0,n-1,b)<<endl;

	return 0;
}
