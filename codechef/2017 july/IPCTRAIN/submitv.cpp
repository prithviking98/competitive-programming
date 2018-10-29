#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct trainer
{
	int s,t,d,lecs,index;
	trainer()
	{
		s=t=d=lecs=index=0;
	}
	bool operator < (const trainer& X) const
	{
		if( s<X.s)
			return 1;
		else if(s==X.s)
			return index<X.index;
		else 
			return 0;
	}
	ll calcsadness()
	{
		if(t>=lecs)
			return (t-lecs)*(ll)s;
		else
			return 0;
	}
	void print()
	{
		printf("d%d t%d s%d lecs%d index%d \n",d,t,s,lecs,index);
	}
};

bool comp(trainer& a,trainer& b)
{
	if(a.d<b.d)
		return 1;
	else if(a.d==b.d)
		return a.s<b.s;
	else
		return 0;
}

int main()
{
	int t,n,d;
	cin>>t;
	while(t--)
	{
		cin>>n>>d;
		vector <trainer> a(n);
		int i,avlbl,curr;
		multiset <trainer> max;
		rep(i,0,n)
		{
			cin>>a[i].d>>a[i].t>>a[i].s;
			a[i].index=i;
		}
		sort(a.begin(),a.end(),comp);
		rep(i,0,n)
			a[i].index=i;
		/*cout<<"sorted print \n";
		rep(i,0,n)
			a[i].print();
		cout<<"end\n";*/
		avlbl=0;
		for(i=1;i<=d;++i)
		{
			while(a[avlbl].d<=i&&avlbl<n)
			{
				//printf("day%d avlbl%d\n",i,avlbl);
				//a[avlbl].print();
				max.insert(a[avlbl]);
				avlbl++;
			}
			if(max.size())
			{
				curr=(*max.rbegin()).index;
				a[curr].lecs++;
				//a[curr].print();
				if(a[curr].lecs>=a[curr].t)
					max.erase(max.find(a[curr]));
				//cout<<"size "<<max.size()<<endl;
			}
		}
		ll totalsadness=0;
		rep(i,0,n)
			totalsadness+=a[i].calcsadness();
		cout<<totalsadness<<endl;
	}
	return 0;
}
