#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
#define PUB push_back
#define PUF push_front
#define POB pop_back
#define POF pop_front
#define trace1(x) cout<<#x<<"="<<x<<endl
#define trace2(x,y) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define trace3(x,y,z) cout<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define trace4(w,x,y,z) cout<<#w<<"="<<w<<" "<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define tracev(a) rep(II,0,a.size()) cout<<#a<<"["<<II<<"]="<<a[II]<<" "; cout<<endl;
#define tracem(a)\
	{\
	rep(II,0,a.size()){\
		rep(JJ,0,a[II].size())\
			cout<<#a<<"["<<II<<"]["<<JJ<<"]="<<a[II][JJ]<<" ";\
		cout<<endl;\
		}\
	}

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef pair<int,int> pii;


int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vi a(n);
	vvi index(1e4+1),next(1e4+1);
	rep(i,1,1e4+1)
		index[i].PUB(-1);
	rep(i,0,n)
	{
		cin>>a[i];
		if(i==0||a[i-1]!=a[i])
			index[a[i]].PUB(i);
	}
	
	rep(i,1,1e4+1)
		index[i].PUB(n);
	rep(i,1,1e4+1)
		next[i].PUB(index[i][1]);
	int i=0,j;
	while(i<n)
	{
		j=i;
		while(j<n&&a[j]==a[i])
			++j;
		next[a[i]].PUB(j);
		i=j;
	}
	int count=1;
	i=1;
	while(index[i].size()<=2)
		++i;
	list <int> li;
	rep(t,0,index[i].size())
		li.PUB(index[i][t]);
	for(;i<1e4;)
	{
		j=i+1;
//		trace2(i,j);
		while(j<1e4+1&&index[j].size()<=2)
			j++;
		if(j==1e4+1)
			break;
		int l=1;
		auto k=++li.begin();
		auto prev=li.begin();
		while(l<index[j].size()-1&&k!=li.end())
		{
			if(index[j][l]<*k&&index[j][l]>*(prev))
			{
//				trace3((*k),(*prev),index[j][l]);
				li.emplace(k,index[j][l]);
				if(*k==next[j][l])
				{
					k=li.erase(k);
					prev=--k;
					++k;
				}
				else 
				{
					prev=k;
					k++;
				}
				l++;
				count++;
			}
			else if(index[j][l]<*(prev))
			{
//				trace3((*k),(*prev),index[j][l]);
				li.emplace(prev,index[j][l]);
				if(*prev==next[j][l])
				{
					prev=li.erase(prev);
					prev--;
				}
				l++;
			}
			else if(index[j][l]>(*k))
			{
				prev=k;
				k++;
			}
//			for(auto t=li.begin();t!=li.end();++t)
//				cout<<*t<<" ";
//			cout<<endl;
		}
		i=j;	
	}
	cout<<count<<endl;
	return 0;
}
