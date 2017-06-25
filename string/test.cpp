#include <iostream>
#include <string>

using namespace std;
void func(string);
int main()
{
	string s,v;
	s="yo yo yo hello";
	func(s);
	cout<<s;
	return 0;
}
void func(string s)
{
	s.erase(2,3);
}
