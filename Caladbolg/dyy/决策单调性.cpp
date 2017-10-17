/*
决策单调性，对于一个1D/1D（状态是一维，转移也是一维）的DP，如果DP的决策具有单调性，那么就可以做到O(nlogn)的复杂度完成DP。
*/

/**************************************************************
    Problem: 2216
    User: idy002
    Language: C++
    Result: Accepted
    Time:4916 ms
    Memory:14476 kb
****************************************************************/
 
#include <cstdio>
#include <algorithm>
#include <cmath>
#define N 500010
using namespace std;
 
struct Trid {
    int p, l, r;
    Trid(){}
    Trid( int p, int l, int r ):p(p),l(l),r(r){}
};
 
int n;
int aa[N];
int f[N], g[N], h[N];
Trid stk[N]; int top;
 
double calc( int j, int i ) {
    return aa[j]-aa[i]+sqrt(abs(i-j));
}
void dodp( int dp[N] ) {
    stk[top=1] = Trid(1,1,n);
    for( int i=2; i<n; i++ ) {
        if( calc(stk[top].p,n)>calc(i,n) ) continue;
         
        while( stk[top].l>=i && 
                calc(stk[top].p,stk[top].l)<calc(i,stk[top].l) )
            top--;
        if( stk[top].r==i-1 ) {
            stk[++top] = Trid( i, i, n );
        } else {
            int lf = max( stk[top].l+1, i );
            int rg = min( stk[top].r+1, n );
            int p = stk[top].p;
            while( lf<rg ) {
                int mid=(lf+rg)>>1;
                if( calc(p,mid) > calc(i,mid) ) lf=mid+1;
                else rg=mid;
            }
            stk[top].r = lf-1;
            stk[++top] = Trid( i, lf, n );
        }
    }
    for( int i=1; i<=top; i++ ) 
        for( int j=stk[i].l; j<=stk[i].r; j++ )
            dp[j] = stk[i].p;
}
int main() {
    scanf( "%d", &n );
    for( int i=1; i<=n; i++ )
        scanf( "%d", aa+i );
    dodp(f);
    reverse( aa+1, aa+1+n );
    dodp(g);
    reverse( aa+1, aa+1+n );
 
    for( int i=1; i<=n; i++ ) 
        g[i] = n+1-g[i];
    reverse( g+1, g+1+n );
 
    for( int i=1; i<=n; i++ )
        if( calc(f[i],i)>calc(g[i],i) ) h[i]=f[i];
        else h[i]=g[i];
    for( int i=1; i<=n; i++ )
        printf( "%lld\n", (long long)ceil(calc(h[i],i)) );
}
