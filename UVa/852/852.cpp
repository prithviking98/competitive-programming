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

vi dr={1,0,-1,0};
vi dc={0,-1,0,1};

int dfs(int root,int r,int c,vvi &b, vvi &v)
{
	if(r>8||r<0||c>8||c<0)
		return 0;
	else if(b[r][c]!=root||v[r][c])
		return 0;
	v[r][c]=1;
	int ans=1;
	rep(i,0,4)
		ans+=dfs(root,r+dr[i],c+dc[i],b,v);
	return ans;
}

int dfss(int &whose,int r,int c,vvi &b,vvi &v)
{
	if(r>8||r<0||c>8||c<0)
		return 0;
	else if(b[r][c]!=2)
	{
		if(whose==-1)
			whose=b[r][c];
		else if(whose!=b[r][c])
		{
			whose=-2;
		}
		return 0;
	}
	else if(v[r][c])
		return 0;
	v[r][c]=1;
	int ans=1;
	rep(i,0,4)
		ans+=dfss(whose,r+dr[i],c+dc[i],b,v);
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--)
	{
		vvi b(9),v(9);
		rep(i,0,9)
		{
			b[i].resize(9);
			v[i].resize(9);
			rep(j,0,9)
				v[i][j]=0;
		}

		rep(i,0,9)
			rep(j,0,9)
			{
				char c;
				cin>>c;
				if(c=='O')
					b[i][j]=0;
				else if(c=='X')
					b[i][j]=1;
				else
					b[i][j]=2;
			}
		int bscore=0,wscore=0;
		rep(i,0,9)
			rep(j,0,9)
			{
				if(v[i][j])
					continue;
				if(b[i][j]==0)
					wscore+=dfs(0,i,j,b,v);
				else if(b[i][j]==1)
					bscore+=dfs(1,i,j,b,v);
				else 
				{
					int whose=-1;
					int count=dfss(whose,i,j,b,v);
					if(whose==0)
						wscore+=count;
					else if(whose==1)
						bscore+=count;
				}
			}
		cout<<"Black "<<bscore<<" White "<<wscore<<endl;
	}
		
	return 0;
}
