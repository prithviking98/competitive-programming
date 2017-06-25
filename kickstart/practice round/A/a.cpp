#include <iostream>
#include <string>
using namespace std;

class citizen
{
public:
	string name;
	int no_alpha;
	citizen()
	{no_alpha=1;}
	void count();
};
void citizen::count()
{
	for(int i=1;i<name.length();++i)
		if((name[i]!=' ')&&(name.rfind(name[i],i-1)==string::npos))
			no_alpha++;
}

int max(citizen*,int);

int main()
{
	int i,j,T,N,index;
	char c;
	citizen person[100];
	cin>>T;
	//cout<<T<<endl;
	for(i=0;i<T;++i) 
	{
		cin>>N;
		//cout<<N<<endl;
		cin.ignore();
		for(j=0;j<N;++j)
		{
			getline(cin,person[j].name);
			//cout<<person[j].name<<endl;
			person[j].count();
			//cout<<person[i].no_alpha<<endl;
		}
		index=max(person,N);
		cout<<"Case #"<<i+1<<": "<<person[index].name<<endl;
	}
	return 0;
}


int max(citizen* person,int n)
{
	int a=person[0].no_alpha,index=0;
	for(int i=1;i<n;++i)
	{
		if(person[i].no_alpha>a)
		{
			a=person[i].no_alpha;
			index=i;
		}
		else if(person[i].no_alpha==a)
		{
			int flag=0;
			for(int j=0;(j<person[i].name.length())&&(j<person[index].name.length());++j)
			{
				if(person[i].name[j]<person[index].name[j])
				{
					a=person[i].no_alpha;
					index=i;
					flag=1;
				}
			}
			if(flag==0)
			{
				if(person[i].name.length()<person[index].name.length())
				{
					a=person[i].no_alpha;
					index=i;
				}
			}
		}
	}
	return index;
}

