#include <bits/stdc++.h>
#define il inline
#define Max 500005
#define N 10005
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
int head[Max],vst[Max],d[Max],cur[Max],q[Max],tot=1,cnt,n1,n2,n3,m,s,t;
il void add2(int u,int v,int w)
{
	e[++tot].t=v;
	e[tot].nt=head[u];
	e[tot].w=w;
	head[u]=tot;
}
il void add(int u,int v,int w)
{
	add2(u,v,w),add2(v,u,0);
}
il bool bfs()
{
	int l=1,r=1;
	memset(d,0,sizeof(d));
	d[s]=1;
	q[l]=s;
	while(l<=r)
	{
		int u=q[l++];
		for(int i=head[u];i;i=e[i].nt)
		{
			int v=e[i].t,w=e[i].w;
			if(!d[v]&&w)
			{
				d[v]=d[u]+1;
				q[++r]=v;
			}
		}
	}
	return d[t];
}
il int dfs(int u,int fw)
{
	if(u==t) return fw;
	int res=0;
	for(int& i=cur[u];i;i=e[i].nt)
	{
		int v=e[i].t,w=e[i].w;
		if(d[v]==d[u]+1&&w)
		{
			if(res=dfs(v,min(fw,w)))
			{
				e[i].w-=res;
				e[i^1].w+=res;
				return res;
			}
		}
	}
	return 0;
}
il int dinic()
{
	int flw=0;
	while(bfs())
	{
		int nfw;
		for(int i=1;i<=t;i++) cur[i]=head[i];
		while(nfw=dfs(s,inf))
		{
			flw+=nfw;
		}
	}
	return flw;
}
int main()
{
	freopen("p1231.in","r",stdin);
	n1=read(),n2=read(),n3=read();
	s=4*N+1,t=4*N+2;
	for(int i=1;i<=n1;i++)
	{
		add(i,i+N,1);
	}
	for(int i=1;i<=n2;i++)
	{
		add(s,i+2*N,1);
	}
	for(int i=1;i<=n3;i++)
	{
		add(i+3*N,t,1);
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add(v+2*N,u,1);
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add(u+N,v+3*N,1);
	}
	cout<<dinic();
}
