/**************************************************************
    Problem: 2179
    User: idy002
    Language: C++
    Result: Accepted
    Time:1300 ms
    Memory:10104 kb
****************************************************************/
 
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
 
typedef long long dnt;
 
const double eps = 1e-10;
const double dpi = 2*acos(-1);
const int N = (1<<17)+10;
const int P = 17;
 
struct Plex {
    double x, y;
    Plex(){}
    Plex( double x, double y ):x(x),y(y){}
};
Plex operator-( const Plex &a ) {
    return Plex(-a.x,-a.y);
}
Plex operator+( const Plex &a, const Plex &b ) {
    return Plex(a.x+b.x,a.y+b.y);
}
Plex operator-( const Plex &a, const Plex &b ) {
    return Plex(a.x-b.x,a.y-b.y);
}
Plex operator*( const Plex &a, const Plex &b ) {
    return Plex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
 
int n, p;
Plex a[N], b[N], c[N], w[P+1];
Plex d[N];
 
void init() {
    for( int p=0,i=1; p<=P; p++,i<<=1 ) {
        w[p] = Plex(cos(dpi/i),sin(dpi/i));
    }
}
void read( Plex a[N] ) {
    static char buf[N];
    scanf( "%s", buf );
    int len = strlen(buf);
    reverse( buf, buf+len );
    for( int i=0; buf[i]; i++ )
        a[i].x = buf[i]-'0';
}
void print( int n, Plex a[N] ) {
    static int stk[N], top;
    for( int i=0; i<n; i++ ) {
        stk[i] += int(a[i].x+0.49);
        stk[i+1] += stk[i]/10;
        stk[i] %= 10;
    }
    top = n-1;
    while( top>=1 && stk[top]==0 ) top--;
    if( top==0 ) {
        printf( "0\n" );
    } else {
        for( int i=top; i>=0; i-- )
            printf( "%d", stk[i] );
        printf( "\n" );
    }
}
int reverse( int a ) {
    int b = 0;
    for( int i=0; i<p; i++ ) 
        if( a&(1<<i) ) b |= 1<<(p-1-i);
    return b;
}
void fft( Plex a[N], bool r ) {
    for( int i=0; i<n; i++ ) {
        int j=reverse(i);
        if( i<j ) swap(a[i],a[j]);
    }
    for( int p=1; p<=::p; p++ ) {
        for( int i=0; i<n; i+=(1<<p) ) {
            Plex wo, wk;
            int l = 1<<(p-1);
            if( !r ) wo = w[p];
            else wo = Plex(w[p].x,-w[p].y);
            wk = w[0];
            for( int j=0; j<l; j++,wk=wk*wo ) {
                Plex lf = a[i+j], rg = a[i+j+l];
                a[i+j] = lf + wk*rg;
                a[i+j+l] = lf - wk*rg;
            }
        }
    }
    if( r ) for( int i=0; i<n; i++ ) 
            a[i].x /= n;
}
int main() {
    scanf( "%d", &n );
    read(a);
    read(b);
    for( p=0; (1<<p)<n; p++ );
    p++;
    n = 1<<p;
    init();
    fft(a,0);
    fft(b,0);
    for( int i=0; i<n; i++ )
        c[i] = a[i]*b[i];
    fft(c,1);
    print(n,c);
}
