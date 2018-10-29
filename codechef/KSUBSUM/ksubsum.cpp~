#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<b;++i)
typedef long long ll;
typedef vector<int> vi;

int main()
{
	//ll start=clock();
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
	{
		int n,k1,k2,k3;
		cin>>n>>k1>>k2>>k3;
		int k=max(k1,k2);
		k=max(k,k3);
		vi a(n),d(n+1);
		rep(i,0,n)
			cin>>a[i];
		d[0]=0;
		rep(i,0,n)
			d[i+1]=d[i]+a[i];
		vector <int> s(k),curr,temp(k);
		rep(i,0,k)
			s[i]=temp[i]=INT_MIN;
		rep(i,0,n)
		{
			for(int j=0;j<=i&&j<k;++j)
				curr.push_back(d[i+1]-d[j]);
			int j=0;
			int l,m;
			l=m=0;
			while(j<k)
			{
				if(l<s.size()&&s[l]>curr[m])
				{
					temp[j]=s[l];
					++j;
					++l;
				}
				else
				{
					temp[j]=curr[m];
					++j;
					++m;
				}
				if(m==curr.size())
				{
					while(j<k)
					{
						temp[j]=s[l];
						++j;
						++l;
					}
					break;
				}
				//cout<<"test";
			}
			s=temp;
			curr.clear();
			j=i;
			int t;
			while(j>=0&&d[j]>d[j+1])
			{
				t=d[j+1];
				d[j+1]=d[j];
				d[j]=t;
				--j;
			}
		}
		//ll mid=clock();
		//float midtime=(mid-start)/(float)CLOCKS_PER_SEC;
		//cout<<"midtime = "<<midtime<<endl;
		printf("%d %d %d\n",s[k1-1],s[k2-1],s[k3-1]);
	}
	//ll stop=clock();
	//float time=(stop-start)/(float)CLOCKS_PER_SEC;
	//cout<<"time = "<<time<<endl;
	return 0;
}
