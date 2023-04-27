//
// Created by 22306 on 2023/4/23.
//

#include "WRSN.h"
#include <list>
using namespace std;
#ifndef WRSN_ULTRA_SERVICEQUEUE_H
#define WRSN_ULTRA_SERVICEQUEUE_H

struct Request {
    int ID;
    float x;    //x坐标
    float y;    //y坐标
    float e;    //剩余能量
    float q;    //消耗速率
    //float t;    //到达时间
};

vector<Request> servicequeue;

void updateRequest(N *node){
    Request tempr;
    for(int i=0;i<30;i++){
        if(needCharge(node[i])){
            tempr.ID = i;
            tempr.x = node[i].x;
            tempr.y = node[i].y;
            tempr.e = node[i].e;
            tempr.q = node[i].q;
            servicequeue.push_back(tempr);
        }
    }
}

vector<Location> canChargeP;
vector<int> P;

void getPoints(vector<Request> serviceQ,Grid G,float R)
{//根据需要充电的点以及半径求得可以给节点充电的位置
    for(int i=0;i<serviceQ.size();i++)
    {
        for(int j=0;j<G.l.size();j++) {
            if (sqrt((G.l[j].x-serviceQ[i].x)*(G.l[j].x-serviceQ[i].x)+(G.l[j].y-serviceQ[i].y)*(G.l[j].y-serviceQ[i].y)) <= R) {
                Location temp;
                temp.x = serviceQ[i].x;
                temp.y = serviceQ[i].y;
                canChargeP.push_back(temp);
                P.push_back(serviceQ[i]);
            }
        }
    }
}



#endif //WRSN_ULTRA_SERVICEQUEUE_H
