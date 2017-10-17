/**************************************************************
 * 求满足a^x = b (mod c)的最小的非负整数．
 * 不要求gcd(a,c) = 1．
 ****************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

typedef long long dnt;
namespace Task {
	const int mod = 38281;
	const int len = mod<<3;
	struct Hash {
		int head[mod], val[len], rat[len], next[len], ntot;
		void init() { 
			ntot=0; 
			memset( head, 0, sizeof(head) );
		}
		void insert( int v, int r ) {
			int k = v % mod;
			ntot++;
			next[ntot] = head[k];
			val[ntot] = v;
			rat[ntot] = r;
			head[k] = ntot;
		}
		int query( int v ) {
			int k = v % mod;
			for( int t=head[k]; t; t=next[t] ) 
				if( val[t]==v ) return rat[t];
			return -1;
		}
	}hash;

	dnt gcd( dnt a, dnt b ) {
		return b ? gcd(b,a%b) : a;
	}
	void exgcd( dnt a, dnt b, dnt &d, dnt &x, dnt &y ) {
		if( b==0 ) {
			x=1, y=0, d=a;
		} else {
			exgcd(b,a%b,d,y,x);
			y-=a/b*x;
		}
	}
	dnt inv( int a, int n ) {
		dnt d, x, y;
		exgcd(a,n,d,x,y);
		return d==1 ? (x%n+n)%n : -1;
	}
	int bsgs( dnt s, dnt a, dnt b, dnt c ) {
		hash.init();
		int m = ceil(sqrt(c));
		for( int i=0; i<m; i++ ) {
			if( s==b ) return i;
			hash.insert( s, i );
			s = s*a % c;
		}
		dnt am = 1;
		for( int i=0; i<m; i++ )
			am = am*a % c;
		am = inv(am,c);
		b = b*am % c;
		for( int i=m; i<c; i+=m ) {
			int j = hash.query( b );
			if( j!=-1 ) return i+j;
			b = b*am % c;
		}
		return -1;
	}
	int exbsgs( dnt a, dnt b, dnt c ) {
		dnt s = 1;
		for( int i=0; i<32; i++ ) {
			if( s==b ) return i;
			s = s*a % c;
		}
		dnt cd;
		s = 1;
		int rt = 0;
		while( (cd=gcd(a,c))!=1 ) {
			rt++;
			s*=a/cd;
			if( b%cd ) return -1;
			b/=cd;
			c/=cd;
			s%=c;
		}
		int p = bsgs(s,a,b,c);
		if( p==-1 ) return -1;
		return rt + p;
	}
	void sov( dnt a, dnt b, dnt c ) {
		int res = exbsgs(a,b,c);
		if( res==-1 ) printf( "Math Error\n" );
		else printf( "%d\n", res );
	}
};

int main() {
	dnt a, b, c;
	std::cin >> a >> b >> c;
	Task::sov( a, b, c );
}

