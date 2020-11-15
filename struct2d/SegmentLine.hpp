





/**
 * @brief 两点线段\n
 * 起点和终点是有顺序的
 */
struct stSegLine
{
	Pointd pt1;///<起点
	Pointd pt2;///<终点

	stSegLine() : pt1(Pointd(0, 0)), pt2(Pointd(0, 0)) {}
	stSegLine(Pointd &p1, Pointd &p2) : pt1(p1), pt2(p2) {}

	bool operator==(stSegLine &stS) const;	///<两条线段是否相等

	bool Cross(stSegLine &stS) const;	  ///<线段与线段相交
	void GetGenLine(stGenLine &stG) const; ///<从线段获得直线
	double Length() const;				  ///<线段长度
	double FromPoint(Point pt) const;  ///<线段到一个点的最短距离
	double FromPoint(Point2d pt) const;  ///<线段到一个点的最短距离

	double Angle() const;				///<线段的角度
	double AngleFrom(stSegLine &stS);	///<两条线段的夹角


	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);
};