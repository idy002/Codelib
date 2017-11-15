struct Rectangle
{
	double lx,rx,ly,ry;
	inline Rectangle() = default;
	inline Rectangle(double _lx,double _rx,double _ly,double _ry):lx(_lx),rx(_rx),ly(_ly),ry(_ry) {}
	inline void set(const Point &p) { lx = rx = p.x; ly = ry = p.y; }
	inline void merge(const Point &p)
	{
		lx = min(lx,p.x); rx = max(rx,p.x);
		ly = min(ly,p.y); ry = max(ry,p.y);
	}
	inline void merge(const Rectangle &r)
	{
		lx = min(lx,r.lx); rx = max(rx,r.rx);
		ly = min(ly,r.ly); ry = max(ry,r.ry);
	}
	// 最小距离，到4个角和4条边距离
	inline double dist(const Point &p) { }
	// 最大距离，到4个角的距离
	inline double dist(const Point &p)
	{ }
};

struct Node
{
	int child[2]; Point p; Rectangle r;
	inline Node() = default;
	inline Node(const Point &_p,const Rectangle &_r):p(_p),r(_r) { r.set(p); memset(child,0,8); }
	inline void set(const Point &_p) { p = _p; r.set(p); memset(child,0,8); }
}tree[maxn];

inline bool cmpx(const Point &a,const Point &b)
{
	if (a.x != b.x) return a.x < b.x;
	else return a.y < b.y;
}
inline bool cmpy(const Point &a,const Point &b)
{
	if (a.y != b.y) return a.y < b.y;
	else return a.x < b.x;
}

inline bool cmp(pair <double,int> a,pair <double,int> b)
{
	int sgn = dcmp(a.first-b.first);
	if (sgn) return sgn < 0;
	else return a.second < b.second;
}	

inline int build(int l,int r,bool dim)
{
	int now = ++size,mid = (l+r)>>1;
	nth_element(vec.begin()+l-1,vec.begin()+mid-1,vec.begin()+r,dim?cmpx:cmpy);
	tree[now].set(vec[mid-1]);
	if (l < mid)
	{
		tree[now].child[0] = build(l,mid-1,dim^1);
		tree[now].r.merge(tree[tree[now].child[0]].r);
	}
	if (r > mid)
	{
		tree[now].child[1] = build(mid+1,r,dim^1);
		tree[now].r.merge(tree[tree[now].child[1]].r);
	}
	return now;
}
