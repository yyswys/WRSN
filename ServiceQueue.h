//
// Created by 22306 on 2023/4/23.
//
#include "WCV.h"
#include "WRSN.h"
#ifndef WRSN_ULTRA_SERVICEQUEUE_H
#define WRSN_ULTRA_SERVICEQUEUE_H
struct Location{
    float x;
    float y;
};
struct Request {
    int ID;
    float x;    //x坐标
    float y;    //y坐标
    float e;    //剩余能量
    float q;    //消耗速率
    float t;    //到达时间
};



#endif //WRSN_ULTRA_SERVICEQUEUE_H
