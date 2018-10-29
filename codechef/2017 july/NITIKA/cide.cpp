#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s,a,b,c;
	int t,i,j,space;
	vector <int> l(2);
	cin>>t;
	cin.ignore();
	for(i=0;i<t;++i)
	{
		getline(cin,s);
		//cout<<s<<endl;
		space=0;
		for(j=s.find(" ",0);j!=string::npos;j=s.find(" ",j))
		{
			l[space]=j;
			++space;
			++j;
		}
		//cout<<space<<endl;
		if(space==0)
		{
			s[0]=toupper(s[0]);
			for(j=1;j<s.size();++j)
				s[j]=tolower(s[j]);
			cout<<s<<endl;
		}
		else if(space==1)
		{
			a=toupper(s[0]);
			a+=". ";
			b=s.substr(l[0]+1,s.size()-l[0]-1);
			//cout<<a<<" test "<<b<<endl;
			for(j=1;j<b.size();++j)
				b[j]=tolower(b[j]);
			b[0]=toupper(b[0]);
			cout<<a+b<<endl;
		}
		else if(space==2)
		{
			a=toupper(s[0]);
			b=toupper(s[l[0]+1]);
			a+=". ";
			b+=". ";
			c=s.substr(l[1]+1,s.size()-l[1]-1);
			for(j=1;j<c.size();++j)
				c[j]=tolower(c[j]);
			c[0]=toupper(c[0]);
			cout<<a+b+c<<endl;
		}
	}
	//cout<<i;
	return 0;
}
			
