/**
 * @file testRansac.cpp
 * @author your name (you@domain.com)
 * @brief 用于测试库的运行
 * @version 0.1
 * @date 2020-09-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include"Ransac.h"
#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std;



int main(int argc, char **argv)
{
    //测试读入
    cout<<"Ransac load successful!"<<endl;
    cout<<"======== test Point ======="<<endl;
    Point pt;
    cout<<"Point pt = "<<pt<<";"<<endl;
    pt = pt +Point(1,2);
    cout<<"Point add = "<<pt<<";"<<endl;

    //测试角度以及旋转
    cout<<"======== test vec =========="<<endl;
    vecf vec1(2.0,1.0);
    cout<<"the angle of "<<vec1<<" is "<<vec1.Angle()<<":"<<vec1.Angle()*180/PI<<"度"<<endl;
    vecf vec2=vec1.Rotate(PI/2);
    cout<<"the angle of "<<vec2<<" is "<<vec2.Angle()<<":"<<vec2.Angle()*180/PI<<"度"<<endl;
    vecf vec3=vec1.Rotate(PI); 
    cout<<"the angle of "<<vec3<<" is "<<vec3.Angle()<<":"<<vec3.Angle()*180/PI<<"度"<<endl;
    vecf vec4=vec1.Rotate(3*PI/2); 
    cout<<"the angle of "<<vec4<<" is "<<vec4.Angle()<<":"<<vec4.Angle()*180/PI<<"度"<<endl; 


    //测试距离
    cout<<"======== test distance =========="<<endl;
    Point pt1(1,1),pt2(1,3);
    cout<<"the distance of "<<pt1<<" and "<<pt2<< " is "<<pt1.Distance(pt2)<<endl;
    SegLine2i sl(pt1,pt2);
    cout<<"the length of "<<sl<<" is "<<sl.Length()<<endl;

    //测试符号运算
    cout<<"======== test operator =========="<<endl;
    cout<<"(pt1 == pt2) is "<<(pt1==pt2)<<endl;
    cout<<"(pt1 != pt2) is "<<(pt1!=pt2)<<endl;

    cout<<"======== test cross =========="<<endl;
    Pointd ptd1(0.0,0.0),ptd2(1.0,0.0),ptd3(1.0,1.0),ptd4(0.0,1.0);
    SegLined sl_1(ptd1,ptd2),sl_2(ptd2,ptd3),sl_3(ptd3,ptd1),sl_4(ptd4,ptd3);
    cout<<"sl_1 cross sl_2 is "<<sl_1.Cross(sl_2)<<endl;
    cout<<"sl_2 cross sl_3 is "<<sl_2.Cross(sl_3)<<endl;
    cout<<"sl_3 cross sl_1 is "<<sl_3.Cross(sl_1)<<endl;
    cout<<"sl_1 cross sl_4 is "<<sl_1.Cross(sl_4)<<endl;

    Pointd ptc_1(-1.0,-1.0),ptc_2(-1.0,-1.0),ptc_3(-1.0,-1.0),ptc_4(-1.0,-1.0);
    sl_1.crossPoint(sl_2,ptc_1);
    sl_2.crossPoint(sl_3,ptc_2);
    sl_3.crossPoint(sl_1,ptc_3);
    sl_4.crossPoint(sl_1,ptc_4);
    cout<<"sl_1 corss sl_2 in "<<ptc_1<<endl;
    cout<<"sl_2 corss sl_3 in "<<ptc_2<<endl;
    cout<<"sl_3 corss sl_1 in "<<ptc_3<<endl;
    cout<<"sl_4 corss sl_1 in "<<ptc_4<<endl;
    
    //测试平行
    cout<<"======== test || =========="<<endl;
    vecd v_1(1.,1.),v_2(-1.,-1.),v_3(0.,1.),v_4(0.,-1.);
    cout<<v_1<<" || "<<v_2<< " = "<<(v_1||v_2)<<endl; 
    cout<<v_3<<" || "<<v_4<< " = "<<(v_3||v_4)<<endl;

    //测试一个点在线段内
    cout<<"======== test point in segment =========="<<endl;
    Pointd pt_mid(0.5,0.5);
    cout<<ptd1<<" in "<<sl_3<<" is "<<sl_3.Contain(ptd1)<<endl;
    cout<<ptd3<<" in "<<sl_3<<" is "<<sl_3.Contain(ptd3)<<endl;
    cout<<ptd4<<" in "<<sl_3<<" is "<<sl_3.Contain(ptd4)<<endl;
    cout<<pt_mid<<" in "<<sl_3<<" is "<<sl_3.Contain(pt_mid)<<endl;

    //测试平行且同向
    cout<<"======== test || and direction =========="<<endl;
    cout<<v_1<<" SameDirector with "<<v_1<< " = "<<(v_1.SameDirector(v_1))<<endl; 
    cout<<v_3<<" SameDirector with "<<v_4<< " = "<<(v_3.SameDirector(v_4))<<endl;
    cout<<v_1<<" SameDirector with "<<v_4<< " = "<<(v_1.SameDirector(v_4))<<endl;

    cout<<"======== test merge segment =========="<<endl;
    //测试合并平行且同向的线段合并
    SegLine2d L_1(Point2d(0.0,0.0),Point2d(2.0,2.0));
    SegLine2d L_2(Point2d(1.0,1.0),Point2d(3.0,3.0));
    SegLine2d L_3(Point2d(0.0,0.0),Point2d(-2.0,-2.0));
    SegLine2d L_4(Point2d(1.0,1.5),Point2d(3.0,3.0));

    bool bm_1,bm_2,bm_3,bm_4;
    SegLine2d L_out_1,L_out_2,L_out_3,L_out_4;
    bm_1 = L_1.Merge(L_2,L_out_1);
    bm_2 = L_1.Merge(L_3,L_out_2);
    bm_3 = L_1.Merge(L_4,L_out_3);
    //bm_1 = L_1.Merge(L_2,L_out_1);
    cout<<L_1<<" merge "<<L_2<<" is "<<bm_1<<", "<<L_out_1<<endl;
    cout<<L_1<<" merge "<<L_3<<" is "<<bm_2<<", "<<L_out_2<<endl;
    cout<<L_1<<" merge "<<L_4<<" is "<<bm_3<<", "<<L_out_3<<endl;

    return 0;
}

