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

#define E 0.000001
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,s,y;
		cin>>n>>s>>y;
		vi v(n),d(n),p(n),l(n);
		rep(i,0,n)
			cin>>v[i];
		rep(i,0,n)
			cin>>d[i];
		rep(i,0,n)
			cin>>p[i];
		rep(i,0,n)
			cin>>l[i];
		double time=0;
		const double crosstime=y/(double)s;
		rep(i,0,n)
		{
			if(d[i]==1)
			{
				double curpos,nextpos;
				curpos=time*v[i]+p[i];
				nextpos=curpos+crosstime*v[i];
				if(curpos<-E&&nextpos<-E)
					time+=crosstime;
				else if(curpos-l[i]>E)
					time+=crosstime;
				else if(curpos<-E&&nextpos>-E||(curpos>=-E&&curpos<0))
				{
					time+=(-curpos+l[i]+E)/v[i]+crosstime;
				}
				else if(curpos>=0&&curpos-l[i]<E)
				{
					time+=crosstime+(l[i]-curpos+E)/v[i];
				}
			}
			if(d[i]==0)
			{
				double curpos,nextpos;
				curpos=-time*v[i]+p[i];
				nextpos=curpos-crosstime*v[i];
				if(curpos>E&&nextpos>E)
					time+=crosstime;
				else if(curpos+l[i]<-E)
					time+=crosstime;
				else if(curpos>E&&nextpos<E||(curpos<=E&&curpos>0))
				{
					time+=(curpos+l[i]+E)/v[i]+crosstime;
				}
				else if(curpos<=0&&curpos+l[i]>-E)
				{
					time+=crosstime+(l[i]+curpos+E)/v[i];
				}
			}
		}
		cout<<time<<endl;
	}
	return 0;
}
