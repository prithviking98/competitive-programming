#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)

int main()
{
	ios::sync_with_stdio(0);
	vector <int> a;
	int n,i;
	n=3;
	while(cin>>n)
	{
		//cout<<n<<endl;
		while(n!=0)
		{
			if(n==-1)
			{
				cout<<a[(a.size()-1)/2]<<"\n";
			}
			else
				a.push_back(n);
			cin>>n;
			//cout<<n<<endl;
		}
		cout<<endl;
		a.clear();
	}
	return 0;
}
