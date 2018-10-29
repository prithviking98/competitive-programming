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
	int n,m;
	cin>>n>>m;
	vector<bool> isp(n+1,true);
	vi index(n+1);
	vi primes;
	isp[0]=isp[1]=false;
	primes.PUB(2);
	for(int i=4;i<=n;i+=2)
		isp[i]=false;
	for(ll i=3;i<=n;i+=2)
	{
		if(isp[i])
		{
			primes.PUB(i);
			index[i]=primes.size()-1;
			for(ll j=i;j*i<=n;j+=2)
				isp[j*i]=false;
		}
	}
//	tracev(primes);
	vector<int> ex(primes.size(),false);
	vector<bool> on(n+1,false);
	char c;
	int t;
	while(m--)
	{
		cin>>c>>t;
//		trace2(c,t);
		if(c=='+')
		{
			if(on[t])
			{
				cout<<"Already on"<<endl;
				continue;
			}
			int flag=0;
			if(isp[t]&&ex[index[t]])
			{
				cout<<"Conflict with "<<ex[index[t]]<<endl;
				flag=1;
				continue;
			}
			for(int i=0;i<primes.size()&&primes[i]*primes[i]<=t;++i)
			{
				if(t%primes[i]==0)
				{
//					trace1(primes[i]);
					if(ex[i])
					{
						cout<<"Conflict with "<<ex[i]<<endl;
						flag=1;
						break;
					}
					else if(t/primes[i]<=n&&isp[t/primes[i]]&&ex[index[t/primes[i]]])
					{
						cout<<"Conflict with "<<ex[index[t/primes[i]]]<<endl;
						flag=1;
						break;
					}
				}
			}
			if(flag==0)
			{
				cout<<"Success"<<endl;
				on[t]=true;
				if(isp[t])
					ex[index[t]]=t;
				for(int i=0;i<primes.size()&&primes[i]*primes[i]<=t;++i)
					if(t%primes[i]==0)
					{
						ex[i]=t;
						if(t/primes[i]<=n&&isp[t/primes[i]])
							ex[index[t/primes[i]]]=t;
					}
			}
//			tracev(ex);
		}
		else
		{
			if(!on[t])
			{
				cout<<"Already off"<<endl;
				continue;
			}
			cout<<"Success"<<endl;
			on[t]=false;
			if(isp[t])
				ex[index[t]]=0;
			for(int i=0;i<primes.size()&&primes[i]*primes[i]<=t;++i)
				if(t%primes[i]==0)
				{
					ex[i]=0;
					if(t/primes[i]<=n&&isp[t/primes[i]])
						ex[index[t/primes[i]]]=0;
				}
		}
	}

	return 0;
}

