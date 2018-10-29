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

typedef long long LL;
typedef vector<int> vi;
//typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
//typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

double wind(LL r1,LL r2)
{
	return ((double)r2+r1)/((double)r2-r1);
}

int main()
{
	ios::sync_with_stdio(0);
	LL n,l,w;
	cin>>n>>l>>w;
	if(n==1)
	{
		cout<<0<<endl;
		return 0;
	}
//	trace3(n,l,w);
	vector<LL> ll,lr,rl,rr; //left going to right=lr
	LL op,od;
	LL x,v;
	rep(i,0,n)
	{
		cin>>x>>v;
//		trace2(x,v);
		if(x>0&&v>0)
			rr.PUB(x);
		else if(x>0&&v<0)
			rl.PUB(x);
		else if(x<0&&v<0)
		{
			if(x+l>0)
				rl.PUB(x);
			else
				ll.PUB(x);
		}
		else if(x<0&&v>0)
			lr.PUB(x);
	}
	sort(rr.begin(),rr.end());
	sort(rl.begin(),rl.end());
	sort(lr.rbegin(),lr.rend());
	sort(ll.begin(),ll.end());
//	trace4(lr.size(),ll.size(),rl.size(),rr.size());
	
	LL count=0;
	count=lr.size()*rl.size();
//	trace3(count,lr.size(),rl.size());
	rep(i,0,rr.size())
	{
		if(rl.size()==0)
			break;
		LL r1,r2;
		r1=rr[i];
		LL f=0;
		for(LL b=rl.size()-1;b>=1;b/=2)
			while(f+b<rl.size()&&rl[f+b]<r1)
				f+=b;
		if(f>0||(f==0&&rl[f]<r1))
			f++;
		if(f==rl.size())
			continue;
//		trace1(f);
		LL k=f;
		for(LL b=rl.size()-1-f;b>=1;b/=2)
			while(f+b<rl.size()&&wind(r1,rl[f+b])>=w)
				f+=b;
//		trace4(r1,rl[f],f,wind(r1,rl[f]));
		if(f>k||(f==k&&wind(r1,rl[f])>=w))
			f++;
//		trace1(f);
		if(f<rl.size())
			count=count+rl.size()-f;
//		trace1(rl.size());
//		trace1(count);
	}
	rep(i,0,ll.size())
	{
		if(lr.size()==0)
			break;
		LL r1,r2;
		r1=abs(ll[i]+l);
		LL f=0;
		for(LL b=lr.size()-1;b>=1;b/=2)
			while(f+b<lr.size()&&lr[f+b]>ll[i])
				f+=b;
		if(f>0||(f==0&&lr[f]>ll[i]))
			f++;
//		trace1(f);
		if(f==lr.size())
			continue;
		LL k=f;
		for(LL b=lr.size()-1-f;b>=1;b/=2)
			while(f+b<lr.size()&&wind(r1,abs(lr[f+b]+l))>=w)
				f+=b;
		if(f>k||(f==k&&wind(r1,abs(lr[f]+l))>=w))
			f++;
//		trace2(f,lr.size());
		if(f<lr.size())
			count=count+lr.size()-f;
	}

	cout<<count<<endl;

	return 0;
}
