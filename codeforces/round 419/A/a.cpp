#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int checkpal(int hour,int min)
{
	int rev;
	rev=(min%10)*10+min/10;
	if(rev==hour)
		return 1;
	else 
		return 0;
}
int main()
{
	string time;
	cin>>time;
	int hour,min;
	hour=(time[0]-48)*10+time[1]-48;
	min=(time[3]-48)*10+time[4]-48;
	int count=0;
	while(!checkpal(hour,min))
	{
		while(!checkpal(hour,min))
		{
			++count;
			++min;
			if(min==60)
			{
				min=0;
				break;
			}
		}
		if(!min)
		{
			++hour;
			if(hour==24)
				hour=0;
		}
	}
	cout<<count<<endl;
	return 0;
}
