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

struct query
{
	int l,r,p,index,ans;
	char c;
};

bool comp1(const query& a,const query &b)
{
	return a.p<b.p;
}

bool comp2(const query& a,const query &b)
{
	return a.index<b.index;
}
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vector <string> s(n);
	rep(i,0,n)
		cin>>s[i];
	int q;
	cin>>q;
	vector <query> qset(q);
	rep(i,0,q)
	{
		cin>>qset[i].l>>qset[i].r>>qset[i].p>>qset[i].c;
		qset[i].l--;
		qset[i].r--;
		qset[i].p--;
		qset[i].index=i;
	}
	sort(qset.begin(),qset.end(),comp1);
	vvi v(26);
	rep(i,0,26)
		v[i].resize(n);
	int qi=0;
	rep(i,0,20)
	{
		if(qset[qi].p>i)
			continue;
		rep(j,0,n)
		{
			if(i<s[j].size())
			{
				int a=s[j][i]-'a';
				rep(k,0,26)
				{
					if(k==a&&j>0)
						v[k][j]=v[k][j-1]+1;
					else if(k==a)
						v[k][j]=1;
					else if(j>0)
						v[k][j]=v[k][j-1];
					else
						v[k][j]=0;
				}
			}
			else
			{
				rep(k,0,26)
				{
					v[k][j]=v[k][j-1];
				}
			}
		}
		while(qset[qi].p==i)
		{
			int a=qset[qi].c-'a';
			int l=qset[qi].l,r=qset[qi].r;
			if(l>0)
				qset[qi].ans=v[a][r]-v[a][l-1];
			else
				qset[qi].ans=v[a][r];
			qi++;
		}
	}
	sort(qset.begin(),qset.end(),comp2);
	rep(i,0,q)
		cout<<qset[i].ans<<endl;
	return 0;
}
