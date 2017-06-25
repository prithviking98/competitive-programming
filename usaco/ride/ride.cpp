
/*
ID: prithvi4
PROG: ride
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("ride.in");
    ofstream fout("ride.out");
    char cn[10],gn[10];
    int ct[10],gt[10],i,pc=1,pg=1,j,k;
    fin>>cn>>gn;
    for(i=0;cn[i]!='\0';++i)
    {
        ct[i]=cn[i]-64;
    }
    j=i;
    for(i=0;gn[i]!='\0';++i)
    {
        gt[i]=gn[i]-64;
    }
    k=i;
    for(i=0;i<j;++i)
    {
        pc*=ct[i];
    }
    for(i=0;i<k;++i)
    {
        pg*=gt[i];
    }
    if((pc%47)==(pg%47))
        fout<<"GO\n";
    else
        fout<<"STAY\n";
    fin.close();
    fout.close();
    return 0;
}
