/*
ID: prithvi4
PROG: combo 
LANG: C++                  
*/
#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int checkcombo(vi,vi,int);

int main()
{
	ios::sync_with_stdio(false);
	freopen("combo.out","w",stdout);
	freopen("combo.in","r",stdin);
	vi fcombo(3),mcombo(3),temp(3);
	int n,i,j,k,s,count;
	cin>>n;
	if(n>5)
		count=250;
	else
	{
		count=2*n*n*n;
	}
	for(i=0;i<3;++i)
		cin>>fcombo[i];
	/*for(i=0;i<3;++i)
		cout<<fcombo[i];*/
	for(i=0;i<3;++i)
		cin>>mcombo[i];
	int p;
	p=n>5?5:n;
	for(i=-2;i<p-2;i++)
	{
		temp[0]=fcombo[0]+i;
		if(temp[0]<1)
			temp[0]=n+temp[0];
		else if(temp[0]>n)
			temp[0]=temp[0]-n;

		for(j=-2;j<p-2;++j)
		{
			temp[1]=fcombo[1]+j;
			if(temp[1]<1)
				temp[1]=n+temp[1];
			else if(temp[1]>n)
				temp[1]=temp[1]-n;
			for(k=-2;k<p-2;++k)
			{
				temp[2]=fcombo[2]+k;
				if(temp[2]<1)
					temp[2]=n+temp[2];
				else if(temp[2]>n)
					temp[2]=temp[2]-n;
				if(checkcombo(temp,mcombo,n))
					--count;
			}
		}
	}
	cout<<count<<endl;
	return 0;
}
int checkcombo(vi temp,vi mcombo,int n)
{
	int s,i,k;
	for(s=0;s<3;++s)
	{
		for(i=-2;i<3;++i)
		{
			k=mcombo[s]+i;
			if(k<1)
				k=n+k;
			else if(k>n)
				k=k-n;
			if(temp[s]==k)
				break;
		}
		if(i==3)
			return 0;
	}
	return 1;
}