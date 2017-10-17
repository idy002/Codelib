/*
　1、带修改，其实就是暴力，只是将同一块的查询再按照时间顺序排，这样就能减少在修改操作上“爬"的时间，
　其实就是利用了数据随机这个特点，可以构造数据来卡。

　　2、以前排序的方法是u按照块，v按照dfs序，这次两个都是按照块，其实差不多。
*/
/**************************************************************
    Problem: 3052
    User: idy002
    Language: C++
    Result: Accepted
    Time:101223 ms
    Memory:21792 kb
****************************************************************/
 
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define P(p) ((1)<<(p))
#define maxn 100010
#define maxp 16
using namespace std;
 
typedef long long dint;
 
int n, m, q, qq, qm;
int cc[maxn], ww[maxn], vv[maxn];
vector<int> g[maxn], stk;
int mno[maxn], mcc_siz, mcc_cnt;
int anc[maxn][maxp+1], depth[maxn], dfn[maxn], dfs_clock;
bool stat[maxn];
dint cnt[maxn], cur_ans;
dint ans[maxn];
int mdu[maxn], mdc[maxn], mdo[maxn], mdcc[maxn];
 
struct Qu {
    int u, v, t, id;
    bool operator<( const Qu & b ) const {
        if( mno[u]^mno[b.u] ) return mno[u]<mno[b.u];
        if( mno[v]^mno[b.v] ) return mno[v]<mno[b.v];
        return t<b.t;
    }
};
Qu qu[maxn];
 
int dfs( int u ) {
    dfn[u] = ++dfs_clock;
    depth[u] = depth[anc[u][0]]+1;
    for( int p=1; p<=maxp; p++ ) {
        anc[u][p] = anc[anc[u][p-1]][p-1];
        if( !anc[u][p] ) break;
    }
 
    int sz = 0;
    for( int t=0; t<g[u].size(); t++ ) {
        int v = g[u][t];
        if( v==anc[u][0] ) continue;
        anc[v][0] = u;
        sz += dfs(v);
        if( sz > mcc_siz ) {
            mcc_cnt++;
            for( int i=1; i<=sz; i++ ) {
                mno[stk.back()] = mcc_cnt;
                stk.pop_back();
            }
            sz = 0;
        }
    }
    stk.push_back( u );
    return sz+1;
}
 
int lca( int u, int v ) {
    if( depth[u]<depth[v] ) swap(u,v);
    int t = depth[u]-depth[v];
    for( int p=0; t; t>>=1, p++ ) 
        if( t&1 ) u=anc[u][p];
    if( u==v ) return u;
    for( int p=maxp; p>=0 && anc[u][0]!=anc[v][0]; p-- ) 
        if( anc[u][p]!=anc[v][p] ) 
            u = anc[u][p], v = anc[v][p];
    return anc[u][0];
}
 
void inv_sig( int u ) {
    if( stat[u] ) {
        cur_ans -= (dint)ww[cnt[cc[u]]]*vv[cc[u]];
        cnt[cc[u]]--;
    } else {
        cnt[cc[u]]++;
        cur_ans += (dint)ww[cnt[cc[u]]]*vv[cc[u]];
    }
    stat[u] ^= 1;
}
 
void chg_sig( int u, int type ) {
    if( stat[u] ) {
        inv_sig(u);
        cc[u] = type;
        inv_sig(u);
    } else cc[u] = type;
}
 
void inv_chain( int u, int v ) {
    int ca = lca(u,v);
    for( ; u!=ca; u=anc[u][0] ) inv_sig(u);
    for( ; v!=ca; v=anc[v][0] ) inv_sig(v);
}
void app_time( int fm, int to ) {
    while( fm<to ) {
        fm++;
        chg_sig(mdu[fm],mdc[fm]);
    }
    while( to<fm ) {
        chg_sig(mdu[fm],mdo[fm]);
        fm--;
    }
}
 
void work() {
    sort( qu+1, qu+1+qq );
    int ou=qu[1].u;
    int ov=qu[1].u;
    int ot=0;
    for( int i=1; i<=qq; i++ ) {
        int u = qu[i].u, v = qu[i].v;
        inv_chain( u, ou );
        inv_chain( v, ov );
        app_time( ot, qu[i].t );
        ot = qu[i].t;
        ou = u;
        ov = v;
        int ca = lca(u,v);
        inv_sig( ca );
        ans[qu[i].id] = cur_ans;
        inv_sig( ca );
    }
}
 
int main() {
    scanf( "%d%d%d", &n, &m, &q );
    for( int i=1; i<=m; i++ ) scanf( "%d", vv+i );
    for( int i=1; i<=n; i++ ) scanf( "%d", ww+i );
    for( int i=1,u,v; i<n; i++ ) {
        scanf( "%d%d", &u, &v );
        g[u].push_back(v);
        g[v].push_back(u);
    }
    mcc_siz = (int)(pow(n,2.0/3.0))+1;
    dfs(1);
    while( !stk.empty() ) {
        mno[stk.back()] = mcc_cnt;
        stk.pop_back();
    }
    for( int i=1; i<=n; i++ ) {
        scanf( "%d", cc+i );
        mdcc[i] = cc[i];
    }
    for( int i=1,type,x,y; i<=q; i++ ) {
        scanf( "%d%d%d", &type, &x, &y );
        if( !type ) {
            qm++;
            mdu[qm]=x, mdc[qm]=y, mdo[qm]=mdcc[x];
            mdcc[x] = y;
        } else {
            qq++;
            qu[qq].u=x, qu[qq].v=y, qu[qq].t=qm, qu[qq].id=qq;
        }
    }
    work();
    for( int i=1; i<=qq; i++ ) 
        printf( "%lld\n", ans[i] );
}
