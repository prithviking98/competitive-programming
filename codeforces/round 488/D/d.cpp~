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

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vector<pii> a(n),b(m);
	rep(i,0,n)
		cin>>a[i].first>>a[i].second;
	rep(i,0,m)
		cin>>b[i].first>>b[i].second;
	int count=0,common=0;
	rep(i,0,n)
	{
		int fc=0,sc=0;
		rep(j,0,m)
			if((a[i].first==b[j].first||a[i].first==b[j].second)&&(a[i]!=b[j]&&a[i]!=make_pair(b[j].second,b[j].first)))
				fc++;
		rep(j,0,m)
			if((a[i].second==b[j].first||a[i].second==b[j].second)&&(a[i]!=b[j]&&a[i]!=make_pair(b[j].second,b[j].first)))
				sc++;
		if(fc*sc==0)
		{
			if(fc>0)
			{
				count++;
				if(count==1)
					common=a[i].first;
				else if (common!=a[i].first)
					common==0;
			}
			else if(sc>0)
			{
				count++;
				if(count==1)
					common=a[i].second;
				else if(common!=a[i].second)
					common=0;
			}
		}
		else
		{
			count=-1;
			break;
		}
	}
	if(count==1)
	{
		cout<<common<<endl;
		return 0;
	}
	else if(count==-1)
	{
		cout<<-1<<endl;
		return 0;
	}
	int count2=0,common2=0;
	rep(i,0,m)
	{
		int fc=0,sc=0;
		rep(j,0,n)
			if((b[i].first==a[j].first||b[i].first==a[j].second)&&(b[i]!=a[j]&&a[i]!=make_pair(a[j].second,a[j].first)))
				fc++;
		rep(j,0,n)
			if((b[i].second==a[j].first||b[i].second==a[j].second)&&(b[i]!=a[j]&&a[i]!=make_pair(a[j].second,a[j].first)))
				sc++;
		if(fc*sc==0)
		{
			if(fc>0)
			{
				count2++;
				if(count2==1)
					common2=b[i].first;
				else if(common2!=b[i].first)
					common2=0;
			}
			else if(sc>0)
			{
				count2++;
				if(count2==1)
					common2=b[i].second;
				else if(common2!=b[i].second)
					common2=0;
			}
		}
		else
		{
			count2=-1;
			break;
		}
	}
	if(count2==1)
		cout<<common2<<endl;
	else if(count2>1)
	{
		if(common==common2&&common!=0)
			cout<<common<<endl;
		else if(common2==-1)
			cout<<-1<<endl;
		else
			cout<<0<<endl;
	}
	else
		cout<<-1<<endl;
	return 0;
}
