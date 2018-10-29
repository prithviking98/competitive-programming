#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	int a[]={1,2,3,4,6,12};
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		vector < pair<int,int> > combo;
		for(int k=0;k<6;++k)
		{
			int r,c;
			r=a[k];
			c=12/a[k];
			rep(j,0,c)
			{
				int i;
				for(i=0;i<r;++i)
					if(s[i*c+j]!='X')
						break;
				if(i==r)
				{
					combo.push_back(make_pair(r,c));
					break;
				}
			}
		}
		int p=combo.size();
		cout<<p<<" ";
		rep(i,0,p)
			cout<<combo[i].first<<"x"<<combo[i].second<<" ";
		cout<<endl;
	}
				
	return 0;
}
