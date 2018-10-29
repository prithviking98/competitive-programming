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

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi c(n),t(n);
	rep(i,0,n)
		cin>>c[i];
	rep(i,0,n)
		cin>>t[i];
	vi author,trans,autrans;
	rep(i,0,n)
	{
		if(t[i]==1)
			author.PUB(c[i]);
		else if(t[i]==2)
			trans.PUB(c[i]);
		else if(t[i]==3)
			autrans.PUB(c[i]);
	}
	sort(author.begin(),author.end());
	sort(trans.begin(),trans.end());
	sort(autrans.begin(),autrans.end());
	int m;
	if(author.size()!=0&&trans.size()!=0&&autrans.size()!=0)
		m=min(author[0]+trans[0],autrans[0]);
	else if((author.size()==0||trans.size()==0)&&autrans.size()!=0)
		m=autrans[0];
	else if(autrans.size()==0)
		m=author[0]+trans[0];
	cout<<m<<endl;
	return 0;
}
