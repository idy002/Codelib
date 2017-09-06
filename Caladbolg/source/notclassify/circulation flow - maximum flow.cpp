/*
1. 上下界网络流求最大流步骤:

　　1) 建出无环无汇的网络,并看是否存在可行流

　　2) 如果存在,那么以原来的源汇跑一次最大流

　　3) 流量下界加上当前网络每条边的流量就是最大可行流了.

2. 输出方案:

　　可以把边的位置信息一起存在边表中,求完最大流后遍历一下边,把信息更新过去.
　　*/
#include <cstdio>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))
#define oo 0x3f3f3f3f
#define N 1500
#define M 500000

struct Dinic {
    int n, src, dst;
    int head[N], dest[M], flow[M], next[M], info[M][2], etot;
    int cur[N], dep[N], qu[N], bg, ed;
    void init( int n, int src, int dst ) {
        this->n = n;
        this->src = src;
        this->dst = dst;
        etot = 0;
        memset( head, -1, sizeof(head) );
    }
    void adde( int i, int j, int u, int v, int f ) {
        next[etot]=head[u],flow[etot]=f,dest[etot]=v,info[etot][0]=i,info[etot][1]=j; head[u]=etot++;
        next[etot]=head[v],flow[etot]=0,dest[etot]=u,info[etot][0]=-1,info[etot][1]=-1; head[v]=etot++;
    }
    bool bfs() {
        memset( dep, 0, sizeof(dep) );
        qu[bg=ed=1] = src;
        dep[src] = 1;
        while( bg<=ed ) {
            int u=qu[bg++];
            for( int t=head[u]; t!=-1; t=next[t] ) {
                int v=dest[t], f=flow[t];
                if( f && !dep[v] ) {
                    dep[v] = dep[u]+1;
                    qu[++ed] = v;
                }
            }
        }
        return dep[dst];
    }
    int dfs( int u, int a ) {
        if( u==dst || a==0 ) return a;
        int remain=a, past=0, na;
        for( int &t=cur[u]; t!=-1; t=next[t] ) {
            int v=dest[t], &f=flow[t], &vf=flow[t^1];
            if( f && dep[v]==dep[u]+1 && (na=dfs(v,min(remain,f))) ) {
                f -= na;
                vf += na;
                remain -= na;
                past += na;
                if( !remain ) break;
            }
        }
        return past;
    }
    int maxflow() {
        int f=0;
        while( bfs() ) {
            memcpy( cur, head, sizeof(cur) );
            f += dfs(src,oo);
        }
        return f;
    }
}D;
struct Btop {
    int n;
    int head[N], dest[M], bval[M], tval[M], next[M], info[M][2], etot;
    int si[N], so[N];
    void init( int n ) {
        this->n = n;
        etot = 0;
        memset( head, -1, sizeof(head) );
        memset( si, 0, sizeof(si) );
        memset( so, 0, sizeof(so) );
    }
    void adde( int i, int j, int u, int v, int b, int t ) {
        next[etot]=head[u],tval[etot]=t,bval[etot]=b,dest[etot]=v; 
        info[etot][0]=i, info[etot][1]=j;
        si[v] += b, so[u] += b;
        head[u]=etot++;
    }
    bool ok() {
        int src=n+1, dst=n+2;
        D.init( dst, src, dst );
        for( int u=1; u<=n; u++ )
            for( int t=head[u]; t!=-1; t=next[t] ) {
                int v=dest[t];
                D.adde( info[t][0], info[t][1], u, v, tval[t]-bval[t] );
            }
        int sum = 0;
        for( int u=1; u<=n; u++ ) {
            if( si[u]>so[u] ) {
                D.adde( -1, -1, src, u, si[u]-so[u] );
                sum += si[u]-so[u];
            } else if( so[u]>si[u] ) {
                D.adde( -1, -1, u, dst, so[u]-si[u] );
            }
        }
        return sum==D.maxflow();
    }
}B;

int n, m;
int c[375];
int ans[375][110], tot;

int main() {
    while( scanf( "%d%d", &n, &m ) == 2 ) {
        int src=n+m+1, dst=src+1;
        B.init(dst);
        for( int i=1,g; i<=m; i++ ) {
            scanf( "%d", &g );
            B.adde( -1, -1, n+i, dst, g, oo );
        }
        memset( ans, 0, sizeof(ans) );
        tot = 0;
        for( int i=1,d; i<=n; i++ ) {
            scanf( "%d%d", c+i, &d );
            B.adde( -1, -1, src, i, 0, d );
            for( int j=1,t,l,r; j<=c[i]; j++ ) {
                scanf( "%d%d%d", &t, &l, &r );
                t++;
                B.adde( i, j, i, n+t, l, r );
                ans[i][j] = l;
                tot += l;
            }
        }
        B.adde( -1, -1, dst, src, 0, oo );
        bool ok = B.ok();
        if( !ok ) {
            printf( "-1\n" );
        } else {
            D.src=src;
            D.dst=dst;
            D.maxflow();
            for( int t=0; t<D.etot; t++ ) {
                int i=D.info[t][0], j=D.info[t][1];
                if( ~i && ~j ) {
                    ans[i][j] += D.flow[t^1];
                    tot += D.flow[t^1];
                }
            }
            printf( "%d\n", tot );
            for( int i=1; i<=n; i++ )
                for( int j=1; j<=c[i]; j++ )
                    printf( "%d\n", ans[i][j] );
        }
        printf( "\n" );
    }
}
