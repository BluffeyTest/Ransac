


#ifndef SEGLINE_HPP
#define SEGLINE_HPP

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

	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);

	
	inline bool operator==(stSegLine &stS) const
	{
		if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
			return true;
		return false;
	}

	//快排跨立实验
	/**
	 * @brief 线段与线段相交
	 * 
	 * @param stS 
	 * @return true 
	 * @return false 
	 */
	inline bool Cross(stSegLine &stS) const
	{
		if (!(min(this->pt1.x, this->pt2.x) <= max(stS.pt1.x, stS.pt2.x) 
			&& min(stS.pt1.y, stS.pt2.y) <= max(this->pt1.y, this->pt2.y) 
			&& min(stS.pt1.x, stS.pt2.x) <= max(this->pt1.x, this->pt2.x) 
			&& min(this->pt1.y, this->pt2.y) <= max(stS.pt1.y, stS.pt2.y))
			)
				return false;

		double u, v, w, z;
		u = (stS.pt1.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt1.y - this->pt1.y);
		v = (stS.pt2.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt2.y - this->pt1.y);
		w = (this->pt1.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt1.y - stS.pt1.y);
		z = (this->pt2.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt2.y - stS.pt1.y);

		return (u * v <= 0.00000001 && w * z <= 0.00000001);
	}

	/**
	 * @brief Get the Gen Line object
	 * 从线段获得直线
	 * 
	 * @param stG 
	 */
	inline void GetGenLine(stGenLine &stG) const
	{
		stG.a = (double)(this->pt1.y - this->pt2.y);
		stG.b = (double)(this->pt2.x - this->pt1.x);
		stG.c = (double)(this->pt1.x * this->pt2.y - this->pt2.x * this->pt1.y);
	}

	/**
	 * @brief 线段长度
	 * 
	 * @return double 
	 */
	inline double Length() const
	{
		return sqrt(pow(this->pt1.x - this->pt2.x, 2) + pow(this->pt1.y - this->pt2.y, 2));
	}

	/**
	 * @brief 线段到点的距离
	 * 与直线到点的距离相比，线段到点的距离的最短值可能是魔偶一个端点到该点都的距离
	 * @param pt 点
	 * @return double 
	 */
	inline double FromPoint(Point pt) const
	{
		double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
			+ (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
		double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
		double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
		if (r <= 0)
			return sqrt(dAP2); //第一种情况, 返回AP的长
		else if (r >= 1)
			return sqrt(dBP2); //第二种情况, 返回BP的长度
		else                   //第三种情况, 返回PC的长度
		{
			double AC = r * this->Length(); //先求AC的长度,(AC=r*|AB|)
			return sqrt(dAP2 - AC * AC);    //再勾股定理返回PC的长度
		}
		return 0.0;
	}

	/**
	* @brief 线段到点的距离
	* 与直线到点的距离相比，线段到点的距离的最短值可能是魔偶一个端点到该点都的距离
	* @param pt 点
	* @return double 
	*/
	inline double FromPoint(Point2d pt) const
	{
		double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
			+ (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
		double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
		double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
		if (r <= 0)
			return sqrt(dAP2); //第一种情况, 返回AP的长
		else if (r >= 1)
			return sqrt(dBP2); //第二种情况, 返回BP的长度
		else                   //第三种情况, 返回PC的长度
		{
			double AC = r * this->Length(); //先求AC的长度,(AC=r*|AB|)
			return sqrt(dAP2 - AC * AC);    //再勾股定理返回PC的长度
		}
		return 0.0;
	}

	/**
	* @brief 线段的倾斜角度
	* 
	* @return double 角度，弧度制
	*/
	inline double Angle() const
	{
		return atan2(pt2.y-pt1.y,pt2.x-pt1.x);
	}

	/**
	* @brief 两条线段之间的夹角
	* 
	* @param stS 这是另一条线段
	* @return double 角度，弧度制
	*/
	inline double stSegLine::AngleFrom(stSegLine &stS) 
	{
		return (stS.Angle() - this->Angle());
	}

	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS)
	{
		os << "SegLine: "
		<< "(" << stS.pt1.x << ", " << stS.pt1.y << ")----( " << stS.pt2.x << ", " << stS.pt2.y << ")";
		return os;
	}

};

#endif //!SEGLINE_HPP