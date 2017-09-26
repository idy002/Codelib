/*
算法步骤:

　　1. 先将原图像最大可行流那样变换,唯一不同的是不加dst->src那条边来将它变成无源无汇的网络流图.直接跑一边超级源到超级汇的最大流.

　　2. 加上刚才没有加上的那条边p

　　3. 再跑一遍超级源汇之间的最大流,p的流量就是我们要求的最小可行流流量(等于其反向边的"容量")

 

收获:

　　1. 最大可行流和最小可行流,当我们把其残量网络求出来后,其流量就是dst->src的残量.

　　　 每条边在此时的流量 = 流量下界 + 转换后对应边的流量
*/
#include <cstdio>
#include <cassert>
#include <cstring>
#define min(a,b) ((a)<(b)?(a):(b))
#define oo 0x3f3f3f3f
#define N 110
#define M N*N

struct Dinic {
    int n, src, dst;
    int head[N], dest[M], flow[M], next[M], info[M], etot;
    int cur[N], dep[N], qu[N], bg, ed;
    void init( int n ) {
        this->n = n;
        memset( head, -1, sizeof(head) );
        etot = 0;
    }
    void adde( int i, int u, int v, int f ) {
        info[etot]=i, flow[etot]=f, dest[etot]=v, next[etot]=head[u]; head[u]=etot++;
        info[etot]=0, flow[etot]=0, dest[etot]=u, next[etot]=head[v]; head[v]=etot++;
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
                    dep[v]=dep[u]+1;
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
    int maxflow( int s, int t ) {
        int f = 0;
        src = s, dst = t;
        while( bfs() ) {
            memcpy( cur, head, sizeof(cur) );
            f += dfs(src,oo);
        }
        return f;
    }
}dinic;
struct Btop {
    int n;
    int head[N], dest[M], bval[M], tval[M], next[M], info[M], etot;
    int sumi[N], sumo[N];
    void init( int n ) {
        etot = 0;
        memset( head, -1, sizeof(head) );
        this->n = n;
    }
    void adde( int i, int u, int v, int b, int t ) {
        info[etot]=i, bval[etot]=b, tval[etot]=t;
        dest[etot]=v, next[etot]=head[u];
        sumi[v]+=b, sumo[u]+=b;
        head[u] = etot++;
    }
    int minflow( int src, int dst ) {
        int ss=n+1, tt=n+2, sum;
        dinic.init( n+2 );
        for( int u=1; u<=n; u++ )
            for( int t=head[u]; t!=-1; t=next[t] ) {
                int v=dest[t];
                dinic.adde( info[t], u, v, tval[t]-bval[t] );
            }
        sum = 0;
        for( int u=1; u<=n; u++ ) {
            if( sumi[u]>sumo[u] ) {
                dinic.adde( 0, ss, u, sumi[u]-sumo[u] );
                sum += sumi[u]-sumo[u];
            } else if( sumo[u]>sumi[u] ) {
                dinic.adde( 0, u, tt, sumo[u]-sumi[u] );
            }
        }
        int f = 0;
        f += dinic.maxflow(ss,tt);
        dinic.adde( 0, dst, src, oo );
        f += dinic.maxflow(ss,tt);
        if( f!=sum ) return -1;
        int eid = dinic.etot-2;
        return dinic.flow[eid^1];
    }
}btop;

int n, m;
int ans[M], tot;

int main() {
    scanf( "%d%d", &n, &m );
    btop.init( n );
    for( int i=1,u,v,z,c; i<=m; i++ ) {
        scanf( "%d%d%d%d", &u, &v, &z, &c );
        if( c==1 ) btop.adde( i, u, v, z, z );
        else btop.adde( i, u, v, 0, z );
        ans[i] = c ? z : 0;
    }
    int minf = btop.minflow(1,n);
    if( minf==-1 ) {
        printf( "Impossible\n" );
        return 0;
    }
    for( int e=0; e<dinic.etot; e++ ) {
        int i=dinic.info[e];
        if( i ) ans[i] += dinic.flow[e^1];
    }
    printf( "%d\n", minf );
    for( int i=1; i<=m; i++ )
        printf( "%d ", ans[i] );
    printf( "\n" );
}

