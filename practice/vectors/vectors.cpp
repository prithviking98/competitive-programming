#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//bool desc(int i,int j){return i>j;}
typedef vector<int> vi;

int function(vi a,vi b,int c)
{
	cout<<a[0]+b[0]<<"	"<<c;
	return 0;
}

int main()
{
	vector<int> a(2),b(2);
	a[0]=5;
	b[0]=10;
	int c=function(a,b,a[0]);
	/*cout<<"enter elements";
	int i=0,c;
	do
	{
		cin>>c;
		a.push_back(c);
		++i;
	}while(c<10);
	sort(a.begin(),a.end(),desc);
	cout<<"elements in sorted order\n";
	for(int j=0;j<i;++j)
		cout<<a[j]<<"  ";*/
	return 0;
}
