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

vi a,score,Prev,Next;
vector <pii> t;
void build(int node,int start,int stop)
{
	if(start==stop)
	{
		t[node]={score[start],start};
//		trace3(node,t[node].first,t[node].second);
		return;
	}
	int mid=(start+stop)/2;
	build(left(node),start,mid);
	build(right(node),mid+1,stop);
	if(t[left(node)].first>t[right(node)].first)
		t[node]=t[left(node)];
	else if(t[left(node)].first==t[right(node)].first)
		t[node]=a[t[left(node)].second]<a[t[right(node)].second]?t[left(node)]:t[right(node)];
	else
		t[node]=t[right(node)];
//	trace3(node,t[node].first,t[node].second);
}

void update(int node,int start,int stop,int index,int val)
{
	if(start>index||stop<index)
		return;
	else if(start==stop)
	{
		t[node].first=val;
//		trace3(start,index,val);
//		trace3(node,t[node].first,t[node].second);
		return;
	}
	int mid=(start+stop)/2;
	if(index<=mid)
		update(left(node),start,mid,index,val);
	else
		update(right(node),mid+1,stop,index,val);

	if(t[left(node)].first>t[right(node)].first)
		t[node]=t[left(node)];
	else if(t[left(node)].first==t[right(node)].first)
		t[node]=a[t[left(node)].second]<a[t[right(node)].second]?t[left(node)]:t[right(node)];
	else
		t[node]=t[right(node)];
//	trace3(node,t[node].first,t[node].second);
}


int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	a.resize(n);
	score.resize(n);
	Prev.resize(n);
	Next.resize(n);
	rep(i,0,n)
		cin>>a[i];
//	trace1(n);
//	tracev(a);
	Prev[0]=-1;
	Next[n-1]=-1;
	rep(i,1,n-1)
	{
		Prev[i]=i-1;
		Next[i]=i+1;
		score[i]=min(a[i-1],a[i+1]);
	}
	int h=ceil(log2(2*n-1));
	t.resize((int)pow(2,h+2));
	build(0,0,n-1);
	ll ans=0;
	rep(j,0,n-2)
	{
		pii m=t[0];
		ans+=m.first;
		int i=m.second;
//		trace4(j,m.first,m.second,a[m.second]);
		Next[Prev[i]]=Next[i];
		Prev[Next[i]]=Prev[i];
		update(0,0,n-1,i,0);
		if(Prev[i]>0)
		{
//			trace1(min(a[Next[i]],a.at(Prev[Prev[i]])));
			update(0,0,n-1,Prev[i],min(a[Next[i]],a.at(Prev[Prev[i]])));
		}
		if(Next[i]<n-1)
		{
			update(0,0,n-1,Next[i],min(a[Prev[i]],a[Next[Next[i]]]));
//			trace1(min(a[Prev[i]],a[Next[Next[i]]]));
		}
	}
	cout<<ans<<endl;
	return 0;
}
