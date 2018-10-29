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

vi prime,fx,fy;
int x,y,l,r,c=0;

ll prod(vi &f)
{
	ll a=1;
	rep(i,0,f.size())
	{
		if(f[i])
			a=a*(ll)pow(prime[i],f[i]);
	}
	return a;
}

void search(int index)
{
	if(index==prime.size())
	{
		ll a,b;
		a=prod(fx);
		b=prod(fy);
		if(a>=l&&a<=r&&b>=l&&b<=r)
		{
//			trace2(a,b);
			c++;
		}
		return;
	}
	search(index+1);
	if(fx[index]==fy[index])
		return;
	int t=fx[index];
	fx[index]=fy[index];
	fy[index]=t;
	search(index+1);
	fy[index]=fx[index];
	fx[index]=t;
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>l>>r>>x>>y;
	prime.PUB(2);
	rep(i,2,1e9)
	{
		int flag=0;
		for(int j=0;prime[j]<=(int)sqrt(i);++j)
		{
			if(i%prime[j]==0)
			{
				flag=1;
				break;
			}
		}
		if(!flag)
			prime.PUB(i);
	}
	fx.resize(prime.size());
	fy.resize(prime.size());
	int tx=x,ty=y;
	rep(i,0,prime.size())
	{
		while(tx%prime[i]==0)
		{
			tx/=prime[i];
			fx[i]++;
		}
		
	}
	rep(i,0,prime.size())
	{
		while(ty%prime[i]==0)
		{
			ty/=prime[i];
			fy[i]++;
		}
	}
	rep(i,0,fx.size())
	{
		if(fx[i]>fy[i])
		{
			cout<<0<<endl;
			return 0;
		}
	}
	search(0);
	cout<<c<<endl;
	return 0;
}
