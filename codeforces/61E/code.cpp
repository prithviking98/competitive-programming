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

void update(vector<ll> &BIT,int i,int val)
{
	for(;i<BIT.size();i+=(i&-i))
		BIT[i]+=val;
}

ll query(vector <ll> &BIT,int i)
{
	ll sum=0;
	for(;i>0;i-=(i&-i))
		sum+=BIT[i];
	return sum;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	vi temp(a);
	sort(temp.begin(),temp.end());
	unordered_map<int,int> m;
	rep(i,0,n)
		m[temp[i]]=i+1;
	rep(i,0,n)
		a[i]=m[a[i]];
	/*
	rep(i,0,n)
		trace2(i,a[i]);
	*/
	vector<ll> inv(n);
	vector<ll> BIT(n+1);
	for(int i=n-1;i>=0;--i)
	{
		inv[i]=query(BIT,a[i]-1);
		update(BIT,a[i],1);
	}
	rep(i,0,n+1)
		BIT[i]=0;
	ll count=0;
	for(int i=n-1;i>=0;--i)
	{
		count+=query(BIT,a[i]-1);
		update(BIT,a[i],inv[i]);
	}
	cout<<count<<endl;
	return 0;
}
