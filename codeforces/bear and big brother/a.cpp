#include <iostream>

using namespace std;

int main()
{
	float a,b,frac=1.5;
	cin>>a>>b;
	int year=1;
	for(;frac<=(b/a);++year)
		frac*=frac;
	cout<<year;
	return 0;
}
