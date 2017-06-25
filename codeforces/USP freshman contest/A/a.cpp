#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int isPrime(unsigned long long n)
{
	for(unsigned long long i=2;i<=(n/2);++i)
		if((n%i)==0)
			return 0;
	return 1;
}
class set
{
public:
	unsigned long long a,b;
	int CheckRelation();
};

int set::CheckRelation()
{
	if(a==b)
		return 1;
	else if(isPrime(a)&&isPrime(b))
		return 0;
	else
	{
		for(unsigned long long j=2;(j<=a)&&(j<=b);++j)
			if(isPrime(j))
				if((a%j==0)&&(b%j==0))
					return 1;
	}
	return 0;
}

int main()
{
	int t;
	cin>>t;
	vector <set> pair(t);
	for(int i=0;i<t;++i)
	{
		cin>>pair[i].a>>pair[i].b;
		if(pair[i].CheckRelation())
			cout<<"Sim"<<endl;
		else
			cout<<"Nao"<<endl;
	}
	return 0;
}
