#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n,k,s,moves,avg;
	vector <int> a;
	cin>>n;
	while(n!=-1)
	{
		s=0;
		moves=0;
		for(int i=0;i<n;++i)
		{
			cin>>k;
			s+=k;
			a.push_back(k);
		}
		if(s%n!=0)
			cout<<-1<<endl;
		else
		{
			avg=s/n;
			//cout<<s<<"	"<<avg<<endl;
			for(int i=0;i<n;++i)
			{
				if(a[i]>avg)
					moves+=(a[i]-avg);
			}
			cout<<moves<<endl;
		}
		cin>>n;
		a.clear();
	}
	return 0;
}
