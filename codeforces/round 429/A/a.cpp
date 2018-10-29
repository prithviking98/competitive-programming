#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int n,k,flag=1;
	string s;
	cin>>n>>k;
	cin>>s;
	sort(s.begin(),s.end());
	for(int i=0;i<s.size();)
	{
		char c;
		int j;
		c=s[i];
		for(j=i;j<s.size()&&s[j]==c;++j);
		if(j-i>k)
			flag=0;
		i=j;
	}
	if(flag)
		cout<<"YES"<<endl;
	else 
		cout<<"NO"<<endl;
	return 0;
}
