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

struct node
{
	char c;
	int index;
	vector<node> next;
};

int prefix(string a,string b)
{
	int i;
	for( i=0;i<b.size()&&i<a.size();)
	{
		if(a[i]==b[i])
			++i;
		else
			break;
	}
	return i;
}

int insert(vector<node> &a,node n)
{
	a.PUB(n);
	int i=a.size()-2;
	while(i>=0)
	{
		if(a[i].c>a[i+1].c)
		{
			node t;
			t=a[i+1];
			a[i+1]=a[i];
			a[i]=t;
			i--;
		}
		else 
			break;
	}
	return i+1;
}

void addString(node &t,string s,int index)
{
	int l=0;
	node *trie=&t;
//	cout<<endl;
//	trace1(s);
	while(l<=s.size())
	{
//		trace1(l);
		if(l<s.size())
		{
			int flag=0;
			int i;
			for(i=0;i<trie->next.size();++i)
				if(trie->next[i].c==s[l])
				{
					flag=1;
					break;
				}
			if(!flag)
			{
				node n;
				n.c=s[l];
				n.index=index;
				i=insert(trie->next,n);
			}
//			trace1(trie->c);
//			rep(p,0,trie->next.size())
//				cout<<trie->next[p].c<<" ";
//			cout<<endl;
			l++;
			trie=&trie->next[i];
		}
		else
		{ 
			if(trie->next.size()==0||trie->next[0].c!=0)
			{
				node n;
				n.c='0';
				n.index=index;
				insert(trie->next,n);
			}
			l++;
		}
	}
}

string find(node &t,string &s,int r,int l)
{
	node trie;
	if(t.index>r)
	{
		string k;
		return k;
	}
	else if(l<s.size()&&(t.c!='0'||!l))
	{
		string m;
		if(l>0)
		{	
			m="a";
			m[0]=t.c; //current node char
		}
		int flag=0,i;
		for(i=0;i<t.next.size();++i)
			if(t.next[i].c==s[l]&&t.next[i].index<=r)
			{
				flag=1;
				break;
			}
		if(flag)
		{
			trie=t.next[i];
			string k=find(trie,s,r,l+1);
			if(k.size()>0)
			{
				if(k[0]!='0')
					return m+k;
				else 
					return m;
			}
			else
			{
				rep(j,0,t.next.size()) //searching current node for smallest
				{
					if(j==i)
						continue;
					if(t.next[j].index<=r)
						k=find(t.next[j],s,r,l+1);
					if(k.size()>0)
					{
						return k[0]!='0'? m+k : m;
					}
				}
				return k;
			}
		}
		else
		{
			string k;
			rep(j,0,t.next.size()) //searching current node for smallest
			{
				if(t.next[j].index<=r)
					k=find(t.next[j],s,r,s.size()); //setting l as s.size() since no match
				if(k.size()>0)
					return k[0]!='0'? m+k : m;
			}
		}
	}
	else if(l==s.size()&&t.c!='0')
	{
		string m="a";
		m[0]=t.c;
		string k;
		rep(j,0,t.next.size()) //searching current node for smallest
		{
			if(t.next[j].index<=r)
				k=find(t.next[j],s,r,l); //not increasing l
//			trace1(k[0]);
			if(k.size()>0)
			{
				if(k[0]=='0')
					return m;
				else
					return m+k;
			}
		}
	}
	else if(l<=s.size()&&t.c=='0')
	{
		string k;
		if (t.index<=r)
		{
			k="a";
			k[0]='0';
			return k;
		}
		else
			return k;
	}
}

string func()
{
	string b;
	return b;
}

void dfs(node t,int i)
{
	cout<<"test"<<endl;
	if(t.c==0&&i)
	{
		cout<<endl;
		return;
	}
	cout<<t.c;
	trace1(t.next.size());
	rep(i,0,t.next.size())
		dfs(t.next[i],1);
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin>>n;
	vector<string> s(n);
	node trie;
	trie.c='0';
	trie.index=0;
	rep(i,0,n)
	{
		cin>>s[i];
		addString(trie,s[i],i+1);
	}
	string a,b;
	a="apple";
	b=func();
	a=a+b;
//	trace1(a);
//	dfs(trie,0);
	int q;
	cin>>q;
	rep(i,0,q)
	{
		int r;
		string p;
		cin>>r>>p;
		string m=find(trie,p,r,0);
		cout<<m<<endl;
	}
	return 0;
}
