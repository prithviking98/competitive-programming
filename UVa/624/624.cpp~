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

int n,m,maxstore,sum;
vi a,maxsol,cur;

void search(int last,int index)
{
	if(sum>n||index==a.size()-1)
	{
		if(sum>n&&sum-last>maxstore)
		{
			maxstore=sum-last;
			maxsol=cur;
			maxsol.POB();
		}
		else if(sum<=n&&sum>maxstore)
		{
			maxstore=sum;
			maxsol=cur;
		}
		return;
	}
	search(last,index+1);
	last=a[index+1];
	cur.PUB(last);
	sum+=last;
	search(last,index+1);
	cur.POB();
	sum-=last;
}


int main()
{
	ios::sync_with_stdio(0);
	while(cin>>n)
	{
		cin>>m;
		a.resize(m);
		rep(i,0,m)
			cin>>a[i];
		sum=0;
		cur.clear();
		maxstore=0;
		maxsol.clear();
		search(0,-1);
		rep(i,0,maxsol.size())
			cout<<maxsol[i]<<" ";
		cout<<"sum:"<<maxstore<<endl;
	}

	return 0;
}
