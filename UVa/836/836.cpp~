#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

#define TRACE
#ifdef TRACE
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracea(a,n) rep(II,0,n) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracevv(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define tracem(a,r,c)\
	{\
	rep(II,0,r){\
		rep(JJ,0,c)\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#else
#define trace1(x)   
#define trace2(x,y)   
#define trace3(x,y,z)   
#define trace4(w,x,y,z)  
#define tracev(a) 
#define tracea(a,n)  
#define tracevv(a)  
#define tracem(a,r,c)  
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	cin.ignore();
	cin.ignore();
	while(t--)
	{
		string s;
		vector<string> a;
		while(1)
		{
			getline(cin,s);
			if(s.size()==0)
				break;
			a.PUB(s);
		}
		vvi sum(a.size());
		rep(i,0,a.size())
			sum[i].resize(a[i].size());
		rep(i,0,a.size())
			rep(j,0,a[0].size())
			{
				sum[i][j]=a[i][j]-'0';
				if(i>0)
					sum[i][j]+=sum[i-1][j];
				if(j>0)
					sum[i][j]+=sum[i][j-1];
				if(i>0&&j>0)
					sum[i][j]-=sum[i-1][j-1];
			}
		int r=a.size(),c=a[0].size();
		int ans=0;
		rep(i,0,r)
			rep(j,0,c)
				rep(k,i,r)
					rep(l,j,c)
					{
						int s=sum[k][l];
						if(i>0)
							s-=sum[i-1][l];
						if(j>0)
							s-=sum[k][j-1];
						if(i>0&&j>0)
							s+=sum[i-1][j-1];
						int area=(k-i+1)*(l-j+1);
						if(s==area)
						{
							ans=max(ans,area);
						}
					}
		cout<<ans<<endl;
		if(t>0)
			cout<<endl;
	}
	return 0;
}
