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

void dijkstra(vvi &v,vi &d,priority_queue<pii,vector<pii>,greater<pii> > &p,vi &in)
{
	while(!p.empty())
	{
		pii t=p.top();
		p.pop();
		int u=t.second;
		if(in[u]==3)
			continue;
		if(d[u]==0)
			in[u]=3;
		else
			in[u]++;
		if(in[u]<3)
			continue;
		d[u]=t.first;
//		trace2(u,d[u]);
		rep(i,0,v[u].size())
			p.push({d[u]+1,v[u][i]});
	}
}
	
int main()
{
	ios::sync_with_stdio(0);
	int n;
	while(cin>>n)
	{
		vi d(26,INT_MAX);
		vvi v(26);
		int m;
		cin>>m;
		string s;
		cin>>s;
		int a,b,c;
		sort(s.begin(),s.end());
		a=s[0]-65;
		b=s[1]-65;
		c=s[2]-65;
		d[a]=d[b]=d[c]=0;
		while(m--)
		{
			cin>>s;
			v[s[0]-'A'].PUB(s[1]-'A');
			v[s[1]-'A'].PUB(s[0]-'A');
		}
		priority_queue< pii, vector <pii>, greater <pii> > p;
		p.push({0,a});
		p.push({0,b});
		p.push({0,c});
		vi in(26);
		dijkstra(v,d,p,in);
//		tracev(in);
		int max=0,count=0;
		rep(i,0,26)
		{
			if(max<d[i]&&d[i]!=INT_MAX)
				max=d[i];
			if(in[i]==3)
				count++;
		}
//		trace2(count,n);
		if(count<n)
			cout<<"THIS BRAIN NEVER WAKES UP"<<endl;
		else
			cout<<"WAKE UP IN, "<<max<<", YEARS"<<endl;
	}
	return 0;
}
