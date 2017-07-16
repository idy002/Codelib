/*
一些定义:

弦图是一种特殊图:它的所有极小环都只有3个顶点。

单纯点：该顶点与其邻接点在原图中的导出子图是一个完全图。

图G的完美消去序列：一个顶点序列a1a2a3...an,使得对于每个元素ai，ai在ai、ai+1、ai+2...an的导出子图中是一个单纯点。

 

弦图有一个性质：任何一个弦图都至少存在一个单纯点（该点和其邻接点组成一个完全图）

弦图另一个性质：一个图是弦图当且仅当其存在完美消去序列。（归纳证明）

 

最大势算法(msc）：若原图是弦图，则该算法计算出的序列是完美消去序列。

算法大致思想：从后往前计算序列，每次选择点v作为序列中的元素，v是还未选的点中与已经选了的点连边最多的点。

然后检查该序列是否是完美消去序列。
*/
/**************************************************************
    Problem: 1242
    User: idy002
    Language: C++
    Result: Accepted
    Time:544 ms
    Memory:1816 kb
****************************************************************/
 
#include <cstdio>
#include <cstring>
#define N 1010
#define M N*N*2
 
int n, m;
bool c[N][N];
int qu[N], inq[N], dgr[N];
int stk[N], top;
 
void msc() {
    dgr[0] = -1;
    for( int i=n; i>=1; i-- ) {
        int s = 0;
        for( int u=1; u<=n; u++ ) 
            if( !inq[u] && dgr[u]>dgr[s] ) s=u;
        qu[i] = s;
        inq[s] = true;
        for( int u=1; u<=n; u++ )
            if( !inq[u] && c[s][u] ) dgr[u]++;
    }
}
bool check() {
    for( int i=n; i>=1; i-- ) {
        int s=qu[i];
        top = 0;
        for( int j=i+1; j<=n; j++ )
            if( c[s][qu[j]] ) stk[++top] = qu[j];
        if( top==0 ) continue;
        for( int j=2; j<=top; j++ )
            if( !c[stk[1]][stk[j]] ) return false;
    }
    return true;
}
int main() {
    scanf( "%d%d", &n, &m );
    for( int i=1,u,v; i<=m; i++ ) {
        scanf( "%d%d", &u, &v );
        c[u][v] = c[v][u] = 1;
    }
    msc();
    printf( "%s\n", check() ? "Perfect" : "Imperfect" );
}

/*
给定一个弦图，问最少染色数。

对于弦图的一个完美消去序列，从后往前染色，每次染可以染的最小编号的颜色，由完美消去序列的定义，
序列任一后缀的点的导出子图中，由该后缀第一个元素及其邻接点导出的子图一定是完全图，所以，序列中
某一元素染的颜色编号是该完全图的大小。所以最小染色数小于等于最大团的点数，而显然前者又大于等于后者，
故弦图的最小染色数等于最大团的大小。
*/

/**************************************************************
    Problem: 1006
    User: idy002
    Language: C++
    Result: Accepted
    Time:1672 ms
    Memory:11968 kb
****************************************************************/
 
#include <cstdio>
#include <vector>
#define maxn 10010
using namespace std;
 
int n, m;
vector<int> g[maxn];
bool done[maxn];
int label[maxn], pos[maxn];
 
int msc() {
    int rt = 0;
    for( int i=n; i>=1; i-- ) {
        int mu = 0;
        for( int u=1; u<=n; u++ ) {
            if( !done[u] ) {
                if( !mu || label[u]>label[mu] )
                    mu = u;
            }
        }
        done[mu] = true;
        pos[mu] = i;
        int cnt = 0;
        for( int t=0; t<g[mu].size(); t++ ) {
            int v = g[mu][t];
            if( done[v] ) {
                cnt++;
            } else {
                label[v]++;
            }
        }
        rt = max( rt, cnt+1 );
    }
    return rt;
}
int main() {
    scanf( "%d%d", &n, &m );
    for( int i=1,u,v; i<=m; i++ ) {
        scanf( "%d%d", &u, &v );
        g[u].push_back(v);
        g[v].push_back(u);
    }
    printf( "%d\n", msc() );
}
