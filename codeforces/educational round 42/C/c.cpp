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

void extract(vi &select,int t)
{
	int n=select.size();
	//cout<<"inside getn"<<endl;
	//trace2(n,t);
	rep(i,0,n)
	{
		int k=t%2;
		//trace2(i,k);
		select[n-1-i]=k;
		t/=2;
	}
}

int getn(vi k)
{
	if(k[0]==0)
		return 0;
	int n=k.size();
	int p=1,num=0;
	for(int i=n-1;i>=0;--i)
	{
		num+=p*k[i];
		p*=10;
	}
	return num;
}
int main()
{
	ios::sync_with_stdio(0);
	string s;
	cin>>s;
	vi a(s.size());
	rep(i,0,s.size())
		a[i]=s[i]-'0';
	int n=s.size();
	vi select(n);
	int t=pow(2,n);
	int m=0;
	for(int i=1;i<t;++i)
	{
//		trace1(i);
		extract(select,i);
		vi k;
		rep(j,0,n)
		{
			//trace2(select[j],j);
			if(select[j])
				k.PUB(a[j]);
		}
		int num;
		if(num=getn(k))
		{
			//trace1(num);
			double root=sqrt(num);
			if(root==floor(root))
			{
				if(k.size()>m)
					m=k.size();
			}
		}
	}
	if(m==0)
		cout<<-1<<endl;
	else
		cout<<n-m<<endl;

	return 0;
}
