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

int isPrime(int i)
{
	for(int j=2;j<=sqrt(i);++j)
		if(i%j==0)
			return 0;
	return 1;
}

int main()
{
	ios::sync_with_stdio(0);
	int q;
	cin>>q;
	vi p(30);
	for(int i=2,j=0;j<30;++i)
	{
		if(isPrime(i))
		{
			p[j]=i;
			++j;
		}
	}
			
	while(q--)
	{
		ll l,r;
		cin>>l>>r;
		int count=0;
		long double a,b;
		int i=0;
		a=pow(l,1/(long double)p[i]);
		b=pow(r,1/(long double)p[i]);
		int flag=0;
		unordered_set<int> s;
		while(floor(b)-floor(a)>0)
		{
			trace2(a,b);
			/*
			if(a==floor(a)&&a!=1)
				count+=(floor(b)-floor(a)+1);
			else
				count+=(floor(b)-floor(a));
			if(floor(b)==b)
			{
				if(flag)
					count--;
				else
					flag=1;
			}
			*/
			for(int j=ceil(a);j<=floor(b);++j)
			{
				ll k=pow(j,p[i]);
				if(s.count(k)==0)
					s.insert(k);
			}
			++i;
			a=pow(l,1/(long double)p[i]);
			b=pow(r,1/(long double)p[i]);
		}
		if(l==r)
			s.insert(l);
		/*
		if(l==1)
			count++;
		*/
		cout<<s.size()<<endl;
	}
	return 0;
}
