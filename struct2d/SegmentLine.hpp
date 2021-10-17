


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
	SegmentLine_(_Tp _p1, _Tp _p2):pt1(_Tp(_p1)),pt2(_Tp(_p2)){}
	~SegmentLine_(){}

	///<两条线段是否相等
	inline bool operator==(SegmentLine_ &stS) const
	{
		if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
			return true;
		return false;
	}

	/*****************************************************************************
	 * @brief 取得线段的中点
	 * 
	 * @return _Tp 
	 *****************************************************************************/
	inline _Tp centerPoint()
	{
		return std::move((pt1+pt2)/2);
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
	 * @brief 计算线段是否包含点
	 * @details 使用叉积，两个向量的叉积为零则两个向量共线，同时，以所求点为终点，原本的向量的起点为起点，这两向量共起点，且一个向量的终点在另一个向量的起点到终点之间，则所求的点在向量上。
	 * @param p 		点
	 * @return true 	点在线上
	 * @return false 	点不在线上
	 */
	inline bool Contain(_Tp &p)const
	{
		if(((p-pt1)||(pt2-pt1))		//pt1-->p 和 pt1-->pt2 平行
			//(Q.x - pt1.x) * (Pj.y - pt1.y) == (Pj.x - Pi.x) * (Q.y - Pi.y)  //叉乘 
       		//保证Q点坐标在pi,pj之间 
       		&& min(pt1.x , pt2.x) <= p.x && p.x <= max(pt1.x , pt2.x)    
       		&& min(pt1.y , pt2.y) <= p.y && p.y <= max(pt1.y , pt2.y))
        	return true;
    	else
        	return false;
	}

	/**
	 * @brief 两段线段是否有重合
	 * @details 有重合的两段线段的向量夹角为零，叉积为零，且一段线段的端点中至少有一个端点在另一个线段上这样只计算一个线段的两个端点是否在另一条线段上有效节省计算量。
	 * 返回的是认为重合的线段是同向，平行，且有重合的两线段
	 * @param stS 
	 * @return true 	两线段平行，同向且重合
	 * @return false 
	 * @sa SameDirector 
	 */
	inline bool Coincide(SegmentLine_<_Tp> &stS)const
	{
		//这个判断看起来有点问题啊，而且运算量有点大
		if(
			(pt2-pt1).SameDirector(stS.pt2-stS.pt1)		//两个向量的夹角为0，意思就是没法区分正向反向了
			//&& ((pt2-pt1).dot(stS.pt2-stS.pt1)>0)		//两个平行向量的点积大于零，则两向量同向
			&& (Contain(stS.pt1)						//线段2的起点在线段1上
				|| Contain(stS.pt2)						//线段2的终点在线段1上
			)
		)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*****************************************************************************
	 * @brief 两线段是否反向重合
	 * 
	 * @param stS 
	 * @return true 两向量平行反向，且有重合
	 * @return false 
	 * @sa Coincide , OppositeDirector , SameDirector
	 *****************************************************************************/
	inline bool OppositeCoincide(SegmentLine_<_Tp> &stS)const
	{
		//这个判断看起来有点问题啊，而且运算量有点大
		if(
			(pt2-pt1).OppositeDirector(stS.pt2-stS.pt1)		//两个向量的夹角为0，意思就是没法区分正向反向了
			//&& ((pt2-pt1).dot(stS.pt2-stS.pt1)>0)		//两个平行向量的点积大于零，则两向量同向
			&& (Contain(stS.pt1)						//线段2的起点在线段1上
				|| Contain(stS.pt2)						//线段2的终点在线段1上
			)
		)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief 合并两个平行同向，且有重合的线段
	 * 
	 * @param stS[in] 		第二条有向线段
	 * @param stSOut[out] 	合并后的线段
	 * @return true 		成功合并
	 * @return false 		未能成功合并
	 */
	inline bool Merge(SegmentLine_<_Tp> &stS, SegmentLine_<_Tp> &stSOut)const
	{
		if(Coincide(stS))
		{
			stSOut.pt1 = Contain(stS.pt1) ? pt1 : stS.pt1;
			stSOut.pt2 = Contain(stS.pt2) ? pt2 : stS.pt2;

			return true;
		}
		else
		{
			return false;
		}
	}
	
	/*****************************************************************************
	 * @brief 取得两个反向线段的并集
	 * @details 以靠近第一段线段起点的点为起点，以靠近第一段线段终点的点为终点
	 * 
	 * @param {type} stS 
	 * @param {type} stSOut 
	 * @return true 
	 * @return false 
	 *****************************************************************************/
	inline bool Union(SegmentLine_<_Tp> &stS, SegmentLine_<_Tp> &stSOut)const
	{
		if(OppositeCoincide(stS))
		{
			stSOut.pt1 = Contain(stS.pt2)?stS.pt2:pt1;
			stSOut.pt2 = Contain(stS.pt1)?stS.pt1:pt2;

			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief 线段长度
	 * 
	 * @return double 
	 */
	inline double Length() const
	{
		//return sqrt(pow(this->pt1.x - this->pt2.x, 2) + pow(this->pt1.y - this->pt2.y, 2));
		return this->pt1.Distance(this->pt2);
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
	 * 注意，两个叉积都为零的情况下，计算处的点是不对的，所以要排除这种情况
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

			//共线的情况没有意义
			if (std::abs(s1)<1e-6 && std::abs(s2)<1e-6)
			{
				return false;
			}
			
			pt = pt1+(pt2-pt1)*s1/(s1+s2);

		}
		else
		{
			return false;
		}
		return true;
	}

	/*****************************************************************************
	 * @brief 检查两线段是否平行
	 * 
	 * @param {type} stS 
	 * @return true 
	 * @return false 
	 *****************************************************************************/
	inline bool operator ||(const SegmentLine_<_Tp> &stS)const
    {
        return (this->pt2 - this->pt1)||(stS.pt2-stS.pt1);
    }

	//输出
	friend std::ostream &operator<<(std::ostream &os, SegmentLine_ &stS)
	{
		os << "SegLine: " << stS.pt1 << "-->" << stS.pt2;
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
typedef SegmentLine_<unsigned char> SegLine2u;
typedef SegmentLine_<long int> SegLine2l;
typedef SegmentLine_<long double> SegLine2ld;

typedef SegLine2i SegLinei;
typedef SegLine2f SegLinef;
typedef SegLine2d SegLined;
typedef SegLine2l SegLinel;
typedef SegLine2ld SegLineld;


//////////////////////////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////////////////////////


#endif //!SEGLINE_HPP