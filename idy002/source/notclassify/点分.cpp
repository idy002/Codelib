/*　1.  关于重心, 对于一个无向图, 我们这样给每条边重新确定方向: u<->v这条边将原图分成两个部分Su,Sv,w(S)表示S集合中点的权值和,那么

　　　　　u->v 当 w(Su)<w(Sv)

　　　　　u<-v 当 w(Su)>w(Sv)

　　　　　u<->v 当 w(Su)=w(Sv)

　　　　　那么从一个点沿着边的方向走,直到走到一个区域,使得走不出这个区域,那么这个区域中的任何一个点就是重心.

　　2. 有了第一条,就可以运用点分来搞一些询问某个点的的东西了(这里就是询问以这个点为重心的权和).

　　　 再用点分最多log层和类似1的性质,就可以做了.

　　3. 点分不擅长求全局最...的东西,而是擅长关于某个点....的东西.

　　　　这道题可以用是因为有重心位置的单调性.

　　　　还有捉迷藏那道题是用堆来辅助的.


*/

#include <cstdio>
#include <vector>
#include <map>
#define max(a,b) ((a)>(b)?(a):(b))
#define oo 0x3f3f3f3f3f3f3f3fLL
#define N 100010
#define M N<<1
#define P 17
using namespace std;

typedef long long dnt;
struct Info {
    int p, s;
    Info(){}
    Info( int p, int s ):p(p),s(s){}
};
struct Pair {
    int s, c;
    Pair(){}
    Pair( int s, int c ):s(s),c(c){}
};

int n, m;
int head[N], dest[M], wght[M], next[M], etot;
int idv[M], vid[N], dep[N], stu[M][P+1], stp[M][P+1];
int bac[N], fat[N], siz[N], vis[N], dis[N];
int bin[P+1], log[M], qu[N], bg, ed;
//Info info[N][P+1]; int icnt[N];
//Pair gc[N][22]; int gcnt[N];
vector<Info> info[N];
vector<Pair> gc[N];
dnt cans[N], fans[N], sumw[N];
dnt rans[N]; int tag[N], curt;

