#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front

typedef long long ll;
typedef vector<int> vi;

int merge(vector<string> &s,int beg, int mid, int end, unordered_map<string,int> &e)
{
	vector<string> temp(end-beg+1);
	int i=beg,j=mid+1,k=0,inv=0,flag=1,lc=0,rc=0;
	//cout<<"beg mid end "<<beg<<mid<<end<<endl;;
	//cout<<"test"<<s[i]<<s[j]<<endl;
	//cout<<e[s[i]]<<e[s[j]]<<endl;
	while(k<temp.size())
	{
		if(e[s[i]]<e[s[j]])
		{
			if(flag==0)
			{
				lc=0;
				flag=1;
			}
			temp[k]=s[i];
	//		cout<<"test";
			++k;++i;++lc;
		}
		else
		{
			if(flag==1)
			{
				inv+=(lc*rc);
	//		cout<<"test"<<inv;
				flag=0;
				rc=0;
			}
			temp[k]=s[j];
			++k;++j;++rc;
		}
		if(i==mid+1)
		{
			inv+=(lc*rc);
	//		cout<<inv;
			while(k<temp.size())
			{
				temp[k]=s[j];
				++k;++j;
			}
		}
		else if(j==end+1)
		{
			lc=0;
			while(k<temp.size())
			{
				temp[k]=s[i];
				++k;++i;
				++lc;
			}
			inv+=(rc*lc);
		}
	}
	rep(i,0,temp.size())
		s[beg+i]=temp[i];
	return inv;
}

int mergesort(vector<string> &s, int beg, int end, unordered_map<string,int> &e)
{
	if(beg==end)
		return 0;
	int mid=(beg+end)/2;
	int linv,rinv;
	linv=mergesort(s,beg,mid,e);
	rinv=mergesort(s,mid+1,end,e);
	//cout<<"linv rinv "<<linv<<" "<<rinv<<endl;
	int minv=merge(s,beg,mid,end,e);
	//cout<<"minv "<<minv<<endl;
	return linv+rinv+minv;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vector <string> sent(n), sorted(n);
		string s;
		rep(i,0,n)
		{
			cin>>s;
			sent[i]=s;
		}
		rep(i,0,n)
		{
			cin>>s;
			sorted[i]=s;
		}
		unordered_map <string,int> e;
		rep(i,0,n)
		{
			e[sorted[i]]=i;
		}
		int inv=mergesort(sent,0,n-1,e);
		cout<<inv<<endl;
	}

	return 0;
}
