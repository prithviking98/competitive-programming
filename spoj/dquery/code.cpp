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
int b;

struct query
{
	int l,r,index;
};

bool mocmp(const query& x,const query &y)
{
	if(x.l/b==y.l/b)
		return x.r<y.r;
	else
		return x.l/b<y.l/b;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	rep(i,0,n)
		cin>>a[i];
	int t;
	cin>>t;
	b=n/sqrt(t);
	if(b==0)
		sqrt(n);
	vector<query> q(t);
	rep(i,0,t)
	{
		int l,r;
		cin>>l>>r;
		q[i].l=l-1;
		q[i].r=r-1;
		q[i].index=i;
	}
	sort(q.begin(),q.end(),mocmp);
	vi p(t);
	vi s(1000001);
	int mol,mor;
	mol=mor=0;
	int u=1;
	s[a[mol]]++;
	rep(i,0,t)
	{
		while(mor<q[i].r)
		{
			++mor;
			if(s[a[mor]]==0)
				++u;
			++s[a[mor]];
		}
		while(mor>q[i].r)
		{
			if(s[a[mor]]==1)
				--u;
			--s[a[mor]];
			--mor;
		}
		while(mol<q[i].l)
		{
			if(s[a[mol]]==1)
				--u;
			--s[a[mol]];
			++mol;
		}
		while(mol>q[i].l)
		{
			mol--;
			if(s[a[mol]]==0)
				u++;
			s[a[mol]]++;
		}
		p[q[i].index]=u;
	}
	rep(i,0,t)
		cout<<p[i]<<endl;

	return 0;
}
