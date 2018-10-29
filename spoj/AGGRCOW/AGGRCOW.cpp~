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

int n,c,Count;
vi a(1e5+1),p(1e5+1);

void assign(int l,int r)
{
	if(l==r-1 || Count==c)
		return;
	int mid=a[l]+a[r];
	mid/=2;
	int index=lower_bound(a.begin()+l,a.begin()+r+1,mid)-a.begin();
	Count++;
	if(a[index]==mid)
	{
		p[index]=1;
		assign(l,index);
		assign(index,r);
		return;
	}
	else 
	{
		int x,y;
		x=a[index-1]-a[l];
		y=a[r]-a[index];
		if(x>=y)
		{
			p[index-1]=1;
			assign(l,index-1);
			assign(index-1,r);
		}
		else
		{
			p[index]=1;
			assign(l,index);
			assign(index,r);
		}
		return ;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>c;
		rep(i,0,n)
			cin>>a[i];
		sort(a.begin(),a.begin()+n);
		tracea(a,n);
		Count=2;
		rep(i,0,n)
			p[i]=0;
		p[0]=p[n-1]=1;
		assign(0,n-1);
		tracea(p,n);
		int ans=INT_MAX;
		int prev=0,cur;
		for(int i=1;i<n;++i)
		{
			if(p[i]!=1)
				continue;
			cur=i;
			int t=a[cur]-a[prev];
			ans=min(t,ans);
			prev=cur;
		}
		cout<<ans<<endl;
	}
	return 0;
}
