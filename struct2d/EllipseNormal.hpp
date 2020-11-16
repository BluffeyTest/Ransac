

#ifndef ELLIPSE_NORMAL_HPP
#define ELLIPSE_NORMAL_HPP

/**
 * @brief 椭圆的一般方程式ax^2+by^2+cxy+dx+ey = 0;
 * 二次型的表述：
 * 
 */
typedef struct stEllipseNormal
{
	double A;
	double B;
	double C;
	double D;
	double E;

	stEllipseNormal():A(0.0),B(0.0),C(0.0),D(0.0),E(0.0){}
	stEllipseNormal(double _a,double _b,double _c,double _d,double _e):
		A(_a),B(_b),C(_c),D(_d),E(_e){}				///<从已经有的参数复制
	stEllipseNormal(Pointd &pt1,Pointd &pt2,Pointd &pt3, 
		Pointd &pt4,Pointd &pt5,Pointd &pt6);		///<从六个点用线性代数导出
	stEllipseNormal(std::vector<Point2f> &vPts);	///<从点集当中用最小二乘法拟合出来椭圆
	stEllipseNormal(stEllipse &_stE);
	
	


}EllipseStd;

#endif //!ELLIPSE_NORMAL_HPP