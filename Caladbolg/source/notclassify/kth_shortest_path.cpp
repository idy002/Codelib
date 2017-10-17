#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int N = 1010;
const int M = 100010;
const int oo = 0x3f3f3f3f;

struct Elist {
	int _head[N], _dest[M], _dist[M], _last[M], etot;
	inline void adde( int u, int v, int d ) {
		etot++;
		_dest[etot] = v;
		_dist[etot] = d;
		_last[etot] = _head[u];
		_head[u] = etot;
	}
	inline int head( int u ) { return _head[u]; }
	inline int dest( int t ) { return _dest[t]; }
	inline int dist( int t ) { return _dist[t]; }
	inline int last( int t ) { return _last[t]; }
};
struct Stat {
	int u, d;
	Stat(){}
	Stat( int u, int d ):u(u),d(d){}
};

int n, m, K;
Elist e, re;
int src, dst;
int rdis[N];
bool done[N];

bool operator<( const Stat &r, const Stat &s ) {
	return r.d + rdis[r.u] > s.d + rdis[s.u];
}
void dijkstra() {
	memset( done, false, sizeof(done) );
	memset( rdis, 0x3f, sizeof(rdis) );
	priority_queue<pair<int,int> > Q;
	Q.push( make_pair(0,dst) );
	rdis[dst] = 0;
	while( !Q.empty() ) {
		int u = Q.top().second;
		Q.pop();
		if( done[u] ) continue;
		done[u] = true;
		for( int t = re.head(u); t; t = re.last(t) ) {
			int v = re.dest(t), d = re.dist(t);
			if( done[v] ) continue;
			if( rdis[v] > rdis[u] + d ) {
				rdis[v] = rdis[u] + d;
				Q.push( make_pair( -rdis[v], v ) );
			}
		}
	}
}
int astar() {
	int pcnt = 0;
	priority_queue<Stat> Q;

	if( rdis[src] == oo ) return -1;
	if( src == dst ) K++;
	Q.push( Stat( src, 0 ) );
	while( !Q.empty() ) {
		Stat s = Q.top();
		Q.pop();
		if( s.u == dst ) {
			pcnt++;
			if( pcnt == K ) 
				return s.d;
		}
		for( int t = e.head(s.u); t; t = e.last(t) ) {
			int v = e.dest(t), d = e.dist(t);
			if( rdis[v] == oo ) continue;
			Q.push( Stat( v, s.d + d ) );
		}
	}
	return -1;
}
int main() {
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i++ ) {
		int u, v, d;
		scanf( "%d%d%d", &u, &v, &d );
		e.adde( u, v, d );
		re.adde( v, u, d );
	}
	scanf( "%d%d%d", &src, &dst, &K );
	dijkstra();
	printf( "%d\n", astar() );
}
