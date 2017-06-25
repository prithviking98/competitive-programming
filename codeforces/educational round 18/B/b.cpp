#include <iostream>
#include <vector>

using namespace std;

void remove(vector <int>& c,int& leader, int a)
{
	int index,i;
	if(leader==c.size()-1)
		index=0;
	else
		index=1+leader;
	for(i=1;i<a;++i)
	{
		index++;
		if(index==c.size())
			index=0;
	}
	cout<<c[index]<<" ";
	if(index==c.size()-1)
		leader=0;
	else
		leader=index;
	for(i=index;i<c.size()-1;++i)
		c[i]=c[i+1];
	c.pop_back();
}
int main()
{
	int n,k,i,leader=0;
	vector <int> a(k),c(n);
	for(i=0;i<k;++i)
		cin>>a[i];
	for(i=1;i<=n;++i)
		c[i-1]=i;
	for(i=0;i<k;++i)
		remove(c,leader,a[i]);
	return 0;
}
