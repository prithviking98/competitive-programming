#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

int main()
{
	ios::sync_with_stdio(0);
	int a;
	cin>>a;
	int shocks=0;
	bool unique=false;
	map <char,int> t;
	map <char, bool> incorrect;
	for(char i='a';i<='z';++i)
	{
		t[i]=0;
		incorrect[i]=false;
	}
	rep(i,0,a)
	{
		char c;
		cin>>c;
		if(c=='!')
		{
			string s;
			cin>>s;
			if(unique)
			{
				shocks++;
				continue;
			}
			vector <bool> seen(26,false);
			rep(k,0,s.size())
			{
				int j=(int)s[k]-97;
				if(!seen[j])
				{
					seen[j]=true;
					if(!incorrect[s[k]])
						t[s[k]]++;
				}
			}
			int max=0;
			for(char j='a';j<='z';++j)
				if(max<=t[j])
					max=t[j];
			int maxcount=0;
			for(char j='a';j<='z';++j)
				if(max==t[j])
					maxcount++;
			if(maxcount==1)
				unique=true;
		}
		else if(c=='.')
		{
			string s;
			cin>>s;
			if(unique)
				continue;
			vector<bool> seen(26,false);
			rep(k,0,s.size())
			{
				int j=(int)s[k]-97;
				if(!seen[j])
				{
					seen[j]=true;
					t[s[k]]--;
					incorrect[s[k]]=true;
				}
			}
			int max=0;
			for(char j='a';j<='z';++j)
				if(max<=t[j])
					max=t[j];
			int maxcount=0;
			for(char j='a';j<='z';++j)
				if(max==t[j])
					maxcount++;
			if(maxcount==1)
				unique=true;
		}
		else if(c=='?')
		{
			char s;
			cin>>s;
			if(i!=a-1)
			{
				if(unique)
				{
					shocks++;
					continue;
				}
				else
				{
					t[s]--;
					incorrect[s]=true;
				}
				int max=0;
				for(char j='a';j<='z';++j)
					if(max<=t[j])
						max=t[j];
				int maxcount=0;
				for(char j='a';j<='z';++j)
					if(max==t[j])
						maxcount++;
				if(maxcount==1)
					unique=true;
			}
		}
	}
	cout<<shocks<<endl;


	return 0;
}
