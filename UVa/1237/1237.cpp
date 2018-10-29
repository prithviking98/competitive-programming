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

vi l(10005),h(10005);
vector<string> name(10005);
int d;
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>d;
		rep(i,0,d)
			cin>>name[i]>>l[i]>>h[i];
		int q,p,count,index;
		cin>>q;
		while(q--)
		{
			cin>>p;
			count=0;
			rep(i,0,d)
			{
				if(p<=h[i]&&p>=l[i])
				{
					count++;
					if(count==1)
						index=i;
				}
			}
			if(count!=1)
				cout<<"UNDETERMINED"<<endl;
			else
				cout<<name[index]<<endl;
		}
		if(T>0)
			cout<<endl;
	}
	return 0;
}
