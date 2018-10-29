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
int b; //global block size
struct query
{
	int first,second,index;
};

bool mocmp(const query &x,const query &y)
{
	if(x.first/b<y.first/b)
		return true;
	else if(x.first/b==y.first/b)
		return x.second<y.second;
	else 
		return false;
}

int main()
{
	ios::sync_with_stdio(0);
	int n,t;
	cin>>n>>t;
	b=sqrt(n);
	//trace1(b);
	vector<ll> a(n);
	rep(i,0,n)
		cin>>a[i];
	vector<query> q(t);
	int l,r;
	rep(i,0,t)
	{
		cin>>l>>r;
		q[i].first=l-1;
		q[i].second=r-1;
		q[i].index=i;
	}
	sort(q.begin(),q.end(),mocmp);
	/*
	rep(i,0,t)
		trace3(q[i].first,q[i].second,i);
		*/
	int mol,mor;
	mol=mor=0;
	vector<ll> occ(1000001,0);
	occ[a[mol]]=1;
	ll power=a[0];
	vector<ll> p(t);
	rep(i,0,t)
	{
		while(mor<q[i].second)
		{
			++mor;
			++occ[a[mor]];
			power=power+(2*occ[a[mor]]-1)*a[mor];
		}
		while(mor>q[i].second)
		{
			if(occ[a[mor]]>0)
			{
				--occ[a[mor]]; 
				//trace2(a[mor],occ[a[mor]]);
				power=power-(2*occ[a[mor]]+1)*a[mor];
			}
			//trace1(power);
			--mor;
		} 
		while(mol<q[i].first)
		{
			if(occ[a[mol]]>0)
			{
				--occ[a[mol]];
				//trace2(a[mol],occ[a[mol]]);
				power=power-(2*occ[a[mol]]+1)*a[mol];
			}
			//trace1(power);
			++mol;
		}
		while(mol>q[i].first)
		{
			--mol;
			++occ[a[mol]];
			power=power+(2*occ[a[mol]]-1)*a[mol];
		}
		p[q[i].index]=power;
	}
	//cout<<endl;
	rep(i,0,t)
		cout<<p[i]<<endl;

	return 0;
}
