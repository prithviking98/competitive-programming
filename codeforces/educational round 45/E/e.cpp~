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

vi b(1e6+1),a(1e6+1),last(1e6+1);
int n,m,k;

ll check(int l)
{
	int cur=0,prev=-1,count=0;
	while(cur<n)
	{
		if(prev==last[cur])
			return LLONG_MAX;
		prev=last[cur];
		cur=last[cur]+l;
		count++;
	}
	return count;
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m>>k;
	int t;
	rep(i,0,m)
		b[i]=0;
	rep(i,0,m)
	{
		cin>>t;
		b[t]=1;
	}
	rep(i,1,n+1)
		cin>>a[i];
	rep(i,0,n)
	{
		if(b[i]&&i)
			last[i]=last[i-1];
		else if(b[i]&&i==0)
			last[i]=-1;
		else
			last[i]=i;
	}
	ll cost=LLONG_MAX;
	rep(i,1,k+1)
	{
		ll num=check(i);
		if(num<LLONG_MAX&&num*a[i]<cost)
			cost=num*a[i];
	}
	if(cost<LLONG_MAX)
		cout<<cost<<endl;
	else
		cout<<-1<<endl;
	return 0;
}
