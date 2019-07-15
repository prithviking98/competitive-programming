#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

#define TRACE
#ifdef TRACE
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracea(a,n) rep(II,0,n) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracevv(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#define tracem(a,r,c)\
	{\
	rep(II,0,r){\
		rep(JJ,0,c)\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}
#else
#define trace1(x)   
#define trace2(x,y)   
#define trace3(x,y,z)   
#define trace4(w,x,y,z)  
#define tracev(a) 
#define tracea(a,n)  
#define tracevv(a)  
#define tracem(a,r,c)  
#endif

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	cin.ignore();
	while(T--)
	{
		string line;
		vi a;
		int alt;
		while(true)
		{
			getline(cin,line,'\n');
			if(line.size()==0)
				break;

//			trace2(line,line.size());
			sscanf(line.c_str(),"%d",&alt);
			a.push_back(alt);
		}
		int n=a.size();
		if(n==0)
		{
			T++;
			continue;
		}
		vi dp,pos,p(n,-1);
		dp.push_back(-1);
		pos.push_back(-1);
		for(int i=0;i<n;++i)
		{
			int f=0;
			for(int b=dp.size()-1;b>=1;b/=2)
				while(f+b<dp.size()&&dp[f+b]<a[i])
					f+=b;
			if(f==dp.size()-1)
			{
				dp.push_back(a[i]);
				pos.push_back(i);
				p[i]=pos[f];
			}
			else
			{
				p[i]=pos[f];
				if(a[i]<dp[f+1])
				{
					dp[f+1]=a[i];
					pos[f+1]=i;
				}
			}
		}
		cout<<"Max hits: "<<dp.size()-1<<endl;
		vi ans;
		int index=pos.back();
		while(index!=-1)
		{
			ans.push_back(a[index]);
			index=p[index];
		}
		for(int i=ans.size()-1;i>=0;--i)
			cout<<ans[i]<<endl;
		if(T>0)
			cout<<endl;
	}
	return 0;
}
