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

struct Move
{
	int i,r,c;
};

int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin>>n>>k;
	vvi a(4);
	rep(i,0,4)
		a[i].resize(n);
	rep(i,0,4)
		rep(j,0,n)
		{
			cin>>a[i][j];
//			trace3(i,j,a[i][j]);
		}
	vector<Move> m;
	Move t;
	rep(i,1,3)
	{
		rep(j,0,n)
		{
			if(i==1&&a[i][j]&&a[i][j]==a[0][j])
			{
				t.i=a[0][j];
				t.r=1;
				t.c=j+1;
				m.PUB(t);
				a[i][j]=0;
			}
			else if(i==2&&a[i][j]&&a[i][j]==a[3][j])
			{
				t.i=a[3][j];
				t.r=4;
				t.c=j+1;
				m.PUB(t);
				a[i][j]=0;
			}
		}
	}
	int f=0;
	rep(i,1,3)
	{
		rep(j,0,n)
		{
			if(a[i][j]==0)
				f++;
//			cout<<a[i][j]<<endl;
		}
//		cout<<endl;
	}
//	trace1(f);
	if(f==0)
	{
		cout<<-1<<endl;
		return 0;
	}
	
	while(f<2*n)
	{
		rep(i,1,3)
		{
			if(i==1)
			{
				rep(j,0,n)
				{
					if(a[i][j]&&a[i][j]==a[0][j])
					{
						t.i=a[0][j];
						t.r=1;
						t.c=j+1;
						m.PUB(t);
						a[i][j]=0;
					}
					if(j<n-1&&a[i][j]&&a[i][j+1]==0)
					{
						a[i][j+1]=a[i][j];
						a[i][j]=0;
						t.i=a[i][j+1];
						t.r=i+1;
						t.c=j+2;
						m.PUB(t);
					}
					else if(j==n-1&&a[i][j]&&a[i+1][j]==0)
					{
						a[i+1][j]=a[i][j];
						a[i][j]=0;
						t.i=a[i+1][j];
						t.r=i+2;
						t.c=j+1;
						m.PUB(t);
					}
				}
			}
			else if(i==2)
			{
				for(int j=n-1;j>=0;--j)
				{
					if(a[i][j]&&a[i][j]==a[3][j])
					{
						t.i=a[3][j];
						t.r=4;
						t.c=j+1;
						m.PUB(t);
						a[i][j]=0;
					}
					if(j>0&&a[i][j]&&a[i][j-1]==0)
					{
						a[i][j-1]=a[i][j];
						a[i][j]=0;
						t.i=a[i][j-1];
						t.r=i+1;
						t.c=j;
						m.PUB(t);
					}
					else if(j==0&&a[i][j]&&a[i-1][j]==0)
					{
						a[i-1][j]=a[i][j];
						a[i][j]=0;
						t.i=a[i-1][j];
						t.r=i;
						t.c=j+1;
						m.PUB(t);
					}
				}
			}
		}
		rep(i,1,3)
		{
			rep(j,0,n)
			{
				if(i==1&&a[i][j]&&a[i][j]==a[0][j])
				{
					t.i=a[0][j];
					t.r=1;
					t.c=j+1;
					m.PUB(t);
					a[i][j]=0;
				}
				else if(i==2&&a[i][j]&&a[i][j]==a[3][j])
				{
					t.i=a[3][j];
					t.r=4;
					t.c=j+1;
					m.PUB(t);
					a[i][j]=0;
				}
			}
		}
		f=0;
		rep(i,1,3)
		{
			rep(j,0,n)
			{
				if(a[i][j]==0)
					f++;
			}
		}
	}
	cout<<m.size()<<endl;
	rep(i,0,m.size())
		cout<<m[i].i<<" "<<m[i].r<<" "<<m[i].c<<endl;
	return 0;
}
