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

struct node
{
	vi a,d;
	vector <pii> m3;
	int visited;
};

void insert(vector<pii> &a,pii t)
{
	if(t.first>a[0].first)
		a[0]=t;
	sort(a.begin(),a.end());
}

void bfs(vector<node> &v,int source)
{
	rep(i,1,v.size())
		v[i].visited=0;
	v[source].m3.PUB({-1,-1});
	v[source].m3.PUB({-1,-1});
	v[source].m3.PUB({-1,-1});
	v[source].d.resize(v.size(),INT_MAX);
	queue<pii> q;
	q.push({source,0});
	while(!q.empty())
	{
		pii t=q.front();
		q.pop();
		if(v[t.first].visited==0)
		{
			v[t.first].visited=1;
			v[source].d[t.first]=t.second;
			//trace3(source,t.first,v[source].d[t.first]);
			if(t.first!=source)
				insert(v[source].m3,{t.second,t.first});
			rep(i,0,v[t.first].a.size())
			{
				q.push({v[t.first].a[i],t.second+1});
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n,m;
	cin>>n>>m;
	vector <node> v(n+1),vr(n+1);
	int src,dest;
	rep(i,0,m)
	{
		cin>>src>>dest;
		v[src].a.PUB(dest);
		vr[dest].a.PUB(src);
	}
	rep(i,1,n+1)
	{
		//cout<<"norm"<<endl;
		bfs(v,i);
		//cout<<"rev"<<endl;
		bfs(vr,i);
	}
	int max=0,maxa,maxb,maxc,maxd;
	rep(i,1,n+1)
	{
		rep(j,1,n+1)
		{
			//trace2(i,j);
			if(v[i].d[j]==INT_MAX||v[i].d[j]==0)
				continue;
			int dist1=v[i].d[j];
			int a;
			if(vr[i].m3[2].second==-1)
				break;
			else if(vr[i].m3[2].second!=j)
			{
				dist1+=vr[i].m3[2].first;
				a=vr[i].m3[2].second;
			}
			else if(vr[i].m3[1].second!=-1)
			{
				dist1+=vr[i].m3[1].first;
				a=vr[i].m3[1].second;
			}
			else
				break;
			int b=v[j].m3[2].second;
			if(b==-1)
				continue;
			else if(b==a||b==i)
			{
				b=v[j].m3[1].second;
				if(b==-1)
					goto x;
				else if(b==a||b==i)
				{
					b=v[j].m3[0].second;
					if(b==-1)
						goto x;
					else
						dist1+=v[j].m3[0].first;
				}
				else
					dist1+=v[j].m3[1].first;
			}
			else
				dist1+=v[j].m3[2].first;
			if(dist1>max)
			{
				max=dist1;
				maxa=a;
				maxb=i;
				maxc=j;
				maxd=b;
			//	trace1(max);
			//	trace4(maxa,maxb,maxc,maxd);
			}

			//NOTICE
			//j gets priority
		 x:
			dist1=v[i].d[j];
			if(v[j].m3[2].second==-1)
				continue;
			else if(v[j].m3[2].second!=i)
			{
				dist1+=v[j].m3[2].first;
				a=v[j].m3[2].second;
			}
			else if(v[j].m3[1].second!=-1)
			{
				dist1+=v[j].m3[1].first;
				a=v[j].m3[1].second;
			}
			else 
				continue;

			b=vr[i].m3[2].second;
			if(b==a||b==j)
			{
				b=vr[i].m3[1].second;
				if(b==-1)
					continue;
				else if(b==a||b==j)
				{
					b=vr[i].m3[0].second;
					if(b==-1)
						continue;
					else
						dist1+=vr[i].m3[0].first;
				}
				else
					dist1+=vr[i].m3[1].first;
			}
			else
				dist1+=vr[i].m3[2].first;
			if(dist1>max)
			{
				max=dist1;
				maxa=b;
				maxb=i;
				maxc=j;
				maxd=a;
			//	trace1(max);
			//	trace4(maxa,maxb,maxc,maxd);
			}
		}
	}

//	cout<<max<<endl;
	printf("%d %d %d %d\n",maxa,maxb,maxc,maxd);
	return 0;
}
