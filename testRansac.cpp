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
    cout<<"Ransac load successful!"<<endl;
    cout<<"========test Point======="<<endl;
    Point pt;
    cout<<"Point pt = "<<pt<<";"<<endl;
    pt = pt +Point(1,2);
    cout<<"Point add = "<<pt<<";"<<endl;

    cout<<"========test vec=========="<<endl;
    vec vec1(2,1);
    cout<<"the angle of "<<vec1<<" is "<<vec1.Angle()<<":"<<vec1.Angle()*180/PI<<"度"<<endl;
    vec vec2=vec1.Rotate(PI/2);
    cout<<"the angle of "<<vec2<<" is "<<vec2.Angle()<<":"<<vec2.Angle()*180/PI<<"度"<<endl;
    vec vec3=vec1.Rotate(PI); 
    cout<<"the angle of "<<vec3<<" is "<<vec3.Angle()<<":"<<vec3.Angle()*180/PI<<"度"<<endl;
    vec vec4=vec1.Rotate(3*PI/2); 
    cout<<"the angle of "<<vec4<<" is "<<vec4.Angle()<<":"<<vec4.Angle()*180/PI<<"度"<<endl; 


    return 0;
}

