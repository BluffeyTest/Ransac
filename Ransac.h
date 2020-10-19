/**
 * @file Ransac.h
 * @author Bluffey (Bluffey@163.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#ifndef RANSAC_H
#define RANSAC_H
#include <ctime>

#include"Struct2d.h"

/**
*
what is .dump?
*/

/**
 * Ransac 参数.
 */
typedef struct stRansacPara
{
	enum emFitType
	{
		FIT_LINE = 0,
		FIT_LINES = 1,
		FIT_CIRCLE = 2,
		FIT_CIRCLES = 3,
	};
	emFitType type;//拟合类型
	double dInner;//内点距离
	double dScale;//最小拟合点数比例，若为0，则取最大，否则一般取至少0.5
	int nIters;//最大迭代次数

	double dMinR;//限制最小直径
	double dMaxR;//限制最大直径

	stRansacPara():type(FIT_LINE), dInner(2.0), dScale(0.9), nIters(50),dMinR(-1.0),dMaxR(-1.0){}
	stRansacPara(emFitType t, double in, double s, int it):type(t), dInner(in), dScale(s), nIters(it) , dMinR(-1), dMaxR(-1){}
	stRansacPara(emFitType t, double in, double s, int it, double min,double max):type(t), dInner(in), dScale(s), nIters(it) ,  dMinR(min), dMaxR(max){}

}RansacPara;

class Ransac
{
public:
	Ransac();
	~Ransac();

private:
	RansacPara m_Para;//参数

	std::vector<Point> m_vec_SrcPoints;///原始点集
	std::vector<Pointd> m_vec_Points;///实际处理过程当中的点集
	std::vector<unsigned char> m_vec_bMask;//存储对应的点是不是符合当前拟合的模型
	std::vector<unsigned char> m_vec_bSampleMask;//存储对应的点是不是已经充当过采样点


	std::vector<stCircle> m_vec_Circles;///检测出来的圆
	std::vector<stGenLine> m_vec_SegLines;//检测出来的线段

	stCircle m_Circle;//返回单个圆
	stGenLine m_SegLine;//返回的单个线段

	stCircle m_CurrentCircle;//正在检测的单个圆
	stGenLine m_CurrentSegLine;//正在检测的单个线段

	bool m_bCircle;//圆检测是否成功
	bool m_bSegLine;//直线检测是否成功

	//bool m_bVecCircle; //是否返回多个圆
	//bool m_bVecSegLine;//是否返回多个线段

public:

	bool InputPoints(std::vector<Point> &vec_pts);//传入点集
	bool InputPara(RansacPara& stR);//传入参数
	bool Run();//运行
	
	
	

	bool GetResult();//这个写法不好，传出不单一
	bool GetResultCircle(stCircle& stC);
	bool GetInnerPoints(std::vector<Pointd> &ptInners);//得到内点

private:
	bool FitSegLine();//拟合直线
	bool FitSegLines();//拟合多条直线；
	bool FitCircle();//拟合圆；
	bool FitCircles();//拟合多个圆

	int SumvUcharVctor(std::vector<unsigned char> &vec_s);//计数，感觉可以优化的样子
	bool RandIndex(int ndataLen, std::vector<int>& vec_Index);
	int InnnerNums();//判断当前的模型的在内点距离内的点数
	int InnnerLineNums();//判断当前的模型的在内点距离内的点数
	int InnnerCircleNums();//判断当前的模型的在内点距离内的点数

	/// 获得内点
	bool GetInnerPointsLine(std::vector<Pointd> &ptInners);
	bool GetInnerPointsCircle(std::vector<Pointd> &ptInners);
};














#endif // !RANSAC_H