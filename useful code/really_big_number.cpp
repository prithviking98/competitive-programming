/*function calculates factorial upto 100!
 *
 *
 */


#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)

void fact(int n,vector<int>& f)
{
	int i,j,k,m,x;
	int temp;
	rep(i,1,160)
	{
		f[i]=0;
	}
	f[0]=1;
	temp=0;
	m=1;
	rep(i,1,n+1)
	{
		for(j=0;j<m;++j)
		{
			x=(f[j]*i+temp);
			f[j]=x%10;
			temp=x/10;
		}
		while(temp!=0)
		{
			f[m]=temp%10;
			temp/=10;
			++m;
		}
	}
}
int main ()
{
	int t,n,i,j,m;
	vector <int> f(160);
	//cout<<sizeof(double)<<" "<<sizeof(long double)<<endl;
	cin>>t;
	for(i=0;i<t;++i)
	{
		cin>>n;
		//cout<<n;
		fact(n,f);
		for(j=159;f[j]==0;--j);
		m=j;
		for(j=m;j>=0;--j)
			cout<<f[j];
		cout<<endl;
	}
	return 0;
}
