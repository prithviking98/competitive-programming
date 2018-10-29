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

ll c=0;
vi f(10),perm(10);

ll fact(ll n)
{
	ll f=1;
	rep(i,1,n+1)
		f*=i;
	return f;
}

void search(int i)
{
	if(i==10)
	{
		if(perm[0]==0)
		{
			ll sum=0;
			ll non=0;
			rep(j,0,10)
				if(perm[j]>0)
					non+=perm[j];
			if(non==0)
				return;
			sum=fact(non);
			rep(j,0,10)
				sum/=fact(perm[j]);
//			tracev(perm);
//			trace1(sum);
			c+=sum;
			return;
		}
		else
		{
			ll sum=0,non=0,sub=0;
			rep(j,0,10)
				if(perm[j]>0)
					non+=perm[j];
			if(non==0||non==perm[0])
				return;
			sum=fact(non);
			rep(j,0,10)
				sum/=fact(perm[j]);
			sub=fact(non-1);
			sub/=fact(perm[0]-1);
			rep(j,1,10)
				sub/=fact(perm[j]);
//			tracev(perm);
//			trace2(sum,sub);
			c+=(sum-sub);
			return;
		}
	}
	if(f[i]==0)
		search(i+1);
	for(int j=1;j<=f[i];++j)
	{
		perm[i]=j;
		search(i+1);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	string s;
	cin>>s;
	rep(i,0,s.size())
		f[s[i]-'0']++;
	search(0);
	cout<<c<<endl;
	return 0;
}
