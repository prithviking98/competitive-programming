#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int checkcount(string p,string s)
{
	//cout<<p<<"\t"<<s<<endl;
	/*for(int i=0;i<p.size();++i)
	{
		//cout<<s.find(p[i],0)<<"	";
		if(s.find(p[i],0)==string::npos)
		{
			//cout<<s.find(p[i],0)<<" test  ";
			return 0;
		}
	}
	return 1;*/
	set <char> c;
	/*for(int i=0;i<s.size();++i)
		c.insert(s[i]);*/
	c=s;
	if(c.size()==p.size())
		return 1;
	else
		return 0;
}

int main()
{
	int nflats=1000000,length=0,n,a,b,i,j;
	cin>>n;
	string s,t,p;
	cin>>s;
	//cout<<s<<endl;
	t=s;
	sort(t.begin(),t.end());
	//cout<<t<<endl;
	p=t[0];
	rep(i,0,n)
		if(t[i]!=p[p.size()-1])
			p+=t[i];
	//cout<<p<<endl;
	t=s;
	rep(a,0,n-1)
	{
		b=n-1;
		for(j=n-1-a;j>=1;j/=2)
		{
			while((b-j>=a)&&checkcount(p,t.substr(a,b-j-a+1)))
			{
				//cout<<t.substr(a,b-j-a+1)<<"	"<<b<<endl;
				b-=j;
			}
		}
		//cout<<endl<<t.substr(a,b-a+1);
		if(checkcount(p,t.substr(a,b-a+1)))
		{
			length=b-a+1;
			//cout<<"\nlength="<<length<<endl;
			if(nflats>length)
				nflats=length;
		}
	}
	if(n==1)
		nflats=1;
	cout<<nflats<<endl;
	return 0;
}
