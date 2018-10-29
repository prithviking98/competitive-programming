#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PB push_back
typedef long long ll;
typedef vector<int> vi;

int hasnameonce(string s,string a)
{
	int i=s.find(a,0);
	if(i!=string::npos)
	{
		if(s.find(a,i+1)==string::npos)
			return 1;
		else 
			return 0;
	}
	else
		return 0;
}
int main()
{
	string s;
	cin>>s;
	vector <string> a(5);
	a[0]="Danil";
	a[1]="Olya";
	a[2]="Slava";
	a[3]="Ann";
	a[4]="Nikita";
	int flag=0;
	rep(i,0,5)
	{
		int temp=hasnameonce(s,a[i]);
		if(flag==1&&temp==1)
		{
			flag=0;
			break;
		}
		else if(temp)
			flag=temp;
		else
			continue;
	}
	if(flag)
		cout<<"YES";
	else
		cout<<"NO";
	return 0;
}
