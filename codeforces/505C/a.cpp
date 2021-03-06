#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;
const int ni=30000;

int maxt(const int d,const int length, const vi  p, vector <vi > &m,int ni)
{
	int l=length-d+250;	
	if(m[d][l]>-1)
		return m[d][l];
	else
	{
		int u,t;
		u=t=0;
		rep(i,-1,2)
		{
			if(length+i==0||d+length+i>ni)
				continue;
			else
			{
				t=maxt(d+length+i,length+i,p,m,ni);
				if(t>=u)
					u=t;
			}
		}
		m[d][l]=p[d]+u;
		return m[d][l];
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int n,d,t;
	cin>>n>>d;
	//cout<<n<<" "<<d<<endl;
	vi p(ni);
	int reach=0;
	rep(i,0,n)
	{
		cin>>t;
		p[t]++;
		if(t>reach)
			reach=t;
	}
	//cout<<p.size()<<endl;
	int k;
	k=(-(2*d+1)+sqrt(8*reach+(2*d-1)*(2*d-1)))/2;
	//cout<<k<<endl;
	vector < vi > m(reach+1);
	rep(i,0,reach+1)
	{
		m[i].resize(250*2);
		rep(j,0,500)
			m[i][j]=-1;
	}
	int count;
	count=maxt(d,d,p,m,reach);
	cout<<count<<endl;
		
	return 0;
}
