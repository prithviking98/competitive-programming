#include <bits/stdc++.h>

using namespace std;
#define pushb(x) push_back(x)
#define popb(x) pop_back(x)
#define pushf(x) push_front(x)
#define popf(x) pop_front(x)

int main()
{
	priority_queue <int> a;
	a.push(5);
	a.push(4);
	a.push(9);
	a.push(6);
	//cout<<a[3]<<endl;
	//cout<<a.front()<<endl;
	//cout<<a.back()<<endl;
	cout<<a.top()<<endl;
	a.pop();
	cout<<a.top()<<endl;
	return 0;
}
