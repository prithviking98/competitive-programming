#include <bits/stdc++.h>
using namespace std;
int main()
{
	int start=clock();
	ios::sync_with_stdio(0);
	int t,n,i,j,temp;
	long long  n2,n5,tzero;
	cin>>t;
	for(i=0;i<t;++i)
	{
		cin>>n;
		//cout<<n<<endl;
		n2=0;
		n5=0;
		/*for(j=2;j<=n;j+=2)
		{
			temp=j;
			while(temp%2==0)
			{
				temp/=2;
				++n2;
			}
			temp=j;
			while(temp%5==0)
			{
				temp/=5;
				++n5;
			}
		}*/
		temp=n;
		for(j=1;temp/pow(2,j)>=1;++j)
			n2+=floor(temp/pow(2,j));
		for(j=1;temp/pow(5,j)>=1;++j)
			n5+=floor(temp/pow(5,j));
		tzero=(n2<=n5)?n2:n5;
		//tzero=n5;
		cout<<tzero<<"\n";
	}	
	int stop=clock();
	//cout<<"time="<<(stop-start)/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
