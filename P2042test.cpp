#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include <bits/stdc++.h>
#define rint register int
#define For(i,a,b) for (rint i=a;i<=b;++i)
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e6+17;
int n,m,rt,cnt;
int a[N],id[N],fa[N],c[N][2];
int sum[N],sz[N],v[N],mx[N],lx[N],rx[N];
bool tag[N],rev[N];
//tag????????????,rev????????????
//sum?????????????,v????????
queue<int> q;
inline int read()
{
	rint x=0,f=1;
	char ch=getchar();
	while (ch<'0' || ch>'9')
	{
		if (ch=='-')f=-1;
		ch=getchar();
	}
	while ('0'<=ch && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
inline void pushup(rint x)
{
	rint l=c[x][0],r=c[x][1];
	sum[x]=sum[l]+sum[r]+v[x];
	sz[x]=sz[l]+sz[r]+1;
	mx[x]=max(mx[l],max(mx[r],rx[l]+v[x]+lx[r]));
	cout<<x<<' '<<mx[l]<<' '<<mx[r]<<' '<<rx[l]+v[x]+lx[r]<<endl;
	lx[x]=max(lx[l],sum[l]+v[x]+lx[r]);
	rx[x]=max(rx[r],sum[r]+v[x]+rx[l]);
}
//??????
inline void pushdown(rint x)
{
	rint l=c[x][0],r=c[x][1];
	if (tag[x])
	{
		rev[x]=tag[x]=0;//?????????????,???????????
		if (l)tag[l]=1,v[l]=v[x],sum[l]=v[x]*sz[l];
		if (r)tag[r]=1,v[r]=v[x],sum[r]=v[x]*sz[r];
		if (v[x]>=0)
		{
			if (l)lx[l]=rx[l]=mx[l]=sum[l];
			if (r)lx[r]=rx[r]=mx[r]=sum[r];
		}
		else
		{
			if (l)lx[l]=rx[l]=0,mx[l]=v[x];
			if (r)lx[r]=rx[r]=0,mx[r]=v[x];
		}
	}
	if (rev[x])
	{
		rev[x]=0;
		rev[l]^=1;
		rev[r]^=1;
		swap(lx[l],rx[l]);
		swap(lx[r],rx[r]);
		//??,??????,????????????????,????
		swap(c[l][0],c[l][1]);
		swap(c[r][0],c[r][1]);
	}
}
//????
inline void rotate(rint x,rint &k)
{
	rint y=fa[x],z=fa[y],l=(c[y][1]==x),r=l^1;
	if (y==k)k=x;
	else c[z][c[z][1]==y]=x;
	fa[c[x][r]]=y;
	fa[y]=x;
	fa[x]=z;
	c[y][l]=c[x][r];
	c[x][r]=y;
	pushup(y);
	pushup(x);
	//????,?????????
}
inline void splay(rint x,rint &k)
{
	while (x!=k)
	{
		int y=fa[x],z=fa[y];
		if (y!=k)
		{
			if (c[z][0]==y^c[y][0]==x)rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
//???????????,????????
inline int find(rint x,rint rk)
{
	pushdown(x);
	//??????????find,????????????????
	rint l=c[x][0],r=c[x][1];
	if (sz[l]+1==rk)return x;
	if (sz[l]>=rk)return find(l,rk);
	else return find(r,rk-sz[l]-1);
}
//??find????????????
//?????????????????????
//??????????????????
//?,???????????????????????????
//????find???
inline void recycle(rint x)
{
	rint &l=c[x][0],&r=c[x][1];
	if (l)recycle(l);
	if (r)recycle(r);
	q.push(x);
	fa[x]=l=r=tag[x]=rev[x]=0;
}
//??????????????????,????
inline int split(rint k,rint tot)
{
	rint x=find(rt,k),y=find(rt,k+tot+1);
	splay(x,rt);
	splay(y,c[x][1]);
	return c[y][0];
}
//??split????????????
//??????split??,??[k+1,k+tot],??k,?k+tot+1??????????
//????????????????,????????????
inline void query(rint k,rint tot)
{
	rint x=split(k,tot);
	printf("%d\n",sum[x]);
}
inline void modify(rint k,rint tot,rint val)
{
	rint x=split(k,tot),y=fa[x];
	v[x]=val;
	tag[x]=1;
	sum[x]=sz[x]*val;
	if (val>=0)lx[x]=rx[x]=mx[x]=sum[x];
	else lx[x]=rx[x]=0,mx[x]=val;
	pushup(y);
	pushup(fa[y]);
	//????????,??????????
	//?????????,????????????
}
inline void rever(rint k,rint tot)
{
	rint x=split(k,tot),y=fa[x];
	//cout<<"qwq "<<x<<endl;
	if (!tag[x])
	{
		rev[x]^=1;
		swap(c[x][0],c[x][1]);
		swap(lx[x],rx[x]);
		//cout<<c[x][0]<<' '<<c[x][1]<<' '<<lx[x]<<' '<<rx[x]<<endl;
		//cout<<mx[rt]<<endl;
		pushup(y);
		pushup(fa[y]);
		cout<<y<<' '<<fa[y]<<endl;
	}
	//??
}
inline void erase(rint k,rint tot)
{
	rint x=split(k,tot),y=fa[x];
	recycle(x);
	c[y][0]=0;
	pushup(y);
	pushup(fa[y]);
	//??
}
inline void build(rint l,rint r,rint f)
{
	rint mid=(l+r)>>1,now=id[mid],pre=id[f];
	if (l==r)
	{
		mx[now]=sum[now]=a[l];
		tag[now]=rev[now]=0;
		//????tag?rev??0???,??????????????
		lx[now]=rx[now]=max(a[l],0);
		sz[now]=1;
	}
	if (l<mid)build(l,mid-1,mid);
	if (mid<r)build(mid+1,r,mid);
	v[now]=a[mid];
	fa[now]=pre;
	pushup(now);
	//??????
	c[pre][mid>=f]=now;
	//?mid>=f?,now?????????,??c[pre][1]=now,?mid<f???
}
inline void insert(rint k,rint tot)
{
	For(i,1,tot)a[i]=read();
	For(i,1,tot)
	if (!q.empty())id[i]=q.front(),q.pop();
	else id[i]=++cnt;//??????????????
	build(1,tot,0);//????tot?????????
	rint z=id[(1+tot)>>1];//?????
	rint x=find(rt,k+1),y=find(rt,k+2);
	//??,??????,????????????????
	splay(x,rt);
	splay(y,c[x][1]);
	//?k+1(?????????????)?(k+1)+1???????
	fa[z]=y;
	c[y][0]=z;
	//???????????????????????????
	pushup(y);
	pushup(x);
	//??????
}
//????????????????
//?????,????split????????
//??find???????
//???,???????????,?????????
int main()
{
	n=read(),m=read();
	mx[0]=a[1]=a[n+2]=-inf;
	For(i,1,n)a[i+1]=read();
	For(i,1,n+2)id[i]=i;//???????1?n+2,?????????????????
	build(1,n+2,0);//??
	rt=(n+3)>>1;
	cnt=n+2;//???????
	rint k,tot,val;
	char ch[10];
	while (m--)
	{
		scanf("%s",ch);
		if (ch[0]!='M' || ch[2]!='X') k=read(),tot=read();
		if (ch[0]=='I')insert(k,tot);
		if (ch[0]=='D')erase(k,tot);
		if (ch[0]=='M')
		{
			if (ch[2]=='X')printf("%d\n",mx[rt]);
			else val=read(),modify(k,tot,val);
		}
		if (ch[0]=='R')rever(k,tot);
		if (ch[0]=='G')query(k,tot);
	}
	return 0;
}
