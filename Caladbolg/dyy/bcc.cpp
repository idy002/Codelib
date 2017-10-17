#include <cstdio>
#include <vector>
using namespace std;

const int N = 1000+10;
const int M = N*N;

struct Edge {
    int u, v;
    Edge( int u, int v ):u(u),v(v){}
};

int n, m;
int head[N], dest[M], next[M], etot;
int dfn[N], low[N], bccno[N], iscut[N], bcc_cnt, idc;
vector<int> bcc[N];
vector<Edge> stk;

void adde( int u, int v ) {
    etot++;
    dest[etot] = v;
    next[etot] = head[u];
    head[u] = etot;
}
void dfs( int u, int fa ) {
    dfn[u] = low[u] = ++idc;
    int child = 0;
    for( int t=head[u]; t; t=next[t] ) {
        int v=dest[t];
        if( v==fa ) continue;

        if( !dfn[v] ) {
            stk.push_back( Edge(u,v) );
            dfs(v,u);
            low[u] = min( low[u], low[v] );
            child++;
            if( low[v]>=dfn[u] ) {
                iscut[u] = true;
                bcc_cnt++;
                while(1) {
                    Edge e=stk.back();
                    stk.pop_back();
                    if( !bccno[e.u] ) bccno[e.u]=bcc_cnt,bcc[bcc_cnt].push_back(e.u);
                    if( !bccno[e.v] ) bccno[e.v]=bcc_cnt,bcc[bcc_cnt].push_back(e.v);
                    if( e.u==u && e.v==v ) break;
                }
            }
        } else if( dfn[v]<dfn[u] ) {
            low[u] = min( low[u], dfn[v] );
        }
    }
    if( u==fa && child<=1 ) iscut[u]=false;
}
int main() {
    scanf( "%d%d", &n, &m );
    for( int i=1,u,v; i<=m; i++ ) {
        scanf( "%d%d", &u, &v );
        adde( u, v );
        adde( v, u );
    }
    dfs(1,1);
    for( int u=1; u<=n; u++ )
        if( iscut[u] ) printf( "%d ", u );
    printf( "\n" );
}
