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
	int k;
	int t=0;
	while(1)
	{
		cin>>k;
		if(k==0)
			break;
		vi a(k);
		rep(i,0,k)
			cin>>a[i];
		sort(a.begin(),a.end());
		t++;
		if(t>1)
			cout<<endl;
		rep(i,0,k-5)
			rep(j,i+1,k-4)
				rep(l,j+1,k-3)
					rep(m,l+1,k-2)
						rep(n,m+1,k-1)
							rep(o,n+1,k)
								cout<<a[i]<<" "<<a[j]<<" "<<a[l]<<" "<<a[m]<<" "<<a[n]<<" "<<a[o]<<endl;
	}
	return 0;
}
