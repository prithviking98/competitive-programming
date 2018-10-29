#include <bits/stdc++.h>

using namespace std;

int main()
{
	unordered_map <int, string> m;
	m[3]="hello";
	m[1]="howdy";
	m[2]="yolo";
	for(auto x=m.begin();x!=m.end();++x)
		cout<<(*x).first<<"\t"<<(*x).second<<endl;
	if(m.find(3)!=m.end())
		cout<<"test"<<endl;
	return 0;
}
