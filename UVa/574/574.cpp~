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

int t,n,sum,flag;
vi a(100),sol;
vector <string> solset;
unordered_set<string> s;
void search(int index)
{
//	trace1(index);
	if(index==n)
	{
		sum=0;
		rep(i,0,sol.size())
			sum+=sol[i];
		if(sum==t)
		{
			string p;
			rep(i,0,sol.size())
			{
				int temp=sol[i];
				int j=0;
				string q,sq="a";
				while(temp>0)
				{
					sq[0]='0'+(char)(temp%10);
					q=sq+q;
					j++;
					temp/=10;
				}
				if(i<sol.size()-1)
					p=p+q+"+";
				else
					p+=q;
			}
//			trace1(p);
			if(s.count(p))
				return;
			s.insert(p);
			solset.PUB(p);
			flag=1;
		}
		return;
	}
	search(index+1);
	if(index==-1)
		return;
	sol.PUB(a[index]);
	search(index+1);
	sol.POB();
}
int main()
{
	ios::sync_with_stdio(0);
	while(cin>>t>>n)
	{
		if(t==0||n==0)
			break;
		rep(i,0,n)
			cin>>a[i];
//		tracev(a);
		sum=0;
		sol.clear();
		solset.clear();
		s.clear();
		flag=0;
		cout<<"Sums of "<<t<<":"<<endl;
		search(-1);
		sort(solset.rbegin(),solset.rend());
		if(flag==0)
			cout<<"NONE"<<endl;
		rep(i,0,solset.size())
			cout<<solset[i]<<endl;;
	}
	return 0;
}
