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
	int t=0;
	while(1)
	{
		t++;
		int n,m;
		cin>>n>>m;
		if(n==0)
			break;
		vi b(n),s(m);
		rep(i,0,n)
			cin>>b[i];
		rep(i,0,m)
			cin>>s[i];
		vi f(61);
		rep(i,0,m)
			f[s[i]]++;
		vi ma(n,1);
		sort(b.rbegin(),b.rend());
		rep(i,0,n)
		{
			int j=b[i];
			int k=b[i];
			while(j>1&&f[j]==0)
				j--;
			while(k<61&&f[k]==0)
				k++;
			if(k==61&&j>1)
				f[j]--;
			else if(k<61&&j==1)
				f[k]--;
			else if(k==61&&j==1)
				ma[i]=0;
			else if(k-b[i]<b[i]-j)
				f[k]--;
			else
				f[j]--;
		}
		int Min=1e6,count=0;
		rep(i,0,n)
			if(ma[i]==0)
			{
				count++;
				Min=min(Min,b[i]);
			}
		cout<<"Case "<<t<<": ";
		if(count==0)
			cout<<count<<endl;
		else
			cout<<count<< " "<<Min<<endl;
	}


	return 0;
}
