#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PB push_back
typedef long long ll;
typedef vector<int> vi;

struct subsequence
{
	int b,e;
};

int main()
{
	int n;
	cin>>n;
	vi a(n);
	vector <subsequence> s;
	rep(i,0,n)
		cin>>a[i];
	int i=0;
	while(i<n)
	{
		int start,stop;
		start=stop=i;
		while(stop<n-1&&a[stop+1]>a[stop])
			++stop;
		subsequence temp;
		temp.b=start;
		temp.e=stop;
		s.PB(temp);
		i=stop+1;
	}
	//comment
	int m=s[0].e-s[0].b+1;
	rep(i,0,s.size()-1)
	{
		int l1,l2,l;
		if(s[i+1].b!=n-1&&a[s[i+1].b+1]>a[s[i].e]+1)
			l1=s[i+1].e-s[i].b+1;
		else
			l1=s[i].e-s[i].b+2;
		if(s[i].e>0&&a[s[i].e-1]<a[s[i+1].b]-1)
			l2=s[i+1].e-s[i].b+1;
		else
			l2=s[i+1].e-s[i+1].b+2;
		l=l2>l1?l2:l1;
		if(l>m)
			m=l;
	}
	cout<<m<<endl;
	return 0;
}
