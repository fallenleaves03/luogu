#include <bits/stdc++.h>
#define il inline
//#define gc() getchar()
#define Max 5000005
#define inf 0x3f3f3f3f
#define gc() (ss==tt&&(tt=(ss=In)+fread(In,1,23333,stdin),ss==tt)?EOF:*ss++)
using namespace std;
char In[23333],*ss=In,*tt=In;
il int read()
{
	char c=gc();
	int x=0,f=1;
	while(c>'9'||c<'0')
	{
		if(c=='-') f=-1;
		c=gc();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=gc();
	}
	return x*f;
}
struct node
{
	int t,nt,w;
}e[Max<<1];
int n,s,t,n1,n2,n3,cur[Max],head[Max],vst[Max],tot=1,m,d[Max],q[Max];
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
	memset(d,0,sizeof(d));
	int l=1,r=0;
	q[++r]=s;
	d[s]=1;
	while(l<=r)
	{
		int u=q[l++];
		for(int i=head[u];i;i=e[i].nt)
		{
			int v=e[i].t,w=e[i].w;
			if(w&&!d[v])
			{
				d[v]=d[u]+1;
				q[++r]=v;
			}
		}
	}
	return d[t];
}
il int dfs(int u,int flw)
{
	if(u==t) return flw;
	for(int& i=cur[u];i;i=e[i].nt)
	{
		int v=e[i].t,w=e[i].w;
		if(d[v]==d[u]+1&&w)
		{
			int p=dfs(v,min(w,flw));
			if(p)
			{
				e[i].w-=p;
				e[i^1].w+=p;
				return p;
			}
		}
	}
	return 0;
}
il int dinic()
{
	int nwflw,res=0;
	while(bfs())
	{
		for(int j=0;j<=s;j++) cur[j]=head[j];
		while((nwflw=dfs(s,inf)))
			res+=nwflw;
	}
	return res;
}
int main()
{
	n1=read(),n2=read(),n3=read();
	n=max(n1,max(n2,n3))+1;
	t=n*4+1,s=n*4+2;
	for(int i=1;i<=n1;i++)
		add(i,i+n,1);
	for(int i=1;i<=n2;i++)
		add(s,i+n*2,1);
	for(int i=1;i<=n3;i++)
		add(i+n*3,t,1);
	for(int i=1;i<=n1;i++)
	{
		int m2=read(),m3=read();
		for(int j=1;j<=m2;j++)
			add(read()+n*2,i,1);
		for(int j=1;j<=m3;j++)
			add(i+n,read()+n*3,1);
	}
	cout<<dinic()<<endl;
}
