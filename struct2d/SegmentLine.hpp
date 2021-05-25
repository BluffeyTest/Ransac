


#ifndef SEGLINE_HPP
#define SEGLINE_HPP

#include"Point.hpp"
//#include"Line.hpp"
using std::min;
using std::max;


template<class _Tp>
class SegmentLine_
{
private:
	/* data */
public:
	//生成和销毁
	SegmentLine_(/* args */):pt1(_Tp()),pt2(_Tp()){}
	SegmentLine_(_Tp _p1, _Tp _p2):pt1(_Tp()),pt2(_Tp()){}
	~SegmentLine_();

	///<两条线段是否相等
	inline bool operator==(SegmentLine_ &stS) const
	{
		if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
			return true;
		return false;
	}

	/**
	 * @brief 线段与线段相交
	 * 使用快排跨立实验
	 * @param SL	另一条线段 
	 * @return true 
	 * @return false 
	 */
	inline bool Cross(SegmentLine_ &SL) const
	{
		//快排
		if (!(min(this->pt1.x, this->pt2.x) <= max(SL.pt1.x, SL.pt2.x) 
			&& min(SL.pt1.y, SL.pt2.y) <= max(this->pt1.y, this->pt2.y) 
			&& min(SL.pt1.x, SL.pt2.x) <= max(this->pt1.x, this->pt2.x) 
			&& min(this->pt1.y, this->pt2.y) <= max(SL.pt1.y, SL.pt2.y))
			)
				return false;

		//跨立
		double u, v, w, z;
		u = (SL.pt1.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (SL.pt1.y - this->pt1.y);
		v = (SL.pt2.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (SL.pt2.y - this->pt1.y);
		w = (this->pt1.x - SL.pt1.x) * (SL.pt2.y - SL.pt1.y) - (SL.pt2.x - SL.pt1.x) * (this->pt1.y - SL.pt1.y);
		z = (this->pt2.x - SL.pt1.x) * (SL.pt2.y - SL.pt1.y) - (SL.pt2.x - SL.pt1.x) * (this->pt2.y - SL.pt1.y);

		return (u * v <= 1e-8 && w * z <= 1e-8);
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
	inline double FromPoint(_Tp pt) const
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
	inline double AngleFrom(SegmentLine_ &stS) 
	{
		return (stS.Angle() - this->Angle());
	}

	/*****************************************************************************
	 * @brief 顺时针法线角度
	 * 
	 * @return double 
	 *****************************************************************************/
	inline double clockwiseNormalAngle()const
	{
		//return (pt2 - pt1).Rotate(PI/2).Angle();
		return (pt2-pt1).clockwiseNormalAngle();
	}

	/*****************************************************************************
	 * @brief 逆时针法线角度
	 * 
	 * @return double 
	 *****************************************************************************/
	inline double unClockwiseNormalAngle()const
	{
		//return (pt2 - pt1).Rotate(-PI/2).Angle();
		return (pt2-pt1).unclockwiseNormalAngle();
	}

	/*****************************************************************************
	 * @brief 求解两个线段所在直线的交点的函数
	 * 求解的方式是转换成点向式求解
	 * $pt = p_1 + a_1 * v_1 = p_2 + a_2 * v_2$
	 * $==> p_1 - p_2 + a_1*v_1-a_2*v_2 = 0$
	 * $==>
	 * 
	 * 
	 * @param {type} stS 
	 * @param {type} pt 
	 * @return true 相交且解算出来了
	 * @return false 不相交或者未解算出来 
	 *****************************************************************************/
	inline bool crossPoint(SegmentLine_<_Tp> &stS,_Tp &pt)
	{
		
		if (Cross(stS))
		{
			//TODO:
			auto s1 = (stS.pt1 - pt1).cross(stS.pt2 - pt1);
			auto s2 = (stS.pt2 - pt2).cross(stS.pt1 - pt2);
			pt = pt1+(pt2-pt1)*s1/(s1+s2);

		}
		else
		{
			return false;
		}
		return true;
	}

	//输出
	friend std::ostream &operator<<(std::ostream &os, SegmentLine_ &stS)
	{
		os << "SegLine: "
		<< "(" << stS.pt1.x << ", " << stS.pt1.y << ") ----> ( " << stS.pt2.x << ", " << stS.pt2.y << ")";
		return os;
	}

public:
	_Tp pt1;///<起点
	_Tp pt2;///<终点
};

//别名
typedef SegmentLine_<Point2i> SegLine2i;
typedef SegmentLine_<Point2f> SegLine2f;
typedef SegmentLine_<Point2d> SegLine2d;


//////////////////////////////////////////////////////////////////////////////////////////////
// 下面的部分不要了
//////////////////////////////////////////////////////////////////////////////////////////////



/**
 * @brief 两点线段\n
 * 起点和终点是有顺序的
 */
// struct stSegLine
// {
// 	Pointd pt1;///<起点
// 	Pointd pt2;///<终点

// 	stSegLine() : pt1(Pointd(0, 0)), pt2(Pointd(0, 0)) {}
// 	stSegLine(Pointd &p1, Pointd &p2) : pt1(p1), pt2(p2) {}

// 	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);

// 	///<两条线段是否相等
// 	inline bool operator==(stSegLine &stS) const
// 	{
// 		if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
// 			return true;
// 		return false;
// 	}

// 	//快排跨立实验
// 	/**
// 	 * @brief 线段与线段相交
// 	 * 
// 	 * @param stS 
// 	 * @return true 
// 	 * @return false 
// 	 */
// 	inline bool Cross(stSegLine &stS) const
// 	{
// 		if (!(min(this->pt1.x, this->pt2.x) <= max(stS.pt1.x, stS.pt2.x) 
// 			&& min(stS.pt1.y, stS.pt2.y) <= max(this->pt1.y, this->pt2.y) 
// 			&& min(stS.pt1.x, stS.pt2.x) <= max(this->pt1.x, this->pt2.x) 
// 			&& min(this->pt1.y, this->pt2.y) <= max(stS.pt1.y, stS.pt2.y))
// 			)
// 				return false;

// 		double u, v, w, z;
// 		u = (stS.pt1.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt1.y - this->pt1.y);
// 		v = (stS.pt2.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt2.y - this->pt1.y);
// 		w = (this->pt1.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt1.y - stS.pt1.y);
// 		z = (this->pt2.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt2.y - stS.pt1.y);

// 		return (u * v <= 0.00000001 && w * z <= 0.00000001);
// 	}

// 	/**
// 	 * @brief Get the Gen Line object
// 	 * 从线段获得直线
// 	 * 
// 	 * @param stG 
// 	 */
// 	// inline void GetGenLine(stGenLine &stG) const
// 	// {
// 	// 	stG.a = (double)(this->pt1.y - this->pt2.y);
// 	// 	stG.b = (double)(this->pt2.x - this->pt1.x);
// 	// 	stG.c = (double)(this->pt1.x * this->pt2.y - this->pt2.x * this->pt1.y);
// 	// }

// 	/**
// 	 * @brief 线段长度
// 	 * 
// 	 * @return double 
// 	 */
// 	inline double Length() const
// 	{
// 		return sqrt(pow(this->pt1.x - this->pt2.x, 2) + pow(this->pt1.y - this->pt2.y, 2));
// 	}

// 	/**
// 	 * @brief 线段到点的距离
// 	 * 与直线到点的距离相比，线段到点的距离的最短值可能是魔偶一个端点到该点都的距离
// 	 * @param pt 点
// 	 * @return double 
// 	 */
// 	inline double FromPoint(Point pt) const
// 	{
// 		double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
// 			+ (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
// 		double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
// 		double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
// 		if (r <= 0)
// 			return sqrt(dAP2); //第一种情况, 返回AP的长
// 		else if (r >= 1)
// 			return sqrt(dBP2); //第二种情况, 返回BP的长度
// 		else                   //第三种情况, 返回PC的长度
// 		{
// 			double AC = r * this->Length(); //先求AC的长度,(AC=r*|AB|)
// 			return sqrt(dAP2 - AC * AC);    //再勾股定理返回PC的长度
// 		}
// 		return 0.0;
// 	}

// 	/**
// 	* @brief 线段到点的距离
// 	* 与直线到点的距离相比，线段到点的距离的最短值可能是魔偶一个端点到该点都的距离
// 	* @param pt 点
// 	* @return double 
// 	*/
// 	inline double FromPoint(Point2d pt) const
// 	{
// 		double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
// 			+ (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
// 		double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
// 		double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
// 		if (r <= 0)
// 			return sqrt(dAP2); //第一种情况, 返回AP的长
// 		else if (r >= 1)
// 			return sqrt(dBP2); //第二种情况, 返回BP的长度
// 		else                   //第三种情况, 返回PC的长度
// 		{
// 			double AC = r * this->Length(); //先求AC的长度,(AC=r*|AB|)
// 			return sqrt(dAP2 - AC * AC);    //再勾股定理返回PC的长度
// 		}
// 		return 0.0;
// 	}

// 	/**
// 	* @brief 线段的倾斜角度
// 	* 
// 	* @return double 角度，弧度制
// 	*/
// 	inline double Angle() const
// 	{
// 		return atan2(pt2.y-pt1.y,pt2.x-pt1.x);
// 	}

// 	/**
// 	* @brief 两条线段之间的夹角
// 	* 
// 	* @param stS 这是另一条线段
// 	* @return double 角度，弧度制
// 	*/
// 	inline double AngleFrom(stSegLine &stS) 
// 	{
// 		return (stS.Angle() - this->Angle());
// 	}

// 	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS)
// 	{
// 		os << "SegLine: "
// 		<< "(" << stS.pt1.x << ", " << stS.pt1.y << ")----( " << stS.pt2.x << ", " << stS.pt2.y << ")";
// 		return os;
// 	}

// };

#endif //!SEGLINE_HPP