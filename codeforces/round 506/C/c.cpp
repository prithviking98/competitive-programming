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
	int n;
	cin>>n;
	vector<pii> a(n);
	vector<int> left,right;
	rep(i,0,n)
	{
		int l,r;
		cin>>l>>r;
		a[i].first=l;
		a[i].second=r;
		left.PUB(l);
		right.PUB(r);
	}
	sort(left.begin(),left.end());
	sort(right.begin(),right.end());
	sort(a.begin(),a.end());
	if(n==2)
	{
		cout<<max(a[0].second-a[0].first,a[1].second-a[1].first)<<endl;
		return 0;
	}
	int cl=a[0].first,cr=a[0].second,index=-1,count=0;
	rep(i,1,n)
	{
		if(a[i].first>cr)
		{
			if(i>1&&i<n-1)
			{
				cout<<0<<endl;
				return 0;
			}
			if(i==1)
			{
				cl=a[i].first;
				cr=a[i].second;
				index=0;
			}
			if(i==n-1)
			{
				if(index==0)
				{
					cout<<0<<endl;
					return 0;
				}
				index=n-1;
			}
		}
		else
		{
			cl=a[i].first;
			cr=min(cr,a[i].second);
		}
	}
	int maxl=0;
	rep(i,0,n)
	{
		if(i==index)
			maxl=max(maxl,cr-cl);
		else if(index==-1)
		{
			int newl=cl,newr=cr;
			if(a[i].first<cl&&a[i].second>cr)
				continue;
			if(a[i].first==cl)
			{
				int t=lower_bound(left.begin(),left.end(),a[i].first)-left.begin();
				if(t<n-1&&a[t+1]!=a[t])
					newl=left[t-1];
				else if(t==n-1)
					newl=left[t-1];
			}
			if(a[i].second==cr)
			{
				int t=lower_bound(right.begin(),right.end(),a[i].second)-right.begin();
				if(t<n-1&&right[t+1]!=right[t])
					newr=right[t+1];
			}
			maxl=max(maxl,newr-newl);
		}
	}
	cout<<maxl<<endl;
	return 0;
}
