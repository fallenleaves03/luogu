#include <bits/stdc++.h>
#define il inline
#define gc() getchar()
#define Max 1000050
//#define gc() (ss==tt&&(tt=(ss=In)+fread(In,1,Max,stdin)),ss==tt?EOF:*ss++)
using  namespace std;
char In[Max],*ss=In,*tt=In;
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
int head[Max],tot,vst[Max],d[Max],f[Max][32],n,m,cnt[Max],q[Max];
il void add(int u,int v)
{
	e[++tot].t=v;
	e[tot].nt=head[u];
	head[u]=tot;
}
il void dfs(int u,int fa)
{
	f[u][0]=fa;
	d[u]=d[fa]+1;
	for(int i=1;i<=25;i++)
		f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nt)
	{
		int v=e[i].t;
		if(v==fa) continue;
		dfs(v,u);
	}
}
il int lca(int u,int v)
{
	if(d[u]<d[v]) swap(u,v);
	for(int i=25;i>=0;i--)
		if(d[f[u][i]]>=d[v]) u=f[u][i];
	if(u==v) return u;
	for(int i=25;i>=0;i--)
	{
		if(f[u][i]!=f[v][i])
			u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
il int dfs2(int u,int fa)
{
	int ans=cnt[u],fid;
	for(int i=head[u];i;i=e[i].nt)
	{
		int v=e[i].t;
		if(v==fa)
		{
			fid=i;
			continue;
		}
		ans+=(e[i].w=dfs2(v,u));
	}
	e[fid].w=ans;
	return ans;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		q[i]=read();
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(q[1],0);
	for(int i=1;i<n;i++)
	{
		cnt[q[i]]++,cnt[q[i+1]]++;
		cnt[lca(q[i],q[i+1])]-=2;
	}
	dfs2(q[1],0);
	for(int u=1;u<=n;u++)
	{
		int ans=0;
		for(int i=head[u];i;i=e[i].nt)
			ans+=e[i].w;
		if(u==q[n]) ans--;
		printf("%d\n",(ans+1)>>1);
		//cout<<"qwq "<<u<<endl;
	}
	return 0;
}
