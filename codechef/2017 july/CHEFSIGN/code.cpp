#include <bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	int t;
	string s;
	cin>>t;
	for(int i=0;i<t;++i)
	{
		cin>>s;
		int c,min,max;
		c=min=max=1;
		for(int j=0;j<s.size();++j)
		{
			if(s[j]=='<')
			{
				int l,length,change;
				for(l=j,length=0;l<s.size()&&(s[l]=='<'||s[l]=='=');++l)
				{
					if(s[l]=='<')
						++length;
				}
				change=l-1;
				if(length<=max-c)
					c=max;
				else
					c+=length;
				//cout<<"c= "<<c<<endl;
				j=change;
			}
			else if(s[j]=='>')
			{
				int l,length,change;
				for(l=j,length=0;l<s.size()&&(s[l]=='>'||s[l]=='=');++l)
				{
					if(s[l]=='>')
						++length;
				}	
				change=l-1;
				if(length<=c-min)
					c=min;
				else
					c-=length;
				//cout<<"c ="<<c<<endl;
				j=change;
			}
			if(c>max)
				max=c;
			if(c<min)
				min=c;
		}
		cout<<max-min+1<<"\n";
	}
	return 0;
}
			
