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

int main()
{

	ios::sync_with_stdio(0);
	int n,pos,l,r;
	cin>>n>>pos>>l>>r;
	int time=0;
	while(1)
	{
		if(pos>=l&&pos<=r)
		{
			if(l==1&&r==n)
				break;
			else if(l==1&&r<n)
			{
				time+=r-pos+1;
				break;
			}
			else if(l>1&&r==n)
			{
				time+=pos-l+1;
				break;
			}
			else if(l>1&&r<n)
			{
				time+=r-l+min(pos-l,r-pos)+2;
				break;
			}
		}
		else if(pos<l)
		{
			time+=l-pos;
			pos=l;
		}
		else 
		{
			time+=pos-r;
			pos=r;
		}
	}
	cout<<time<<endl;
	return 0;
}
