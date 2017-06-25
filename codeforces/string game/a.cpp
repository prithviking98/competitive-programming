#include <iostream>
#include <string>
#include <vector>

using namespace std;

int check(string,string);

int main()
{
	int rmax;
	string t,p;
	cin>>t;
	cin>>p;
	vector <long long int> a(t.size());
	for(int i=0;i<t.size();++i)
		cin>>a[i];
	for(int i=0;i<t.size()-1;)
	{
		t[a[i]-1]='0';//random comment
		if(check(t,p))
		{
			++i;
			rmax=i;
		}
		else 
			break;
	}
	cout<<rmax<<endl;
	return 0;
}
int check(string t,string p)
{
	int i=0,k=0;
	for(;i<t.size();++i)
		if(t[i]==p[k])
		{
			++k;
			if(k==p.size())
				return 1;
		}
	return 0;
}
