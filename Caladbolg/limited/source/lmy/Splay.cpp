const int maxn = 500010,inf = 1<<29;
int N,M,root,cnt,arr[maxn],tag[maxn],key[maxn],fa[maxn],ch[maxn][2],lb[maxn],rb[maxn];
int wb[maxn],sum[maxn],size[maxn],stk[maxn]; bool rev[maxn]; char cmd[20]; queue <int> team;

inline int gi()
{
	char ch; int ret = 0,f = 1;
	do ch = getchar(); while (!(ch >= '0'&&ch <= '9')&&ch != '-');
	if (ch == '-') f = -1,ch = getchar();
	do ret = ret*10+ch-'0',ch = getchar(); while (ch >= '0'&&ch <= '9');
	return ret*f;
}

inline int newnode(int x = 0)
{
	int ret;
	if (!team.empty())
		ret = team.front(),team.pop();
	else ret = ++cnt;
	key[ret] = sum[ret] = lb[ret] = rb[ret] = wb[ret] = x;
	rev[ret] = false; tag[ret] = inf; size[ret] = 1;
	return ret;
}

inline void pushdown(int now) { }

inline void update(int now)
{
	// pushdown(now);
	int lc = ch[now][0],rc = ch[now][1];
	size[now] = size[lc]+size[rc]+1;
	sum[now] = sum[lc]+sum[rc]+key[now];
	if (lc&&rc) { } 
	else if (lc) { }
	else if (rc) { }
	else { }
}

inline int build(int l,int r)
{
	int mid = (l+r) >> 1,ret = newnode(arr[mid]);
	if (l < mid) ch[ret][0] = build(l,mid-1),fa[ch[ret][0]] = ret;
	if (r > mid) ch[ret][1] = build(mid+1,r),fa[ch[ret][1]] = ret;
	update(ret); return ret;
}

inline void init()
{
	root = newnode(); ch[root][1] = newnode(); fa[2] = 1;
	for (int i = 1;i <= N;++i) arr[i] = gi();
	ch[2][0] = build(1,N); fa[ch[2][0]] = 2;
	update(2); update(1);
}

inline int find(int rk)
{
	for (int now = root;;)
	{
		pushdown(now);
		if (rk == size[ch[now][0]]+1) return now;
		else if (rk > size[ch[now][0]]+1)
			rk -= size[ch[now][0]]+1,now = ch[now][1];
		else now = ch[now][0];
	}
	return 0;
}

inline void rotate(int x)
{
	int y = fa[x],z = fa[y],l = ch[y][0] != x,r = l^1;
	if (z) ch[z][ch[z][0] != y] = x;
	fa[x] = z; fa[y] = x; fa[ch[x][r]] = y;
	ch[y][l] = ch[x][r]; ch[x][r] = y;
	update(y); update(x);
}
inline void splay(int x,int aim)
{
	int top = 0;
	for (int i = x;i;i = fa[i]) stk[++top] = i;
	while (top) pushdown(stk[top--]);
	while (fa[x] != aim)
	{
		int y = fa[x],z = fa[y];
		if (z != aim)
		{
			if ((ch[y][0] == x)^(ch[z][0] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if (!aim) root = x;
}

inline void Delete(int &now)
{
	if (!now) return;
	Delete(ch[now][0]);
	Delete(ch[now][1]);
	team.push(now); now = 0;
}

inline void print()
{
	for (int i = 1;i <= cnt;++i)
		printf("%d:%d %d\n",i,ch[i][0],ch[i][1]);
	for (int i = 1;i <= cnt;++i)
		printf("%d:%d\n",i,fa[i]);
	
}

inline void laydown(int now)
{
	if (!now) return;
	pushdown(now);
	laydown(ch[now][0]);
	printf("%d ",key[now]);
	laydown(ch[now][1]);
	update(now);
}

