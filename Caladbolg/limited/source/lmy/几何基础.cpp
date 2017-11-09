//计算几何常用公式
struct Point {	double x,y; inline Point unit() const {
		double len = norm(); if (!dcmp(len)) return Point(1,0); else return *this/len; }
	inline Point reflect(const Point &p) const {
		Point v = *this-p; double len = v.norm();
		v = v/len; return p+v*(1/len); }
	inline Point vertical() const { return Point(y,-x); } 
	inline double angle() const {
		double ret = atan2(y,x); if (ret < 0) ret += 2*pi; return ret; }
};
struct Line
{
    Point p,v; double slop; inline Line() = default;
	inline Line(const Point &_p,const Point &_v):p(_p),v(_v) {}
    inline void update() { slop = v.alpha(); }
    friend inline bool operator <(const Line &l1,const Line &l2)
	{ return l1.slop < l2.slop; }
	inline double dis(const Point &a) { fabs((a-p)/v)/(v.len()); } //点到直线距离
};

inline bool OnLine(const Line &l,const Point &p) { return !dcmp(l.v/(p-l.p)); } //点在直线上

inline Point CrossPoint(const Line &a,const Line &b)  //直线交点
{	 Point u = a.p - b.p; double t = (b.v/u)/(a.v/b.v); return a.p+a.v*t; }

inline bool parallel(const Line &a,const Line &b) { return !dcmp(a.v/b.v); } //直线平行
