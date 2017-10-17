/*
第一道"虚树"题目（好吧，我也不知道这是不是虚树，但和虚树的思想肯定是一样的，都是简化树结构）

这一类算法核心思想都是简化树结构，只取我们必须的节点和一些信息，然后在简化后的树结构上工作。

首先，如果这道题只有一次询问，那么很容易想到树形DP的解法，但这道题又多组询问，并且限制了所有询问的关键点个数，
这意味着我们必须设计出一种算法，她回答一组询问的复杂度只和关键点个数相关（O(k)或O(klogk)都是可接受的），而和原图无关（最多加个logn)。

然后就有了虚树，我们可以构建一个新的树，这棵树上有所有关键点，以及相邻dfs序上相邻的两个关键点的lca，我们发现，
这样的图包括了所有关键点的lca以及所有关键点，然后改一下DP就可以在这棵树上快速的搞了（因为节点个数是O(2*k)，
所以这样DP的复杂度就从O(n)变成了O(k)）。
DP：

dp[i]表示将i及其子树中所有关键点与跟节点断开所需的最小代价（可以砍他们上面的边）

构简化图：

对于一个询问，我们先将其关键点按照DFS序排序。然后维护一个栈保存当前走了的关键点或关键点之间的LCA，
当我们要插入一个新的关键节点时，我们根据当前节点与当前栈顶节点LCA的深度与栈顶元素的深度来判断是否需要弹出节点，一直弹出，
直到深度大于等于栈顶元素（注意，这个LCA是最初的栈顶与新的关键节点的LCA）
*/
/**************************************************************
    Problem: 2286
    User: idy002
    Language: C++
    Result: Accepted
    Time:6700 ms
    Memory:32060 kb
****************************************************************/
 
#include <cstdio>
#include <vector>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
#define oo 0x3f3f3f3f
#define N 250010
#define P 17
using namespace std;
 
typedef long long dnt;
 
int n, m;
int head[N], dest[N+N], wght[N+N], next[N+N], ntot;
int dfn[N], dep[N], bst[N], anc[N][P+1], idc;
int qcnt, aa[N], stk[N], top;
dnt dp[N];
 
void adde( int u, int v, int w ) {
    ntot++;
    wght[ntot] = w;
    dest[ntot] = v;
    next[ntot] = head[u];
    head[u] = ntot;
}
void dfs( int u ) {
    dfn[u] = ++idc;
    for( int p=1; p<=P; p++ )
        anc[u][p] = anc[anc[u][p-1]][p-1];
    for( int t=head[u]; t; t=next[t] ) {
        int v=dest[t], w=wght[t];
        if( v==anc[u][0] ) continue;
        anc[v][0] = u;
        bst[v] = min( bst[u], w );
        dep[v] = dep[u]+1;
        dfs(v);
    }
}
bool cmp( int u, int v ) {
    return dfn[u]<dfn[v];
}
int lca( int u, int v ) {
    if( dep[u]<dep[v] ) swap(u,v);
    int t=dep[u]-dep[v];
    for( int p=0; t; t>>=1,p++ )
        if( t&1 ) u=anc[u][p];
    if( u==v ) return u;
    for( int p=P; p>=0 && anc[u][0]!=anc[v][0]; p-- )
        if( anc[u][p]!=anc[v][p] ) 
            u=anc[u][p], v=anc[v][p];
    return anc[u][0];
}
void sov() {
    scanf( "%d", &qcnt );
    for( int i=1; i<=qcnt; i++ ) 
        scanf( "%d", aa+i );
    sort( aa+1, aa+1+qcnt, cmp );
     
    stk[top=1] = 1;
    dp[1] = 0;
    for( int i=1; i<=qcnt; i++ ) {
        int ca=lca(aa[i],stk[top]);
        while( dep[stk[top]]>dep[ca] ) {
            int fa, u;
            u = stk[top];
            top--;
            if( dep[stk[top]]<=dep[ca] ) {
                if( dep[stk[top]]<dep[ca] ) {
                    stk[++top] = ca;
                    dp[ca] = 0;
                }
                fa = stk[top];
 
                dp[u] = min( dp[u], bst[u] );
                dp[fa] += dp[u];
                break;
            } 
            fa = stk[top];
 
            dp[u] = min( dp[u], bst[u] );
            dp[fa] += dp[u];
        }
        int u=aa[i];
        stk[++top] = u;
 
        dp[u] = bst[u];
    }
    while( top ) {
        if( top-1 ) {
            int fa=stk[top-1], u=stk[top];
 
            dp[u] = min( dp[u], bst[u] );
            dp[fa] += dp[u];
        }
        top--;
    }
    printf( "%lld\n", dp[1] );
}
int main() {
    scanf( "%d", &n );
    for( int i=1,u,v,w; i<n; i++ ) {
        scanf( "%d%d%d", &u, &v, &w );
        adde( u, v, w );
        adde( v, u, w );
    }
    anc[1][0] = 1;
    dep[1] = 1;
    bst[1] = oo;
    dfs(1);
    scanf( "%d", &m );
    for( int i=1; i<=m; i++ )
        sov();
}
