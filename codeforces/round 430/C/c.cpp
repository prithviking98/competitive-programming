#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct vertex
{
	int a,beauty,min;
	vi child;
};

int gcd(int a,int b)
{
	ifb
void beautyfinder(vector <vertex> &v,int i,int min,int prevbeauty)
{
	if(!v[i].beauty)
	{
		if(min<=v[i].a)
		{
			v[i].beauty=gcd(v[i].a,prevbeauty);
			v[i].min=min;
		}
		else
		{
			v[i].beauty=gcd(prevbeauty,min);
			v[i].min=v[i].a;
		}
	}
	if(v[i].beauty)
	{
		for(int j=0;i<v[i].child.size();++j)
			beautyfinder(v,v[i].child[j],v[i].min,v[i].beauty);
	}
}
int main()
{
	return 0;
}
