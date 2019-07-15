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

struct elephant
{
	int w,s,index;
	bool operator < (const elephant &x) const
	{
		if(s!=x.s)
			return s>x.s;
		else
			return w<x.w;
	}
};

int main()
{
	ios::sync_with_stdio(0);
	vector<elephant> a;
	int t1,t2,index=0;
	while(cin>>t1>>t2)
	{
		a.push_back({t1,t2,index});
		index++;
	}
	int n=a.size();
	sort(a.begin(),a.end());
	vi p(n,-1),l(n,1);
	int ml=1;
	l[0]=1;
	for(int i=1;i<n;++i)
	{
		for(int j=0;j<i;++j)
		{
			if(a[j].s>a[i].s&&a[j].w<a[i].w)
			{
				if(l[j]+1>l[i])
				{
					l[i]=l[j]+1;
					p[i]=j;
				}
			}
		}
		if(ml<l[i])
		{
			ml=l[i];
			index=i;
		}
	}
	cout<<ml<<endl;
	vi ans;
	while(index!=-1)
	{
		ans.push_back(a[index].index+1);
//		trace3(a[index].w,a[index].s,a[index].index);
		index=p[index];
	}
	for(int i=ans.size()-1;i>=0;--i)
		cout<<ans[i]<<endl;
	return 0;
}
