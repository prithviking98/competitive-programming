#include <bits/stdc++.h>

using namespace std;

int main()
{
	multiset <int> s;
	s.insert(5);
	s.insert(2);
	s.insert(7);
	s.insert(10);
	s.insert(5);
	auto x=s.begin();
	for(;x!=s.end();++x)
		cout<<*x<<endl;
	if(s.find(3)!=s.end())
		cout<<*s.find(5)<<"test"<<endl;
	//cout<<*s.upper_bound(5)<<endl;
	cout<<s.size()<<endl;
	s.clear();
	cout<<s.size()<<endl;
	return 0;
}
