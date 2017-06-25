#include <iostream>
#include <vector>

using namespace std;

vector <float> q;
int count=0;

void add(char,float);
void leave(char);
void disp(char, float);

int main()
{
	int op,n,t;
	char loc;
	float id,val;
	cin>>t;
	for(int i=0;i<t;++i)
	{
		count=0;
		q.clear();
		cout<<"Case "<<i+1<<":\n";
		cin>>n;
		for(int j=0;j<n;++j)
		{
			cin>>op;
			cin>>loc;
			if(op==1)
			{
				cin>>id;
				add(loc,id);
			}
			else if(op==2)
			{
				leave(loc);
			}
			else
			{
				cin>>val;
				disp(loc,val);	
			}
		}
	}
	return 0;
}

void add(char loc, float id)
{
	if(loc=='B')
	{
		q.push_back(id);
		++count;
	}
	else
	{
		q.push_back(0);
		for(int i=count-1;i>=0;--i)
			q[i+1]=q[i];
		q[0]=id;
		++count;
	}
}

void leave(char loc)
{
	if(loc=='B')
	{
		q.pop_back();
		--count;
	}
	else
	{
		for(int i=0;i<(count-1);++i)
			q[i]=q[i+1];
		q.pop_back();
		--count;
	}
}

void disp(char loc, float val)
{
	if(loc=='D')
		cout<<q[val-1]<<endl;
	else
	{
		for(int i=0;i<count;++i)
			if(q[i]==val)
				cout<<q[i];
	}
}
