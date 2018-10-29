
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	string lay1,lay2,s,s2;
	char c;
	int i,j,upper=0;
	cin>>lay1>>lay2>>s;
	rep(i,0,s.size())
	{
		if(!isalpha(s[i]))
			s2+=s[i];
		else
		{
			c=s[i];
			if(isupper(c))
			{
				upper=1;
				c=tolower(c);
			}
			for(j=0;j<lay1.size();++j)
				if(lay1[j]==c)
					break;
			if(upper)
				s2+=toupper(lay2[j]);
			else
				s2+=lay2[j];
			upper=0;
		}
	}
	cout<<s2<<endl;
	return 0;
}
