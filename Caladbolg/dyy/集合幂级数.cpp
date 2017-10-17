#include <cstdio>

const int N = 10;

int n, U;
int a[1<<N], b[1<<N], c[1<<N];

void trans( int a[], int flag ) {
    for( int b=0; b<n; b++ ) {
        int u = U ^ (1<<b);
        for( int s=u,t=1<<(n-1); t; s=(s-1)&u,t-- ) {
            int l=a[s], r=a[s|(1<<b)];
            /*
            NOT AND
            if( flag==1 ) {
                a[s] = l+r;
                a[s|(1<<b)] = r;
            } else {
                a[s] = r;
                a[s|(1<<b)] = l-r;
            }
             */
            /*
            NOT XOR
            if( flag==1 ) {
                a[s] = l+r;
                a[s|(1<<b)] = l-r;
            } else {
                a[s] = (l-r)/2;
                a[s|(1<<b)] = (l+r)/2;
            }
             */
            /*
            NOT OR
            if( flag==1 ) {
                a[s] = l;
                a[s|(1<<b)] = l+r;
            } else {
                a[s] = r-l;
                a[s|(1<<b)] = l;
            }
            */
            /*
            OR
            if( flag==1 ) {
                a[s] = l;
                a[s|(1<<b)] = l+r;
            } else {
                a[s] = l;
                a[s|(1<<b)] = r-l;
            }
            */
            /*
            AND
            if( flag==1 ) {
                a[s] = l+r;
                a[s|(1<<b)] = r;
            } else {
                a[s] = l-r;
                a[s|(1<<b)] = r;
            }
            */
            /*
            XOR
            if( flag==1 ) {
                a[s] = l+r;
                a[s|(1<<b)] = l-r;
            } else {
                a[s] = (l+r)/2;
                a[s|(1<<b)] = (l-r)/2;
            }
            */
        }
    }
}
int main() {
    scanf( "%d", &n );
    U = (1<<n)-1;
    for( int i=0; i<=U; i++ )
        scanf( "%d", a+i );
    for( int i=0; i<=U; i++ )
        scanf( "%d", b+i );
    trans(a,1);
    trans(b,1);
    for( int s=0; s<=U; s++ )
        c[s] = a[s]*b[s];
    trans(c,-1);
    for( int s=0; s<=U; s++ )
        printf( "%d ", c[s] );
    printf( "\n" );
}
