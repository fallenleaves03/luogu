#include <bits/stdc++.h>
#define il inline
#define Max 5000005
#define inf 0x3f3f3f3f
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
struct node
{
	int t,nt,w;
}e[Max<<1];
int n,m,vst[Max],head[Max],tot,cnt;
il void add2(int u,int v,int w)
{
	e[++tot].t=v;
	e[tot].w=w;
	e[tot].nt=head[u];
	head[u]=tot;
}
il void add(int u,int v,int w)
{
	add(u,v,w),add(v,u,0);
}
int main()
{
	n=read(),m=read();
	
}
