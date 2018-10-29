#include <bits/stdc++.h>

using namespace std;
//#define TRACE
#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#ifdef TRACE
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
#else
#define trace1(x) 
#define trace2(x,y) 
#define trace3(x,y,z) 
#define trace4(w,x,y,z)
#define tracev(a) 
#define tracem(a)
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
	rep(_i,0,t)
	{
		int s;
		cin>>s;
		vi a(s-1);
		rep(i,0,s-1)
			cin>>a[i];
		tracev(a);
		int sum=a[0],ans=a[0],l=1,r=2,al=1,ar=2;
		rep(i,1,s-1)
		{
			if(a[i]>sum+a[i])
			{
				sum=a[i];
				l=i+1;r=i+2;
			}
			else
			{
				sum=a[i]+sum;
				r++;
			}
			if(ans<sum)
			{
				ans=sum;
				al=l;
				ar=r;
				trace3(al,ar,ans);
			}
			else if (sum==ans)
			{
				trace2(sum,ans);
				if(ar-al<r-l)
				{
					trace4(al,ar,l,r);
					al=l;
					ar=r;
				}
			}

		}
		if(ans>0)
			cout<<"The nicest part of route "<<_i+1<<" is between stops "<<al<<" and "<<ar<<endl;
		else
			cout<<"Route "<<_i+1<<" has no nice parts"<<endl;
	}
	return 0;
}
