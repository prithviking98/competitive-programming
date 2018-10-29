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

typedef long long ll;
typedef vector<int> vi;

int main()
{
	ios::sync_with_stdio(0);
	string a,b;
	cin>>a>>b;
	priority_queue <char> p;
	int n=a.size();
	rep(i,0,n)
		p.push(a[i]);
	vector <char> t,at;
	if(n==b.size())
	{
		int k=0;
		while(k<b.size())
		{
			if(p.top()==b[k])
			{
				at.PUB(p.top());
				p.pop();
				k++;
			}
			else if(p.top()<b[k])
			{
				while(p.size())
				{
					at.PUB(p.top());
					++k;
					p.pop();
				}
				break;
			}
			else
			{
				while(p.top()>b[k])
				{
					t.PUB(p.top());
					p.pop();
				}
				if(p.top()==b[k])
				{
					at.PUB(p.top());
					p.pop();
					k++;
					while(t.size())		
					{
						p.push(t[t.size()-1]);
						t.POB();
					}
				}
				else
				{
					at.PUB(p.top());
					p.pop();
					while(t.size())
					{
						p.push(t[t.size()-1]);
						t.POB();
					}
					while(p.size())
					{
						at.PUB(p.top());
						++k;
						p.pop();
					}
					break;
				}
			}
		}
		rep(i,0,n)
			cout<<at[i];
		cout<<endl;
	}
	else
	{
		sort(a.rbegin(),a.rend());
		cout<<a<<endl;
	}
	return 0;
}