inline void uMax( int &u, int v ) { if( u<v ) u=v; }
void adde( int u, int v, int w ) {
    etot++;
    dest[etot] = v;
    wght[etot] = w;
    next[etot] = head[u];
    head[u] = etot;
}
void build_lca( int s ) {
    //    qu fat dep dis, siz
    fat[s] = 0;
    dep[s] = 1;
    dis[s] = 0;
    siz[s] = 0;
    qu[bg=ed=1] = s;
    while( bg<=ed ) {
        int u=qu[bg++];
        for( int t=head[u]; t; t=next[t] ) {
            int v=dest[t], w=wght[t];
            if( v==fat[u] ) continue;
            fat[v] = u;
            siz[v] = 0;
            dep[v] = dep[u]+1;
            dis[v] = dis[u]+w;
            qu[++ed] = v;
        }
    }
    //    siz
    for( register int i=ed; i>=2; i-- ) {
        int u=qu[i], p=fat[u];
        siz[u]++;
        siz[p]+=siz[u];
    }
    siz[s]++;
    //    idv vid
    vid[s] = 1;
    idv[1] = s;
    for( register int i=1; i<=ed; i++ ) {
        int u=qu[i];
        int cur=vid[u]+1;
        for( register int t=head[u]; t; t=next[t] ) {
            int v=dest[t];
            if( v==fat[u] ) continue;
            idv[cur] = u;
            cur++;
            vid[v] = cur;
            idv[cur] = v;
            cur += siz[v]+siz[v]-1;
        }
    }
    idv[n+n] = s;
    //    bin log
    int idc = n+n;
    bin[0] = 1;
    for( int i=1; i<=P; i++ ) bin[i] = bin[i-1]<<1;
    log[0] = -1;
    for( int i=1; i<=idc; i++ ) log[i] = log[i>>1]+1;
    //    stu stp
    for( int i=1; i<=idc; i++ ) {
        stu[i][0] = idv[i];
        stp[i][0] = dep[idv[i]];
    }
    for( int p=1; p<=log[idc]; p++ ) {
        for( register int i=1; i<=idc-bin[p]+1; i++ ) {
            if( stp[i][p-1] < stp[i+bin[p-1]][p-1] ) {
                stp[i][p] = stp[i][p-1];
                stu[i][p] = stu[i][p-1];
            } else {
                stp[i][p] = stp[i+bin[p-1]][p-1];
                stu[i][p] = stu[i+bin[p-1]][p-1];
            }
        }
    }
}
inline int lca( int u, int v ) {
    int lf=vid[u], rg=vid[v];
    if( lf>rg ) swap(lf,rg);
    int p = log[rg-lf+1];
    if( stp[lf][p] < stp[rg-bin[p]+1][p] )
        return stu[lf][p];
    else
        return stu[rg-bin[p]+1][p];
}
inline int qu_dis( int u, int v ) {
    int ca = lca(u,v);
    return dis[u]+dis[v]-(dis[ca]<<1);
}
int build_vdcp( int s ) {
    int c;
    //    qu fat, siz bac
    fat[s] = 0;
    siz[s] = bac[s] = 0;
    qu[bg=ed=1] = s;
    while( bg<=ed ) {
        int u=qu[bg++];
        for( int t=head[u]; t; t=next[t] ) {
            int v=dest[t];
            if( v==fat[u] || vis[v] ) continue;
            fat[v] = u;
            siz[v] = bac[v] = 0;
            qu[++ed] = v;
        }
    }
    //    siz bac
    for( register int i=ed; i>=2; i-- ) {
        int u=qu[i], p=fat[u];
        siz[u]++;
        siz[p]+=siz[u];
        uMax( bac[p], siz[u] );
    }
    siz[s]++;
    //    bac c
    c = 0;
    for( register int i=1; i<=ed; i++ ) {
        int u=qu[i];
        uMax( bac[u], siz[s]-siz[u] );
        if( bac[u]<bac[c] ) c=u;
    }
    //    qu info
    vis[c] = true;
    vector<int> stk;
    for( int t=head[c]; t; t=next[t] ) {
        int s=dest[t], cc;
        if( vis[s] ) continue;

        qu[bg=ed=1] = s;
        fat[s] = c;
        stk.clear();
        while( bg<=ed ) {
            int u=qu[bg++];
            stk.push_back( u );
            for( int t=head[u]; t; t=next[t] ) {
                int v=dest[t];
                if( v==fat[u] || vis[v] ) continue;
                qu[++ed] = v;
                fat[v] = u;
            }
        }
        cc = build_vdcp(s);
        gc[c].push_back(Pair(s,cc));
//        gc[c][gcnt[c]] = Pair(s,cc);
//        gcnt[c]++;
        for( register int t=stk.size()-1; t>=0; t-- )  {
            int u=stk[t];
            info[u].push_back( Info(c,cc) );
//            info[u][icnt[u]] = Info(c,cc);
//            icnt[u]++;
        }
    }
    return c;
}
dnt query( int u ) {
    if( tag[u]==curt ) return rans[u];
    tag[u] = curt;
    dnt rt = cans[u];
    for( int t=0; t<info[u].size(); t++ ) {
//    for( int t=icnt[u]-1; t>=0; t-- ) {
        int p=info[u][t].p, s=info[u][t].s;
        rt += cans[p]-fans[s]+(sumw[p]-sumw[s])*qu_dis(u,p);
    }
    return rans[u]=rt;
}
dnt search( int u ) {
    dnt su = query(u);
    for( int t=0; t<gc[u].size(); t++ ) {
//    for( int t=gcnt[u]-1; t>=0; t-- ) {
        Pair &p = gc[u][t];
        dnt a=query(p.s);
        if( a<su ) return search(p.c);
    }
    return su;
}
void modify( int u, int delta ) {
    sumw[u] += delta;
    for( int t=info[u].size()-1; t>=0; t-- ) {
//    for( int t=icnt[u]-1; t>=0; t-- ) {
        int p=info[u][t].p, s=info[u][t].s;
        dnt d = (dnt)delta*qu_dis(u,p);
        cans[p] += d;
        fans[s] += d;
        sumw[p] += delta;
    }
}
