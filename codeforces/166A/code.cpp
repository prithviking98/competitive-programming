#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

class team
{
public:
	int p,t;
	team(){p=0;t=0;}
};
bool comp(team x,team y)
{
	if(x.p!=y.p)
		return x.p>y.p;
	else
		return x.t<y.t;
}
//comment
int main()
{
	int n,k,b,t,upper,lower,i;
	cin >>n>>k;
	vector<team> list(n);
	rep(i,0,n)
		cin>>list[i].p>>list[i].t;
	/*rep(i,0,n)
		cout<<list[i].p<<endl;*/
	sort(list.begin(),list.end(),comp);
	/*rep(i,0,n)
		cout<<list[i].p<<endl;*/
	t=k-1;
	for(b=n-1;b>=1;b/=2)
	{
		while(t+b<=n-1&&(list[t+b].p==list[k-1].p&&list[t+b].t==list[k-1].t))
			t+=b;
	}
	upper=t;
	//cout<<upper<<endl;
	t=k-1;
	for(b=n-1;b>=1;b/=2)
	{
		while(t-b>=0&&(list[t-b].p==list[k-1].p&&list[t-b].t==list[k-1].t))
			t-=b;
	}
	lower=t;
	//cout<<lower<<endl;
	int total=upper-lower+1;
	cout<<total<<endl;
	return 0;
}
