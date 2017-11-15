// 询问树上路径元素mex，inc dec复杂度不对，需要用线段树/set(带log)或者分块(修改O(1))
// 若包括lca，每组询问需要把lca补(inc)上去。
const int Size = 337,maxn = 200010;
int N,Q,cnt,nxt[maxn],side[maxn],len[maxn],toit[maxn],f[maxn][20],key[maxn],timestamp;
int dep[maxn],L[maxn],R[maxn],dfn[maxn],ans[maxn],exist[maxn],show[maxn],res;
struct Node
{
	int a,b,c,id;
	Node() = default;
	Node(int _a,int _b,int _c = 0,int _id = 0):a(_a),b(_b),c(_c),id(_id) {}
	inline void read(int i)
	{
		id = i; scanf("%d %d",&a,&b); c = lca(a,b);
		if (c == a||c == b) { if (a != c) swap(a,b); a = L[c]+1; b = L[b]; }
		else { if (L[a] > L[b]) swap(a,b); a = R[a]; b = L[b]; }
	}
	friend inline bool operator <(const Node &x,const Node &y) { return x.b < y.b; }
}query[maxn];

inline bool cmp(const Node &x,const Node &y) { return x.a < y.a; }
inline void work()
{
	int l = 1,r = 0;
	for (int i = 1;i <= Q;++i) {
		while (r < query[i].b) {
			show[dfn[++r]]++;
			if (show[dfn[r]] == 2) dec(dfn[r]); else inc(dfn[r]); }
		while (l > query[i].a) {
			show[dfn[--l]]++;
			if (show[dfn[l]] == 2) dec(dfn[l]); else inc(dfn[l]); }
		while (r > query[i].b) {
			if (show[dfn[r]] == 1) dec(dfn[r]); else inc(dfn[r]);
			show[dfn[r--]]--; }
		while (l < query[i].a) {
			if (show[dfn[l]] == 1) dec(dfn[l]); else inc(dfn[l]);
			show[dfn[l++]]--; }
		ans[query[i].id] = res; }
}

int main() {
	dfs(1);
	for (int i = 1;i <= Q;++i) query[i].read(i);
	sort(query+1,query+Q+1,cmp);
	for (int i = 1,j;i <= Q;i = j) {
		for (j = i;j <= Q&&query[j].a-query[i].a <= Size;++j);
		sort(query+i+1,query+j);
	}
	work();
	for (int i = 1;i <= Q;++i) printf("%d\n",ans[i]);
}
