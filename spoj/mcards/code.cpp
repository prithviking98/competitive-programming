#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

struct card
{
	int col,num;
};

int checknest(vector <card> a,int i)
{
	int l,r;
	l=r=1;
	if(a[i].col==1)
	{
		int j=i-1;
		while(j>=0)
		{
			if(a[j].col!=a[i].col)
			{
				l=0;
				break;
			}
			--j;
		}	
		j=i+1;
		while(j<a.size())
		{
			if(a[j].col!=a[i].col)
			{
				r=0;
				break;
			}
			++j;
		}
	}
	else
	{
		int j=i-1;
		while(j>=0)
		{
			if(a[j].col>a[i].col)
			{
				l=0;
				break;
			}
			--j;
		}
		j=i+1;
		while(j<a.size())
		{
			if(a[j].col>a[i].col)
			{
				r=0;
				break;
			}
			++j;
		}
	}
	return !(l||r);
}

int findlis(const vector <card> a,const int tot, const int col,vector <card> &d,int num)
{
	if(num==1)
		return 0;
	int inbetween=0,flag=0;
	rep(i,0,tot)
	{
		if(a[i].col!=col)
			continue;
		int f=0,b;
		for(b=d.size()-1;b>=1;b/=2)
			while(f+b<d.size()&&d[f+b].num<a[i].num)
				f+=b;
		if(f==d.size()-1)
		{
			d.push_back(a[i]);
			if(checknest(a,i))
			{
				inbetween++;
				flag=1;
			}
			else
				flag=0;
		}
		else
		{
			if(d[f+1].num>a[i].num)
				d[f+1]=a[i];
			if(f+1==d.size()-1)
			{
				if(checknest(a,i)&&flag)
					inbetween;
				else if(checknest(a,i)&&!flag)
					++inbetween;
				else if(!checknest(a,i)&&flag)
					--inbetween;
			}
		}
	}
	//cout<<"inbetween"<<inbetween<<endl;
	return d.size()-1-inbetween;
}

int main()
{
	int col,num;
	cin>>col>>num;
	vector <card> a(col*num),ar(col*num);
	vector <card> d(1);
	d[0].col=-1;
	d[0].num=-1;
	int tot=col*num;
	rep(i,0,tot)
		cin>>a[i].col>>a[i].num;
	rep(i,0,tot)
		ar[tot-1-i]=a[i];
	vi c(col),cr(col);
	rep(i,0,col)
	{
		c[i]=findlis(a,tot,i+1,d,num);
		cout<<num-c[i]<<endl;
		d.resize(1);
	}
	rep(i,0,col)
	{
		cr[i]=findlis(ar,tot,i+1,d,num);
		cout<<num-cr[i]<<endl;
		d.resize(1);
	}	
	int lmoves,lmovesr;
	lmoves=lmovesr=col*num;
	rep(i,0,col)
	{
		lmoves-=c[i];
		lmovesr-=cr[i];
	}
	if(lmoves<lmovesr)
		cout<<lmoves<<endl;
	else
		cout<<lmovesr<<endl;
	return 0;
}
