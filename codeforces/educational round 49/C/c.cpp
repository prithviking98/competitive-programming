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
	while(t--)
	{
		int n;
		cin>>n;
		vi a(n),b,c;
		rep(i,0,n)
			cin>>a[i];
		sort(a.begin(),a.end());
		int i=0;
		while(i<n)
		{
			
			b.PUB(a[i]);
			int j=i+1;
			while(j<n&&a[j]==a[i])
				j++;
			c.PUB(j-i);
			c[c.size()-1]-=(c.back()%2);
			i=j;
		}
		long double mrat=5e6,rat;
		int l,br;
		int j;
		i=0;
		while(i<c.size())
		{
			if(c[i]>=4)
			{
				l=br=b[i];
				break;
			}
			else if(c[i]==2)
			{
				j=i+1;
				while(j<c.size()&&c[j]==0)
					j++;
				if(j>=c.size())
					break;
				rat=4*((long double)b[i]/b[j]+(long double)b[j]/b[i]+2);
				if(rat<mrat)
				{
					l=b[i];
					br=b[j];
					mrat=rat;
				}
				i=j;
			}
			else
				i++;
		}
		cout<<l<<" "<<l<<" "<<br<<" "<<br<<endl;
	}
	return 0;
}
