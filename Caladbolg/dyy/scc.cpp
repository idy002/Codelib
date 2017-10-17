#include <cstdio>
#include <cstring>
#include <vector>
#define maxn 10010
using namespace std;

int n, m;
vector<int> g[maxn], gg[maxn], scc[maxn], stk;
int dfn[maxn], low[maxn], sccno[maxn], scc_cnt, dfs_clock;
int indgr[maxn];


void dfs( int u ) {
	dfn[u] = low[u] = ++dfs_clock;
	stk.push_back( u );
	for( int t=0; t<g[u].size(); t++ ) {
		int v=g[u][t];
		if( !dfn[v] ) {
			dfs(v);
			low[u] = min( low[u], low[v] );
		} else if( !sccno[v] ) 
			low[u] = min( low[u], dfn[v] );
	}
	if( dfn[u]==low[u] ) {
		scc_cnt++;
		while(1) {
			int v = stk.back();
			sccno[v] = scc_cnt;
			scc[scc_cnt].push_back(v);
			stk.pop_back();
			if( v==u ) break;
		}
	}
}
int main() {
	scanf( "%d%d", &n, &m );
	for( int i=1,u,v; i<=m; i++ ) {
		scanf( "%d%d", &u, &v );
		g[v].push_back(u);
	}
	for( int i=1; i<=n; i++ ) 
		if( !dfn[i] ) dfs(i);
	for( int u=1; u<=n; u++ ) {
		for( int t=0; t<g[u].size(); t++ ) {
			int v = g[u][t];
			if( sccno[u]!=sccno[v] ) 
				indgr[sccno[v]]++;
		}
	}
	int ans, cnt=0;
	for( int i=1; i<=scc_cnt; i++ )
		if( indgr[i]==0 ) {
			cnt++;
			if( cnt>1 ) {
				printf( "0\n" );
				return 0;
			}
			ans = (int)scc[i].size();
		}
	printf( "%d\n", ans );
}


