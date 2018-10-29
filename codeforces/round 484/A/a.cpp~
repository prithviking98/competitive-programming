#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;

int main()
{
	ios::sync_with_stdio(0);
	string s;
	int n;
	cin>>n; 
	cin>>s;
	string s1(n,'0'),s2(n,'0');
	int flag,count=0;
	if(s[0]=='0')
		flag=0;
	else
	{
		flag=1;
	}
	int i,tf;
	for( i=1;i<n;++i)
	{
		if(flag==1)
		{
			if(s[i]=='1')
				break;
			else
				flag=0;
		}
		else
		{
			if(s[i]=='1')
			{
				tf=0;
				flag=1;
				count++;
			}
			else
			{
				if(tf||i==n-1||i==1)
					break;
				tf=1;
			}
		}
	}
	if(i==n)
	{
		if(n==1&&s[0]=='1')
			cout<<"Yes"<<endl;
		else if(n==1&&s[0]=='0')
			cout<<"No"<<endl;
		else
			cout<<"Yes"<<endl;
	}
	else
		cout<<"No"<<endl;
	return 0;
}
