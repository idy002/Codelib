const int N = 1000 + 10;

int n, m;
int match[N], visit[N], stamp;
vector<int> edge[N];

bool dfs( int u ) {
	for( int t = 0; t < (int)edge[u].size(); t++ ) {
		int v = edge[u][t];
		if( visit[v] == stamp ) continue;
		visit[v] = stamp;
		if( match[v] == 0 || dfs(match[v]) ) {
			match[v] = u;
			return true;
		}
	}
	return false;
}
int hungary() {
	int ans = 0;
	memset( visit, 0, sizeof(visit) );
	memset( match, 0, sizeof(match) );
	stamp = 0;
	for( int u = 1; u <= n; u++ ) {
		++stamp;
		ans += dfs( u );
	}
	return ans;
}
