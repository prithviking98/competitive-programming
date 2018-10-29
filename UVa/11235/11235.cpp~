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

#define left(i) 2*i+1
#define right(i) 2*i+2

void build(vi &t,vi &a,int node,int start,int stop)
{
	if(start==stop)
		t[node]=a[start];
	else 
	{
		int mid=(start+stop)/2;
		build(t,a,left(node),start,mid);
		build(t,a,right(node),mid+1,stop);
		t[node]=max(t[left(node)],t[right(node)]);
	}
}

int query(vi &t,int node,int start,int stop,int l,int r)
{
	if(start>r||stop<l)
		return 0;
	else if(start>=l&&stop<=r)
		return t[node];
	else
	{
		int mid=(start+stop)/2;
		int p1=query(t,left(node),start,mid,l,r);
		int p2=query(t,right(node),mid+1,stop,l,r);
		return max(p1,p2);
	}
}


int main()
{
	ios::sync_with_stdio(0);
	int n,q;
	while(cin>>n>>q)
	{
		if(n==0)
			break;
		int size=pow(2,(int)log2(2*n-1)+1);
//		trace1(size);
		vi t(size);
		vi a(n),count(n),start(n),stop(n);
		rep(i,0,n)
			cin>>a[i];
		for(int i=0;i<n;)
		{
			int j;
			for(j=i;a[j]==a[i];j++);
			int c=j-i;
			rep(k,i,j)
			{
				count[k]=c;
				start[k]=i;
				stop[k]=j-1;
			}
			i=j;
		}
//		tracev(a);
//		tracev(count);
//		tracev(start);
//		tracev(stop);

		build(t,count,0,0,n-1);
		while(q--)
		{
			int l,r;
			cin>>l>>r;
//			trace2(l,r);
			l--;
			r--;
//			trace2(l,r);
			if(a[l]==a[r])
				cout<<r-l+1<<endl;
			else if(start[l]==l&&stop[r]==r)
				cout<<query(t,0,0,n-1,l,r)<<endl;
			else 
			{
				int cl=0,cr=0,fr=0,fl=0;
				if(start[l]<l)
				{
					fl=1;
					cl=count[l]+start[l]-l;
				}
				if(stop[r]>r)
				{
					fr=1;
					cr=r-start[r]+1;
				}
				int mc;
				if(fl&&fr)
					mc=query(t,0,0,n-1,stop[l]+1,start[r]-1);
				else if(fl&&!fr)
					mc=query(t,0,0,n-1,stop[l]+1,r);
				else if(!fl&&fr)
					mc=query(t,0,0,n-1,l,start[r]-1);
				int ans=max(max(cl,cr),mc);
				cout<<ans<<endl;
			}
		}
	}
	return 0;
}
