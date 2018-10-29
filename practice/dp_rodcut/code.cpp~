#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

pair <vi,vi> bottom_up_rod_cut(vi p,int n)
{
	vi r(n+1);
	r[0]=0;
	vi s(n+1);
	s[0]=1;
	rep(i,1,n+1)
	{
		int m=INT_MIN;
		rep(j,1,i+1)
		{
			if(m<p[j-1]+r[i-j])
			{
				s[i]=j;
				m=p[j-1]+r[i-j];
			}
		}
		r[i]=m;
	}
	pair <vi,vi> l;
	l=make_pair(r,s);
	return l;
}
int main()
{
	int n,i,j;
	vi p(10);
	pair <vi,vi> l;
	p={1,5,8,9,10,17,17,20,24,30};
	l=bottom_up_rod_cut(p,10);
	rep(i,1,11)
	{
		printf("best price for length %d = %d	\n",i,l.first[i]);
		cout<<i<<" = ";
		int n=i;
		while(n>0)
		{
			cout<<l.second[n]<<"+";
			n=n-l.second[n];
		}
		cout<<"\b\b\n\n";
	}
	cout<<endl;
	return 0;
}
