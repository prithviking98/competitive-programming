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
	int n,cas=1;
	while(cin>>n)
	{
		if(n==0)
			break;
		cout<<"Case #"<<cas<<":"<<endl;
		cas++;
		vi y(n),a(n),b(n),l(n);
		int max=-1;
		rep(i,0,n)
		{
			cin>>y[i]>>a[i]>>b[i];
			if(a[i]>max)
				max=a[i];
			l[i]=b[i]-a[i];
		}
		vector<bitset<10000>> set(n);
		rep(i,0,n)
		{
			int k=y[i];
			while(k<10000)
			{
				if(k>=max)
				{
					set[i][k]=1;
				}
				k+=l[i];
			}
		}
		bitset<10000> c;
		c=set[0];
		rep(i,0,n)
			c&=set[i];
		int flag=1;
		rep(i,0,10000)
			if(c[i]==1&&i>=max)
			{
				cout<<"The actual year is ";
				cout<<i<<"."<<endl<<endl;
				flag=0;
				break;
			}
		if(flag)
			cout<<"Unknown bugs detected."<<endl<<endl;
	}

	return 0;
}
