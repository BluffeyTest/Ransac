/**
 * @file Ransac.cpp
 * @author Bluffey (Bluffey@163.com)
 * @brief 使用Ransac拟合二维图形
 * @note 后续可能会添加三位平面，三维球，三维椭球，以及二维椭圆的拟合
 *      可能会大更，增加命名空间，或者不再使用类进行编写。
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include"Ransac.h"

using namespace std;

Ransac::Ransac()
{
    m_bCircle = false;
    m_bSegLine = false;
}

Ransac::~Ransac()
{
}

/**
 * 输入需要的点.
 * 
 * @param vec_pts
 * @return 
 */
bool Ransac::InputPoints(std::vector<Point>& vec_pts)
{
    if (vec_pts.empty()) return false;//检查

    //清空防干扰
    m_vec_SrcPoints.clear();
    m_vec_Points.clear();
    m_vec_bMask.clear();

    //赋值
    m_vec_SrcPoints.assign(vec_pts.begin(), vec_pts.end() - 1);
    m_vec_Points.assign(vec_pts.begin(), vec_pts.end() - 1);
    for (size_t i = 0; i < m_vec_SrcPoints.size(); i++)
    {
        m_vec_bMask.push_back(0);
        m_vec_bSampleMask.push_back(0);
    }
    return true;
}

/**
 * @brief 输入参数
 * 
 * @param stR 
 * @return true 
 * @return false 
 */
bool Ransac::InputPara(RansacPara& stR)
{
    m_Para = stR;
    return false;
}


/**
 * @brief 运行拟合
 * 
 * @return true 
 * @return false 
 */
bool Ransac::Run()
{
    switch (m_Para.type)
    {
    case RansacPara::FIT_LINE:
        m_bSegLine = FitSegLine(); break;
    case RansacPara::FIT_LINES:
        FitSegLines(); break;
    case RansacPara::FIT_CIRCLE:
        m_bCircle = FitCircle(); break;
    case RansacPara::FIT_CIRCLES:FitCircles(); break;
    default:
        break;
    }
    return false;
}

/**
 * @brief 拟合线
 * 
 * @return true 拟合成功
 * @return false 拟合失败
 */
bool Ransac::FitSegLine()
{
    size_t nSampleLen = m_vec_Points.size();
    int nInners(0);
    vector<int> vec_index;
    for(size_t i = 0;i<m_Para.nIters;i++)
    {
        //随机取点
        if (SumvUcharVctor(m_vec_bSampleMask) != nSampleLen)
        {
            RandIndex(nSampleLen, vec_index);
        }
        else break;
       
        //取得当前直线
        m_CurrentSegLine = stGenLine(m_vec_Points[vec_index[0]], m_vec_Points[vec_index[1]]);

        //判断当前直线的内点数量，并更新模型
        int nCurentInners = InnnerNums();
        if(nInners < nCurentInners)
        { 
            nInners = nCurentInners;
            m_SegLine = m_CurrentSegLine;          
        }


    }

    //判断是否有模型
    double dScale = (double)nInners / nSampleLen;
    if (m_Para.dScale < 1e-5)
    {
        //将最好的模型拿来做最小二乘
        //暂时直接扔出去

		return true;
    }
    else if (dScale < m_Para.dScale )
    {
        m_SegLine = stGenLine(0.,0.,0.);
        return false;
    }

    return true;
}


/**
 * @brief 拟合多条直线，涉及到剔除已经拟合的直线的点问题，和已经拟合的结果返回的问题
 * @note 暂时不添加，知道有需要的时候
 * @return true 
 * @return false 
 */
bool Ransac::FitSegLines()
{
    return false;
}

/**
 * @brief 拟合圆
 * 
 * @return true 拟合成功
 * @return false 拟合失败
 */
