/*
学习了元根的一些知识，哈哈。

总结一下：

几个概念：

阶：对于模数m和整数a，并且gcd(m,a)==1，那么定义a在模m下的阶r为满足ar=1 mod m的最小正整数。

性质1：r in [1,phi(m)]   (由欧拉定理）

性质2：r | phi(m)  ( a^r=a^phi(m) mod m，然后用反证法)

性质3：r 是整数a模m的阶当且仅当满足：1）a^r=1 mod m   2) a^(r/p(r)) ≠ 1 mod m (后面推前面也用反正法）。

元根：

如果对于一个模数m，存在一个数a，满足a在模m下的阶是phi(m)，那么就称a是模数m的一个元根。

性质：所有质数有元根（更一般的，2,4,pe,2pe有元根，p是奇质数）

元根应用

元根依靠离散对数，将对数运算引入了模数的缩系下。从而可以解决很多数论中关于指数的问题。

ind a = ind b mod phi(m) <=> a = b mod m

ind a^k = k ind a mod phi(m)

ind ab = ind a + ind b mod phi(m)
*/


/**************************************************************
    Problem: 3285
    User: idy002
    Language: C++
    Result: Accepted
    Time:756 ms
    Memory:32072 kb
****************************************************************/
 
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#define N 1000010
 
typedef long long dnt;
 
const int Hmod = 60793;
struct Hash {
    int head[N], key[N], val[N], next[N], etot;
    void init() {
        etot = 0;
        memset( head, 0, sizeof(head) );
    }
    void insert( int k, int v ) {
        int kk = k%Hmod;
        etot++;
        key[etot] = k;
        val[etot] = v;
        next[etot] = head[kk];
        head[kk] = etot;
    }
    int query( int k ) {
        int kk = k%Hmod;
        for( int t=head[kk]; t; t=next[t] )
            if( key[t]==k ) return val[t];
        return -1;
    }
}hash;
 
dnt mpow( dnt a, int b, int c ) {
    dnt rt;
    for( rt=1; b; b>>=1,a=(a*a)%c )
        if( b&1 ) rt=(rt*a)%c;
    return rt;
}
int findroot( int p ) {
    int phi = p-1;
    int tmp = phi;
    int stk[50], top;
    top = 0;
    for( int i=2; i<=(1<<16); i++ ) {
        if( tmp%i==0 ) {
            stk[++top] = i;
            do {
                tmp/=i;
            }while( tmp%i==0 );
        }
    }
    if( tmp!=1 ) 
        stk[++top] = tmp;
    for( int r=1; ; r++ ) {
        bool ok = true;
        for( int i=1; i<=top; i++ ) {
            if( mpow(r,phi/stk[i],p)==1 ) {
                ok=false;
                break;
            }
        }
        if( ok ) return r;
    }
}
dnt ind( dnt r, int a, int p ) {    //  ind_r(a) mod p-1
    int m = ceil(sqrt(p-1));
    hash.init();
    dnt cur = 1;
    for( int i=0; i<m; i++ ) {
        if( cur==a ) return i;
        hash.insert( cur, i );
        cur = (cur*r) % p;
    }
    dnt base;
    base = cur = mpow(cur,p-2,p);
    for( int i=m; i<p; i+=m,cur=(cur*base)%p ) {
        int j = hash.query( a*cur%p );
        if( j!=-1 ) return i+j;
    }
    return -1;  //  impossible
}
dnt gcd( dnt a, dnt b ) {
    return b ? gcd(b,a%b) : a;
}
void exgcd( dnt a, dnt b, dnt &d, dnt &x, dnt &y ) {
    if( b==0 ) {
        d=a, x=1, y=0;
    } else {
        exgcd(b,a%b,d,y,x);
        y-=a/b*x;
    }
}
dnt meq( dnt a, dnt b, dnt c ) {    //  ax=b mod c
    dnt d, dd, x, y;
    a = (a%c+c)%c;
    b = (b%c+c)%c;
    d = gcd(a,c);
    if( b%d!=0 ) return -1;
    exgcd(a/d,c/d,dd,x,y);
    x = x*(b/d);
    x = (x%(c/d)+(c/d))%(c/d);
    if( x==0 ) x+=c/d;
    return x;
}
 
dnt a, b, c, g, p, r;
int aa[N], bb[N], cc[N], gg[N];
 
