/**
 * @file Ransac.cpp
 * @author Bluffey (Bluffey@163.com)
 * @brief 
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
 * ������Ҫ�ĵ�.
 * 
 * \param vec_pts
 * \return 
 */
bool Ransac::InputPoints(std::vector<Point>& vec_pts)
{
    if (vec_pts.empty()) return false;//���

    //��շ�����
    m_vec_SrcPoints.clear();
    m_vec_Points.clear();
    m_vec_bMask.clear();

    //��ֵ
    m_vec_SrcPoints.assign(vec_pts.begin(), vec_pts.end() - 1);
    m_vec_Points.assign(vec_pts.begin(), vec_pts.end() - 1);
    for (size_t i = 0; i < m_vec_SrcPoints.size(); i++)
    {
        m_vec_bMask.push_back(0);
        m_vec_bSampleMask.push_back(0);
    }
    return true;
}

bool Ransac::InputPara(RansacPara& stR)
{
    m_Para = stR;
    return false;
}

bool Ransac::Run()
{
    switch (m_Para.type)
    {
    case RansacPara::RASANC_SEG_LINE:
        m_bSegLine = FitSegLine(); break;
    case RansacPara::RASANC_SEG_LINES:
        FitSegLines(); break;
    case RansacPara::RASANC_SEG_CIRCLE:
        m_bCircle = FitCircle(); break;
    case RansacPara::RASANC_SEG_CIRCLES:FitCircles(); break;
    default:
        break;
    }
    return false;
}

bool Ransac::FitSegLine()
{
    return false;
}


bool Ransac::FitSegLines()
{
    return false;
}

/**
 * Ransac���Բ.
 * 
 * \return 
 */
bool Ransac::FitCircle()
{
    size_t nSampleLen = m_vec_Points.size();
    int nInners(0);
    vector<int> vec_index;
    for(size_t i = 0;i<m_Para.nIters;i++)
    {
        //���ȡ��
        if (SumvUcharVctor(m_vec_bSampleMask) != nSampleLen)
        {
            RandIndex(nSampleLen, vec_index);
        }
        else break;
       
        //ȡ�õ�ǰԲ
        m_CurrentCircle = stCircle(m_vec_Points[vec_index[0]], m_vec_Points[vec_index[1]], m_vec_Points[vec_index[2]]);

        //�жϵ�ǰԲ���ڵ�����
        int nCurentInners = InnnerNums();
        if(nInners < nCurentInners)
        { 
            if (m_Para.dMaxR < 0.0 && m_Para.dMinR < 0.0)//�����뾶
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR > 0.0 && m_Para.dMinR > 0.0
                && (m_CurrentCircle.dR < m_Para.dMaxR && m_CurrentCircle.dR > m_Para.dMinR))//�����뾶�Ĵ�С�����,�����Ըĳ�ֻ�����������С
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR < 0.0 && m_Para.dMinR > 0.0
                && m_CurrentCircle.dR > m_Para.dMinR)//ֵ�����С�뾶��ͨ��
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else if (m_Para.dMaxR > 0.0 && m_Para.dMinR < 0.0
                && m_CurrentCircle.dR < m_Para.dMinR)//ֻ������뾶����ͨ��
            {
                nInners = nCurentInners;
                m_Circle = m_CurrentCircle;
            }
            else
            {
                //������
            }
            
        }


    }

    //�ж��Ƿ���ģ��
    double dScale = (double)nInners / nSampleLen;
    if (m_Para.dScale < 1e-5)
    {
        //����õ�ģ����������С����
        //��ʱֱ���ӳ�ȥ

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

bool Ransac::FitCircles()
{
    return false;
}

bool Ransac::GetResult()
{
    return false;
}

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
    case RansacPara::RASANC_SEG_LINE:
    case RansacPara::RASANC_SEG_LINES:nNums = 2; break;
    case RansacPara::RASANC_SEG_CIRCLE:
    case RansacPara::RASANC_SEG_CIRCLES:nNums = 3; break;
    default:nNums = 2;
        break;
    }

    for (int i = 0; i < nNums; i++)
    {
		nIndex = rand() % ndataLen;
        int nLimit(0);//��ֹ��ѭ��
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
    case RansacPara::RASANC_SEG_LINE:return InnnerLineNums(); break;//break��Ԥ���޸ĵ�
    case RansacPara::RASANC_SEG_LINES:; break;
    case RansacPara::RASANC_SEG_CIRCLE:return InnnerCircleNums(); break;
    case RansacPara::RASANC_SEG_CIRCLES:; break;
    default:
        break;
    }
    return 0;
}

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