bool Ransac::FitCircle()
{
    size_t nSampleLen = m_vec_Points.size();
    int nInners(0);
    vector<int> vec_index;
    for(size_t i = 0;i<m_Para.nIters;i++)
    {
        //随机取点
        if (SumvUcharVctor(m_vec_bSampleMask) != nSampleLen)
        {
            RandIndex(nSampleLen, vec_index);
        }
        else break;
       
        //取得当前圆
        m_CurrentCircle = stCircle(m_vec_Points[vec_index[0]], m_vec_Points[vec_index[1]], m_vec_Points[vec_index[2]]);

        //判断当前圆的内点数量
        int nCurentInners = InnnerNums();
        if(nInners < nCurentInners)
        { 
            if (m_Para.dMaxR < 0.0 && m_Para.dMinR < 0.0)//不检查半径
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR > 0.0 && m_Para.dMinR > 0.0
                && (m_CurrentCircle.dR < m_Para.dMaxR && m_CurrentCircle.dR > m_Para.dMinR))//两个半径的大小都检查,还可以改成只检查最大或者最小
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR < 0.0 && m_Para.dMinR > 0.0
                && m_CurrentCircle.dR > m_Para.dMinR)//值检查最小半径且通过
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR > 0.0 && m_Para.dMinR < 0.0
                && m_CurrentCircle.dR < m_Para.dMinR)//只检查最大半径，且通过
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else
            {
                //不更新
            }
            
        }


    }

    //判断是否有模型
    double dScale = (double)nInners / nSampleLen;
    if (m_Para.dScale < 1e-5)
    {
        //将最好的模型拿来做最小二乘
        //暂时直接扔出去

		if (m_Para.dMaxR > 0.0 && m_Para.dMinR > 0.0
			&& (m_Circle.dR> m_Para.dMaxR || m_Circle.dR < m_Para.dMinR)
            )
        {
            Pointd pt(0, 0);
            m_Circle = stCircle(pt, -1.);
            return false;
        }
    }
    else if (dScale < m_Para.dScale )
    {
        Pointd pt(0, 0);
        m_Circle = stCircle(pt, -1.);
        return false;
    }

    //
    return true;
}

/**
 * @brief 拟合多个圆
 * @note 暂时不添加，直到有需要的时候
 * @return true 
 * @return false 
 */
bool Ransac::FitCircles()
{
    return false;
}

/**
 * @brief 获取结果，尚未有较好的返回方式
 * 
 * @return true 
 * @return false 
 */
bool Ransac::GetResult()
{
    return false;
}

/**
 * @brief 返回圆的结果
 * 
 * @param[out] stC 返回的圆
 * @return true 
 * @return false 
 */
bool Ransac::GetResultCircle(stCircle& stC)
{
    if (m_bCircle)
    {
        stC = m_Circle;
    }
    else
    {
        stC.dR = -1.0;
    }
    return m_bCircle;
}

int Ransac::SumvUcharVctor(vector<unsigned char> &vec_s)
{
    int sum(0);
    for (size_t i = 0; i < vec_s.size(); i++)
    {
        sum += vec_s[i];
    }
    return sum;
}

bool Ransac::RandIndex(int ndataLen, vector<int> &vec_Index)
{
    int nNums;
    int nIndex(-1);
    vec_Index.clear();
    switch (m_Para.type)
    {
    case RansacPara::FIT_LINE:
    case RansacPara::FIT_LINES:nNums = 2; break;
    case RansacPara::FIT_CIRCLE:
    case RansacPara::FIT_CIRCLES:nNums = 3; break;
    default:nNums = 2;
        break;
    }

    for (int i = 0; i < nNums; i++)
    {
		nIndex = rand() % ndataLen;
        int nLimit(0);//防止死循环
		while (nLimit <50 &&
            nIndex!= -1 
            && m_vec_bSampleMask[nIndex] != 0)
		{
            nIndex = rand() % ndataLen;
            nLimit++;
		}
        vec_Index.push_back(nIndex);
        m_vec_bSampleMask[nIndex] = 1;
    }

    return true;
}

int Ransac::InnnerNums()
{
    switch (m_Para.type)
    {
    case RansacPara::FIT_LINE:return InnnerLineNums(); break;//break是预防修改的
    case RansacPara::FIT_LINES:; break;
    case RansacPara::FIT_CIRCLE:return InnnerCircleNums(); break;
    case RansacPara::FIT_CIRCLES:; break;
    default:
        break;
    }
    return 0;
}


/**
 * @brief 计算直线的内点数量
 * 
 * @return int 
 */
int Ransac::InnnerLineNums()
{
    int sum(0);
    for (size_t i = 0; i < m_vec_Points.size(); i++)
    {
        if (m_CurrentSegLine.FromPoint(m_vec_Points[i]) < m_Para.dInner)
        {
            sum++;
        }
    }
    return sum;
}

/**
 * @brief 计算圆的内点数量
 * 
 * @return int 
 */
int Ransac::InnnerCircleNums()
{
    int sum(0);
    for (size_t i = 0; i < m_vec_Points.size(); i++)
    {
        double d = Distance(m_CurrentCircle.ptCenter, m_vec_Points[i]);//m_CurrentCircle.FromPoint(m_vec_Points[i]);
        if ( fabs(d- m_CurrentCircle.dR)< m_Para.dInner)
        {
            sum++;
        }
    }
    return sum;
}

