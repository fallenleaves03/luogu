#include <bits/stdc++.h>
#define il inline
#define Max 500005
#define rg register
using namespace std;
il int read()
{
	char c=getchar();
	int x=0,f=1;
	while(c>'9'||c<'0')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
struct Mo
{
	int l,r,id,ans,b;
}e[Max];
int n,s,m,c[1000005],a[Max],cnt;
il bool cmp(Mo x,Mo y)
{
	if(x.b==y.b)
	{
		if(x.b&1)
		{
			return x.r<y.r;
		}
		return x.r>y.r;
	}
	return x.b<y.b;
}
il void ins(int x)
{
	cnt+=(++c[a[x]]==1);
}
il void del(int x)
{
	cnt-=(--c[a[x]]==0);
}
il bool cmp2(Mo a,Mo b)
{
	return a.id<b.id;
}
int main()
{
	n=read();s=sqrt(n);
	if(n>460000) s=817;
	for(rg int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	m=read();
	for(rg int i=1;i<=m;i++)
	{
		e[i].l=read(),e[i].r=read();
		e[i].b=e[i].l/s;
		e[i].id=i;
	}
	sort(e+1,e+1+m,cmp);
	rg int l=0,r=0;
	for(rg int i=1;i<=m;i++)
	{
		while(r<e[i].r) ins(++r);
		while(r>e[i].r) del(r--);
		while(l<e[i].l) del(l++);
		while(l>e[i].l) ins(--l);
		e[i].ans=cnt;
	}
	sort(e+1,e+1+m,cmp2);
	for(int i=1;i<=m;i++)
		printf("%d\n",e[i].ans);
}
