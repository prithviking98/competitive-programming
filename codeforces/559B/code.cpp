#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int eqv(string a,string b)
{
	string c,d;
	c=a;
	d=b;
	sort(c.begin(),c.end());
	sort(d.begin(),d.end());
	if(c!=d)
		return 0;
	else if(a==b)
		return 1;
	else if(a.size()!=1)
	{
		string a1,a2,b1,b2;
		a1=a.substr(0,a.size()/2);
		a2=a.substr(a.size()/2,a.size()/2);
		b1=b.substr(0,b.size()/2);
		b2=b.substr(b.size()/2,b.size()/2);
		//cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<"\n";
		if((eqv(a1,b1)&&eqv(a2,b2))||(eqv(a1,b2)&&eqv(a2,b1)))
			return 1;
		else 
			return 0;
	}
	return 0;
}

int main()
{
	string a,b;
	cin>>a>>b;
	//cout<<a<<b;
	if(eqv(a,b))
		cout<<"YES\n";
	else
		cout<<"NO\n";
	return 0;
}