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
	string a,b,c;
	cin>>a>>b>>c;
	unordered_map<char,int> m;
	rep(i,0,26)
	{
		m['A'+i]=i;
		m['a'+i]=i+26;
//		trace3(i,m['A'+i],m['a'+i]);
	}
	vector <int> ca(52),cb(52),cc(52);

	rep(i,0,a.size())
	{
		ca[m[a[i]]]++;
		cb[m[b[i]]]++;
		cc[m[c[i]]]++;
	}
//	tracev(ca);
//	tracev(cb);
//	tracev(cc);
	int ma,mb,mc;
	ma=mb=mc=0;
	rep(i,0,52)
	{
		if(ma<ca[i])
			ma=ca[i];
		if(mb<cb[i])
			mb=cb[i];
		if(mc<cc[i])
			mc=cc[i];
	}
//	trace3(ma,mb,mc);
	int rema,remb,remc;
	rema=a.size()-ma;
	remb=a.size()-mb;
	remc=a.size()-mc;
//	trace3(rema,remb,remc);
	int ba,bb,bc;
	if(rema>n)
		ba=ma+n;
	else
	{
		if((n-rema)%2==0)
			ba=a.size();
		else
			ba=a.size()-1;
	}
	if(remb>n)
		bb=mb+n;
	else
	{
		if((n-remb)%2==0)
			bb=a.size();
		else
			bb=a.size()-1;
	}	
	if(remc>n)
		bc=mc+n;
	else
	{
		if((n-remc)%2==0)
			bc=a.size();
		else
			bc=a.size()-1;
	}
//	trace3(ba,bb,bc);

	if(ba>bb&&ba>bc)
		cout<<"Kuro"<<endl;
	else if(bb>ba&&bb>bc)
		cout<<"Shiro"<<endl;
	else if(bc>ba&&bc>bb)
		cout<<"Katie"<<endl;
	else
		cout<<"Draw"<<endl;

	return 0;
}
