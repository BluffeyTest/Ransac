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

    return 0;
}

