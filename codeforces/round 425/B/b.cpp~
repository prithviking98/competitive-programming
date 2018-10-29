
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	string good,s;
	cin>>good>>s;
	int n;
	cin>>n;
	while(n--)
	{
		string t;
		cin>>t;
		int flag=1;
		int i,j;
		i=j=0;
		while(i<s.size()&&j<t.size())
		{
			if(t[j]==s[i])
			{
				++j;
				++i;
				//cout<<i<<"	"<<j<<endl;
			}	
			else if(s[i]=='?')
			{
				if(good.find(t[j],0)==string::npos)
				{
					flag=0;
					break;
				}
				else
				{
					++i;
					++j;
					//cout<<i<<"	"<<j<<endl;
				}
			}
			else if(s[i]=='*')
			{
				while(j<t.size()&&good.find(t[j],0)==string::npos)
					++j;
				++i;
				//cout<<i<<"	"<<j<<endl;
				/*if(i==s.size()&&j<t.size())
				{
					flag=0;
					break;
				}
				else if(i<s.size()&&j==t.size())
				{
					flag=0;
					break;
				}*/
			}
			else if(t[j]!=s[i])
			{
				flag=0;
				break;
			}
		}
		if((i<s.size()&&j==t.size())||(i==s.size()&&j<t.size()))
			flag=0;
		if(j==t.size()&&i==s.size()-1&&s[i]=='*')
			flag=1;
		if(flag)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	return 0;
}
