#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct sub
{
	int l,start;
};
int main()
{
	string s;
	cin>>s;
	list <sub> l;
	char c='a';
	sub t;
	t.l=0; t.start=-1;
	rep(i,0,s.size())
	{
		if(s[i]==c)
		{
			t.l++;
			if(t.start==-1)
				t.start=0;
		}
		else
		{
			l.push_back(t);
			t.start=i;
			t.l=1;
			if(c=='a')
				c='b';
			else
				c='a';
		}
	}
	if(c=='b')
	{
		l.push_back(t);
		t.start=s.size();
		t.l=0;
		l.push_back(t);
	}
	else
		l.push_back(t);
	//cout<<"size"<<l.size()<<endl;
	auto first=l.begin();
	list<sub>::iterator last=--l.end();
	while(l.size()>3)
	{
		list<sub>::iterator i=++l.begin();
		list<sub>::iterator m=i;
		for(;i!=last;++i)
		{
			if((*m).l>(*i).l)
				m=i;
		}
		if(m==++l.begin())
		{
			//cout<<(*m).start<<endl;
			m=l.erase(m);
			(*first).l+=(*m).l;
			l.erase(m);
		}
		else if(m==--(--(l.end())))
		{
			//cout<<(*m).start<<endl;
			m=l.erase(m);
			--m;
			(*m).l+=(*last).l;
			l.pop_back();
		}
		else
		{
			//cout<<(*m).start<<endl;
			l.erase(m);
		}
	}
	int size=0;
	rep(i,0,3)
	{
		size=size+(*first).l;
		++first;
	}
	cout<<size;

	return 0;
}
