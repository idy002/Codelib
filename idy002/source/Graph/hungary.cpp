const int N = 1010;

int n, m;
int lno[N], rno[N];
vector<int> g[N];
int vis[N], vclock;

bool dfs( int u ) {
	for( int t = 0; t < (int)g[u].size(); t++ ) {
		int v = g[u][t];
		if( vis[v] == vclock ) continue;
		vis[v] = vclock;
		if( rno[v] == 0 || dfs(rno[v]) ) {
			lno[u] = v;
			rno[v] = u;
			return true;
		}
	}
	return false;
}
int hungary() {
	int match = 0;
	vclock = 0;
	for( int u = 1; u <= n; u++ ) {
		vclock++;
		match += dfs(u);
	}
	return match;
}

