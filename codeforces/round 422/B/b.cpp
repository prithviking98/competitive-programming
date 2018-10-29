#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

class errors
{
public:
	int a[1000];
	int e;
	errors()
	{
		e=0;
		for(int i=0;i<1000;++i)
			a[i]=0;
	}
};

errors comp(string s,string t,int i)
{
	errors m;
	for(int j=0;j<s.size();++j)
	{
		//cout<<s[j]<<" "<<t[i+j]<<endl;
		if(s[j]!=t[i+j])
		{
			//cout<<j+1<<endl;
			m.a[m.e]=j+1;
			++m.e;
			//cout<<m.e<<endl;
		}
	}
	return m;
}

int main()
{
	int a,b,i;
	errors m,temp;
	m.e=1001;
	string s,t;
	cin>>a>>b;
	cin>>s>>t;
	//cout<<a<<b<<s<<" "<<t<<endl;
	for(i=0;i<=b-a;++i)
	{
		temp=comp(s,t,i);
		if(temp.e<=m.e)
			m=temp;
	}
	cout<<m.e<<endl;
	for(i=0;i<m.e;++i)
		cout<<m.a[i]<<" ";
	cout<<endl;
	return 0;
}
