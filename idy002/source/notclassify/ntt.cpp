#include <bits/stdc++.h>
using namespace std;

struct NTT {
	int mod, g, maxp;
	int w[33], rw[33], rb[33];

	vector<int> pfactor(int a) {
		if(a <= 1) return vector<int>();
		vector<int> pfac;
		for(int d = 2; d * d <= a; d++) {
			if(a % d == 0) {
				pfac.push_back(d);
				do a /= d;
				while(a % d == 0);
			}
		}
		if(a != 1) pfac.push_back(a);
		return pfac;
	}
	int findroot(int mod) {
		if(mod == 2) return 1;
		vector<int> pfac = pfactor(mod - 1);
		for(int g = 2; ; g++) {
			bool ok = true;
			for(int p : pfac) {
				if(mpow(g, (mod - 1) / p, mod) == 1) {
					ok = false;
					break;
				}
			}
			if(ok) return g;
		}
	}
	int mpow(int a, int b, int mod) {
		int rt;
		for(rt = 1; b; b>>=1,a=(1LL*a*a)%mod)
			if(b & 1) rt=(1LL*rt*a)%mod;
		return rt;
	}
	void setmod(int m) {
		mod = m;
		g = findroot(mod);
		maxp = 0;
		for(int t = mod - 1; (t & 1) == 0; t >>= 1)
			maxp++;
		w[maxp] = mpow(g, (mod - 1) / (1 << maxp), mod);
		for(int p = maxp - 1; p >= 0; p--)
			w[p] = 1LL * w[p + 1] * w[p + 1] % mod;
		for(int p = 0; p <= maxp; p++) {
			rw[p] = mpow(w[p], mod - 2, mod);
			rb[p] = mpow(1<<p, mod - 2, mod);
		}
	}
	NTT() {}
	int reverse(int pmax, int a) {
		int b = 0;
		for( int i=0; i<pmax; i++ ) 
			if( a&(1<<i) ) b |= 1<<(pmax-1-i);
		return b;
	}
	void ntt(vector<int> &a, int pmax, bool r) {
		int n = (int)a.size();
		for(int i=0,j=0; i<n; i++){
			if(i>j) swap(a[i],a[j]);
			for(int l=n>>1;(j^=l)<l;l>>=1);
		}
		/*
		for(int i = 0; i < n; i++) {
			int j = reverse(pmax, i);
			if(i < j) swap(a[i], a[j]);
		}
		*/
		for(int p = 1; p <= pmax; p++) {
			for(int i = 0; i < n; i += (1<<p)) {
				int wo, wk;
				int l = 1<<(p-1);
				if(!r) wo = w[p];
				else wo = rw[p];
				wk = w[0];
				for(int j = 0; j < l; j++,wk=1LL*wk*wo%mod) {
					int lf = a[i+j], rg = a[i+j+l];
					int val = 1LL * wk * rg % mod;
					a[i+j] = (lf + val) % mod;
					a[i+j+l] = (lf + mod - val) % mod;
				}
			}
		}
		if(r) for(int i = 0; i < n; i++) 
			a[i] = 1LL * a[i] * rb[pmax] % mod;
	}
	vector<int> multiply(vector<int> ca, vector<int> cb) {
		int pmax;
		for( pmax = 0; ca.size() > (1u<<pmax) || cb.size() > (1u<<pmax); pmax++ );
		pmax++;
		if(pmax > maxp) { assert("check this" == 0); }
		vector<int> cc;
		ca.resize(1<<pmax);
		cb.resize(1<<pmax);
		cc.resize(1<<pmax);
		ntt( ca, pmax, 0 );
		ntt( cb, pmax, 0 );
		for( int t = 0; t < (int)cc.size(); t++ ) 
			cc[t] = 1LL * ca[t] * cb[t] % mod;
		ntt( cc, pmax, 1 );
		return cc;
	}
}ntt;

int main() {
	int n, m;
	vector<int> a, b, c;
	scanf("%d%d", &n, &m);
	a.resize(n + 1);
	b.resize(m + 1);
	for(int i = 0; i <= n; i++) 
		scanf("%d", &a[i]);
	for(int i = 0; i <= m; i++)
		scanf("%d", &b[i]);
	ntt.setmod((479<<21) + 1);
	c = ntt.multiply(a,b);
	for(int i = 0; i <= n + m; i++)
		printf("%d%c", c[i], " \n"[i == n + m]);
}



