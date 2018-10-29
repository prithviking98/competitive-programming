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
	vi total(n+1);
	total[1]=1;
	vi above(n+1),d(n+1);
	rep(i,1,n+1)
	{
		int m;
		cin>>m;
		above[i]=m;
		if(above[i]>=total[i-1])
		{
			for(int j=i-1,k=above[i];j>0&&k>0;--j,k--)
			{
				if(k>total[j])
					total[j]=k;
				else
					break;
				d[j]=total[j]-above[j]-1;
//				trace3(j,total[j],d[j]);
			}
			total[i]=m+1;
		}
		else
			total[i]=total[i-1];
		d[i]=(total[i]-m-1);
	}
	ll sum=0;
	rep(i,1,n+1)
		sum+=d[i];
	cout<<sum<<endl;
	return 0;
}
