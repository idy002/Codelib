/**************************************************************
    Problem: 3529
    User: idy002
    Language: C++
    Result: Accepted
    Time:3568 ms
    Memory:3192 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
using namespace std;
 
struct Query {
    int n, m, a, id;
    bool operator<( const Query & b ) const {
        return a<b.a;
    }
};
 
int prm[10000], isnot[100010], mu[100010], f[100010], h[100010], ptot;
int order[100010], cur;
int q, ans[20010];
Query qry[20010];
 
bool cmp( int a, int b ) { return f[a]<f[b]; }
void modify( int pos, int delta ) {
    for( int i=pos; i<=100000; i+=i&-i )
        h[i] += delta;
}
int query( int pos ) {
    int rt = 0;
    for( int i=pos; i; i-=i&-i )
        rt += h[i];
    return rt;
}
void init( int n ) {
    mu[1] = 1;
    for( int i=2; i<=n; i++ ) {
        if( !isnot[i] ) {
            prm[++ptot] = i;
            mu[i] = -1;
        }
        for( int j=1; j<=ptot && i*prm[j]<=n; j++ ) {
            isnot[i*prm[j]] = true;
            if( i%prm[j]==0 ) {
                mu[i*prm[j]] = 0;
                break;
            }
            mu[i*prm[j]] = -mu[i];
        }
    }
    for( int i=1; i<=n; i++ )
        for( int j=i; j<=n; j+=i )
            f[j] += i;
    for( int i=1; i<=n; i++ )
        order[i] = i;
    sort( order+1, order+1+n, cmp );
}
 
int main() {
    init(100000);
    scanf( "%d", &q );
    for( int i=1; i<=q; i++ ) {
        scanf( "%d%d%d", &qry[i].n, &qry[i].m, &qry[i].a );
        if( qry[i].n>qry[i].m ) swap( qry[i].n, qry[i].m );
        qry[i].id = i;
    }
    sort( qry+1, qry+1+q );
    for( int i=1; i<=q; i++ ) {
        while( cur+1<=100000 && f[order[cur+1]]<=qry[i].a ) {
            cur++;
            int j=order[cur];
            for( int k=j; k<=100000; k+=j )
                modify( k, f[j]*mu[k/j] );
        }
        int &tans = ans[qry[i].id];
        int n = qry[i].n, m = qry[i].m;
        for( int j=1; j<=n; j++ ) {
            int jj=min( n/(n/j), m/(m/j) );
            tans += (query(jj)-query(j-1))*(n/j)*(m/j);
            j = jj;
        }
    }
    for( int i=1; i<=q; i++ )
        printf( "%d\n", ans[i]&((1U<<31)-1) );
}
