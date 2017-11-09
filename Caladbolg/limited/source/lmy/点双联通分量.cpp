const int maxn = 400010;
int N,M,Q,cnt = 1,side[maxn],toit[maxn],nxt[maxn],f[maxn][25],father[maxn],low[maxn];
int tot,dep[maxn],dfn[maxn],nside[maxn],ntoit[maxn],nnxt[maxn]; bool cut[maxn];
stack <int> S; vector <int> bel[maxn],bcc[maxn]; bool vis[maxn];

inline int find(int a) { if (father[a] != a) father[a] = find(father[a]); return father[a]; }
inline void add(int a,int b) { nxt[++cnt] = side[a]; side[a] = cnt; toit[cnt] = b; }
inline void ins(int a,int b) { add(a,b); add(b,a); }
inline void nadd(int a,int b) { nnxt[++cnt] = nside[a]; nside[a] = cnt; ntoit[cnt] = b; }
inline void nins(int a,int b) { nadd(a,b); nadd(b,a); }

inline void tj(int now,int fa)
{
	dfn[now] = low[now] = ++cnt; int child = 0;
	for (int i = side[now];i;i = nxt[i])
	{
		if (toit[i] == fa) continue;
		if (!dfn[toit[i]])
		{
			S.push(i>>1); tj(toit[i],now); ++child;
			low[now] = min(low[now],low[toit[i]]);
			if (low[toit[i]] >= dfn[now])
			{
				cut[now] = true; ++tot;
				while (true)
				{
					int t = S.top(); S.pop();
					bel[toit[t<<1]].push_back(tot);	bel[toit[t<<1|1]].push_back(tot);
					bcc[tot].push_back(toit[t<<1]); bcc[tot].push_back(toit[t<<1|1]);
					if (t == (i>>1)) break;
				}
			}
		}
		else low[now] = min(low[now],dfn[toit[i]]);
	}
	if (!fa&&child == 1) cut[now] = false;
}

inline void build()
{
	vector <int> cuts; cnt = 1;
	for (int i = 1;i <= tot;++i)
	{
		sort(bcc[i].begin(),bcc[i].end());
		bcc[i].erase(unique(bcc[i].begin(),bcc[i].end()),bcc[i].end());
	}
	for (int i = 1;i <= N;++i) if (cut[i]) cuts.push_back(i);
	for (auto x:cuts)
	{
		sort(bel[x].begin(),bel[x].end());
		bel[x].erase(unique(bel[x].begin(),bel[x].end()),bel[x].end());
		++tot; for (auto y:bel[x]) nins(tot,y);
		bel[x].clear(); bel[x].push_back(tot); bcc[tot].push_back(x);
	}
}

