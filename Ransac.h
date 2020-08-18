#pragma once

#ifndef RANSAC_H
#define RANSAC_H
#include <ctime>

#include"Struct2d.h"

/**
 * Ransac ����.
 */
typedef struct stRansacPara
{
	enum emFitType
	{
		RASANC_SEG_LINE = 0,
		RASANC_SEG_LINES = 1,
		RASANC_SEG_CIRCLE = 2,
		RASANC_SEG_CIRCLES = 3,
	};
	emFitType type;//�������
	double dInner;//�ڵ����
	double dScale;//��С��ϵ�����������Ϊ0����ȡ��󣬷���һ��ȡ����0.5
	int nIters;//����������

	double dMinR;//������Сֱ��
	double dMaxR;//�������ֱ��

	stRansacPara():type(RASANC_SEG_LINE), dInner(2.0), dScale(0.9), nIters(50),dMinR(-1.0),dMaxR(-1.0){}
	stRansacPara(emFitType t, double in, double s, int it):type(t), dInner(in), dScale(s), nIters(it) , dMinR(-1), dMaxR(-1){}
	stRansacPara(emFitType t, double in, double s, int it, double min,double max):type(t), dInner(in), dScale(s), nIters(it) ,  dMinR(min), dMaxR(max){}

}RansacPara;

class Ransac
{
public:
	Ransac();
	~Ransac();

private:
	RansacPara m_Para;//����

	std::vector<Point> m_vec_SrcPoints;///ԭʼ�㼯
	std::vector<Point> m_vec_Points;///ʵ�ʴ�����̵��еĵ㼯
	std::vector<unsigned char> m_vec_bMask;//�洢��Ӧ�ĵ��ǲ��Ƿ��ϵ�ǰ��ϵ�ģ��
	std::vector<unsigned char> m_vec_bSampleMask;//�洢��Ӧ�ĵ��ǲ����Ѿ��䵱��������


	std::vector<stCircle> m_vec_Circles;///��������Բ
	std::vector<stSegLine> m_vec_SegLines;//���������߶�

	stCircle m_Circle;//���ص���Բ
	stSegLine m_SegLine;//���صĵ����߶�

	stCircle m_CurrentCircle;//���ڼ��ĵ���Բ
	stSegLine m_CurrentSegLine;//���ڼ��ĵ����߶�

	bool m_bCircle;//Բ����Ƿ�ɹ�
	bool m_bSegLine;//ֱ�߼���Ƿ�ɹ�

	//bool m_bVecCircle; //�Ƿ񷵻ض��Բ
	//bool m_bVecSegLine;//�Ƿ񷵻ض���߶�

public:

	bool InputPoints(std::vector<Point> &vec_pts);//����㼯
	bool InputPara(RansacPara& stR);//�������
	bool Run();//����
	
	
	

	bool GetResult();//���д�����ã���������һ
	bool GetResultCircle(stCircle& stC);

private:
	bool FitSegLine();//���ֱ��
	bool FitSegLines();//��϶���ֱ�ߣ�
	bool FitCircle();//���Բ��
	bool FitCircles();//��϶��Բ

	int SumvUcharVctor(std::vector<unsigned char> &vec_s);
	bool RandIndex(int ndataLen, std::vector<int>& vec_Index);
	int InnnerNums();//�жϵ�ǰ��ģ�͵����ڵ�����ڵĵ���
	int InnnerLineNums();//�жϵ�ǰ��ģ�͵����ڵ�����ڵĵ���
	int InnnerCircleNums();//�жϵ�ǰ��ģ�͵����ڵ�����ڵĵ���
};














#endif // !RANSAC_H