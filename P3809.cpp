#include <bits/stdc++.h>
#define il inline
#define Max 1000005
using namespace std;
int n,a[Max],rk[Max],tp[Max],sa[Max],c[Max],m;
char s[Max];
il void rsort()
{
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++) c[rk[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i>=1;i--) sa[c[rk[tp[i]]]--]=tp[i];
}
il void getsa()
{
	for(int i=1;i<=n;i++) rk[i]=a[i],tp[i]=i;
	rsort();
	//Debug();
	for(int k=1,p;p<n;k<<=1,m=p)
	{
		p=0;
		for(int i=n-k+1;i<=n;i++) tp[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) tp[++p]=sa[i]-k;
		rsort();
		swap(rk,tp);
		rk[sa[1]]=p=1;
		for(int i=2;i<=n;i++)
			rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;
			//Debug();
	}
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);m=127;
	for(int i=1;i<=n;i++) a[i]=s[i];
	getsa();
	for(int i=1;i<=n;i++)
		printf("%d ",sa[i]);
}