void read( int a[] ) {
    int i;
    char ch;
    for( i=0; isdigit(ch=getchar()); i++ )
        a[i] = ch-'0';
    a[i] = -1;
}
dnt modulo( int a[], dnt mod ) {
    dnt rt = 0;
    for( int i=0; a[i]!=-1; i++ )
        rt = (rt*10 + a[i]) % mod;
    return rt;
}
int main() {
    read(aa); 
    read(bb); 
    read(cc); 
    read(gg);
    scanf( "%lld", &p );
    a = modulo(aa,p-1); 
    b = modulo(bb,p-1),
    c = modulo(cc,p); 
    g = modulo(gg,p);
 
    if( g%p==0 || c%p==0 ) {
        if( g%p==0 && c%p==0 ) 
            printf( "1\n" );
        else
            printf( "no solution\n" );
        return 0;
    }
    r = findroot(p);
//  fprintf( stderr, "%d\n", (int)r );
    dnt ans = meq( a*ind(r,g,p), ind(r,c,p)-b*ind(r,g,p), p-1 );
    if( ans<0 ) 
        printf( "no solution\n" );
    else
        printf( "%lld\n", ans );
}
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long dnt;

const int mod = 8543;
const int elen = 100010;
struct Hash {
    int head[mod], val[elen], rat[elen], next[elen], etot;
    void init() {
        memset( head, 0, sizeof(head) );
        etot = 0;
    }
    void insert( int v, int r ) {
        int k = v % mod;
        etot++;
        next[etot] = head[k];
        rat[etot] = r;
        val[etot] = v;
        head[k] = etot;
    }
    int query( int v ) {
        int k = v % mod;
        for( int t=head[k]; t; t=next[t] ) 
            if( val[t]==v ) return rat[t];
        return -1;
    }
}hash;

int p, a, k;
int g, b;
vector<int> stk;

dnt mpow( dnt a, int b, int m ) {
    dnt rt;
    for( rt=1; b; b>>=1,a=(a*a)%m )
        if( b&1 ) rt=(rt*a)%m;
    return rt;
}
void exgcd( int a, int b, int &d, dnt &x, dnt &y ) {
    if( b==0 ) d=a, x=1, y=0;
    else {
        exgcd( b, a%b, d, y, x );
        y-=a/b*x;
    }
}
int gcd( int a, int b ) {
    return b ? gcd(b,a%b) : a;
}
int findroot( int n ) {        //    n is prime
    if( n==2 ) return 1;

    vector<int> pfac;
    int maxi = (int)ceil(sqrt(n-1));
    int remain=n-1;
    for( int i=2; i<=maxi; i++ ) {
        if( remain%i==0 ) {
            pfac.push_back(i);
            while( remain%i==0 ) 
                remain/=i;
        }
    }
    if( remain!=1 ) pfac.push_back( remain );
    for( int i=1; ; i++ ) {
        bool ok = true;
        for( int t=0; t<pfac.size(); t++ ) 
            if( mpow(i,(n-1)/pfac[t],n)==1 ) {
                ok = false;
                   break;
            }
        if( ok ) return i;
    }
}
dnt inv( int a, int n ) {
    return mpow(a,n-2,n);
}
dnt ind( int g, int b, int n ) {    //    n is prime, g is root, return v in [0,n-1]
    hash.init();
    int m = (int)ceil(sqrt(n-1));
    dnt s = 1;
    for( int i=0; i<m; i++ ) {
        if( s==b ) return i;
        hash.insert( s, i );
        s = (s*g) % n;
    }
    int am = s;
    s = b;
    for( int i=m,j; i<n; i+=m ) {
        s = (s*inv(am,n)) % n;
        if( (j=hash.query(s))!=-1 )
            return i+j;
    }
    return -1;    //    impossible
}
void meq( int a, int b, int m ) {
    stk.clear();
    int d = gcd(a,m);
    if( b%d ) return;
    int aa=a/d, bb=b/d, mm=m/d, dd;
    dnt x0, y0;
    exgcd( aa, mm, dd, x0, y0 );
    x0 = (x0%mm+mm)%mm;
    for( dnt k=0; k<d; k++ ) 
        stk.push_back( (x0*bb+k*mm)%m );
}

int main() {
    scanf( "%d%d%d", &p, &k, &a );    //    x^k = a mod p
    if( a==0 ) {
        printf( "1\n0 \n" );
        return 0;
    }
    //    find the root of p: g
    g = findroot(p);
    //    ind a: b
    b = ind( g, a, p );
    //    kx=b mod phi(p)
    meq( k, b, p-1 );
    //    decode
    for( int t=0; t<stk.size(); t++ )
        stk[t] = mpow( g, stk[t], p );
    sort( stk.begin(), stk.end() );
    //    output
    printf( "%d\n", stk.size() );
    for( int t=0; t<stk.size(); t++ )
        printf( "%d ", stk[t] );
    printf( "\n" );
}
