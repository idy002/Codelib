//ะกล๓ำับอถþฒๆส๗
//Nlog^2N
#include <cstdio>
#include <algorithm>
#define FOR(i,j,k) for(i=j;i<=k;++i)
#define rep(i,j,k) for(i=j;i<k;++i)
#define gmod(i) (((i)%mod+mod)%mod)
const int N = 262144, mod = 998244353, inv2 = 499122177;
using namespace std;
typedef long long ll;
ll qpow(ll x, int y) {
    ll z = 1;
    for (; y; x = x * x % mod, y /= 2)
        if (y & 1) z = z * x % mod;
    return z;
}
namespace NTT {
    int n, rev[N], inv_n, m = -1;
    void init(int c) {
        int k = -1, i;
        if (m == c) return; else m = c;
        for (n = 1; n <= m; n <<= 1) ++k;
        inv_n = qpow(n, mod - 2);
        rep(i,0,n) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
    }
    void ntt(int *a, int f) {
        int h, i, j;
        rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (h = 2; h <= n; h *= 2) {
            int wn = qpow(3, (mod - 1) / h);
            for (i = 0; i < n; i += h) {
                int w = 1;
                rep(j,0,h/2) {
                    int u = a[i + j], t = 1ll * a[i + j + h / 2] * w % mod;
                    a[i + j + h / 2] = (u - t + mod) % mod;
                    a[i + j] = (u + t) % mod;
                    w = 1ll * w * wn % mod;
                }
            }
        }
        if (f) {
            rep(i,1,n/2) swap(a[i], a[n - i]);
            rep(i,0,n) a[i] = 1ll * a[i] * inv_n % mod;
        }
    }
}
void inv(int *a, int *b, int n) {
    static int t[N];
    int i;
    if (n == 1) { b[0] = qpow(a[0], mod - 2); return; }
    inv(a, b, n / 2);
    rep(i,0,n) t[i] = a[i]; rep(i,n,2*n) t[i] = 0;
    NTT::init(n);
    NTT::ntt(t, 0); NTT::ntt(b, 0);
    rep(i,0,NTT::n) t[i] = (ll) b[i] * gmod(2ll - (ll) t[i] * b[i] % mod) % mod;
    NTT::ntt(t, 1);
    rep(i,0,n) b[i] = t[i]; rep(i,n,2*n) b[i] = 0;
}
void sqrt(int *a, int *b, int n) {
    static int t[N], b1[N];
    if (n == 1) { b[0] = 1; return; }
    int i;
    sqrt(a, b, n / 2);
    rep(i,0,n) b1[i] = 0;
    inv(b, b1, n);
    rep(i,0,n) t[i] = a[i]; rep(i,n,2*n) t[i] = 0;
    NTT::init(n);
    NTT::ntt(t, 0), NTT::ntt(b, 0), NTT::ntt(b1, 0);
    rep(i,0,NTT::n) t[i] = inv2 * ((b[i] + (ll) b1[i] * t[i] % mod) % mod) % mod;
    NTT::ntt(t, 1);
    rep(i,0,n) b[i] = t[i]; rep(i,n,2*n) b[i] = 0;
}
int main() {
    static int c[N], sc[N], ic[N];
    int i, x, n, m, l;
    scanf("%d%d", &n, &m);
    FOR(i,1,n) scanf("%d", &x), ++c[x];
    c[0] = gmod(1 - c[0]);
    FOR(i,1,m) c[i] = gmod(-4 * c[i]);
    for (l = 1; l <= m; l <<= 1);
    sqrt(c, sc, l);
    (++sc[0]) %= mod;
    inv(sc, ic, l);
    FOR(i,0,m) ic[i] = 2ll * ic[i] % mod;
    FOR(i,1,m) printf("%d\n", ic[i]);
    return 0;
}
