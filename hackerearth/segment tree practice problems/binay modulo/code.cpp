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

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

void build(vector<int> &t,const string &a,int node,int start,int end)
{
	if(start==end)
	{
		t[node]=a[start]-'0';
	}
	else
	{
		int mid=(start+end)/2;
		build(t,a,2*node+1,start,mid);
		build(t,a,2*node+2,mid+1,end);
		int len=end-mid,pow;
		if(len%4==1)
			pow=2;
		else if(len%4==2)
			pow=4;
		else if(len%4==3)
			pow=3;
		else if(len%4==0)
			pow=1;
		t[node]=((pow*t[2*node+1])%5+t[2*node+2])%5;
	}
}

int query(vi &t,int node,int start,int end,int l,int r)
{
	if(start>r||end<l)
		return 0;
	else if(start>=l&&end<=r)
		return t[node];
	else
	{
		int mid=(start+end)/2;
		int ql=query(t,2*node+1,start,mid,l,r);
		int qr=query(t,2*node+2,mid+1,end,l,r);
		int len,pow;
		if(r>end)
			len=end-mid;
		else
			len=r-mid;
		if(len%4==1)
			pow=2;
		else if(len%4==2)
			pow=4;
		else if(len%4==3)
			pow=3;
		else if(len%4==0)
			pow=1;
		if(len<=0)
			pow=1;
		return ((pow*ql)%5+qr)%5;
	}
}

void update(vi &t,string a,int node,int start,int end,int index,int val)
{
	if(start==end)
	{
		if(val)
			a[index]='1';
		else
			a[index]='0';
		t[node]=a[index]-'0';
	}
	else
	{
		int mid=(start+end)/2;
		if(index<=mid)
			update(t,a,node*2+1,start,mid,index,val);
		else
			update(t,a,node*2+2,mid+1,end,index,val);
		int len=end-mid,pow;
		if(len%4==1)
			pow=2;
		else if(len%4==2)
			pow=4;
		else if(len%4==3)
			pow=3;
		else if(len%4==0)
			pow=1;
		t[node]=((pow*t[2*node+1])%5+t[2*node+2])%5;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int t1=clock();
	int t=0;
	cin>>t;
	while(t--)
	{
		string a;
		cin>>a;
		int n=a.size();
		vector<int> t(pow(2,floor(log2(n))+2)-1);
		build(t,a,0,0,a.size()-1);
		/*
		rep(i,0,t.size())
			trace2(i,t[i]);
		*/
		int q;
		cin>>q;
		
		while(q--)
		{
			int c,l,r;
			cin>>c>>l>>r;
		//	trace3(c,l,r);
			if(c==0)
				cout<<query(t,0,0,n-1,l,r)<<"\n";
			else 
				update(t,a,0,0,n-1,l,r);
		}
		
	}
	int t2=clock();
	double time=(t2-t1)/(double)CLOCKS_PER_SEC;
	cout<<"time = "<<time<<endl;
	return 0;
}
