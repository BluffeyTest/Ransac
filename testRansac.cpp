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


    return 0;
}

