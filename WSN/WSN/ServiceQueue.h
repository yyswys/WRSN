//
// Created by 22306 on 2023/4/15.
//
#include"vector"
#include "WRSN.h"
#include "WCV.h"
#ifndef WSN_SERVICEQUEUE_H
#define WSN_SERVICEQUEUE_H
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


/*
 * 时间优先级
 */
float time(WCV Car,N Node,int n)
{
    return ((Node.e / Node.q - Car.te) * n) /
           (Car.tl - Car.te);
}
/*
 * 空间优先级
 */
float distance(WCV Car,N Node,int n)
{
    float d = sqrt((Car.x - Node.x) * (Car.x - Node.x) +
                   (Car.y - Node.y) * (Car.y - Node.y));
    return  ((d - Car.dn) * n) /
            (Car.df - Car.dn);
}


float score(float d,float t) {
    float a = 1;
    float b = 1;
    return a * t + b * d + log10(t * d + 1);
}

/*
 * 节点1、节点2、充电车、节点个数
 * 根据论文中的公式判定两个节点获得充电优先级
 */
bool op(N N1,N N2,WCV Car,int n) {
    float n1_car_distance = distance(Car, N1, n);
    float n1_car_time = time(Car, N1, n);
    float n2_car_distance = distance(Car, N2, n);
    float n2_car_time = time(Car, N2, n);
    float final_score_n1 = score(n1_car_distance, n1_car_time);
    float final_score_n2 = score(n2_car_distance, n2_car_time);

    if (final_score_n1 < final_score_n2) {
        return true;
    } else {
        return false;
    }
}
//传入车、要充电的节点，判断在小车到达给节点充电之前是否会死亡
//bool checkCanWaitDeadLine(WCV Car,N n[],int ID) {
/*
 * 判断在小车到达前是否会死亡
 * 不改变节点、小车的值
 */
bool checkCanWaitDeadline(WCV Car,N node){
    float d = 0;
    //N node = n[ID];
    d = sqrt((Car.x - node.x) * (Car.x - node.x) +
             (Car.y - node.y) * (Car.y - node.y));
    if (node.e - ((d / Car.v) * node.q) < 0) {//充电设备到达前不会死亡
        return false;
    } else
        return true;
}
/*
 * 虚拟充电，运动过程中小车没电、小车的电不够充满以及充完后无法回返补充则不去进行充电
 */
bool fakeCharge(WCV Car,N Node)
{
    float d = sqrt((Car.x - Node.x) * (Car.x - Node.x) +
                   (Car.y - Node.y) * (Car.y - Node.y));
    float d1 = sqrt((150 - Node.x) * (150 - Node.x) +
    (75 - Node.y) * (75 - Node.y));
    //error in move
    //error in charge
    //error after charge
    if (Car.E - (d / Car.v) * Car.qm - //error in move
        Car.qc * (Node.emax - Node.e) / Node.qr - //error in charge
        (d1 / Car.v) * Car.qm < 0) {    //error after charge
        return false;
    } else
        return true;
}

/*
 * 小车前往充电
 * 改变参数有：小车的电量————路程耗电、补满节点耗电
 * 节点电量————满状态
 * 小车位置————更新为节点位置
 * 函数返回参数中的t包含了运动过程和充电过程的总时间，便于更新节点状态
 */
void realCharge(WCV &Car,N &Node,float &t) {
    float distance = sqrt((Car.x - Node.x) * (Car.x - Node.x) +
                          (Car.y - Node.y) * (Car.y - Node.y));
    float E = Car.E;
    Car.x = Node.x;
    Car.y = Node.y;
    float tm = distance / Car.v;

    float qc = Car.qc;
    float tc = (Node.emax - Node.e) / Node.qr;

//    float Ec = (900-Node.e)/Node.qr;
//    float tc  = Ec/qc;
    t = tc + tm;

    Car.Eall += tc * qc + tm * Car.qm;
    Car.Ereal += tc * qc * 0.9 + tm * Car.qm;
    Car.E = E - (tc * qc + tm * Car.qm);
    Node.e = Node.emax;
}


/*
 * 想要将更新节点状态和队列整合起来而做了尝试，但是还没投入使用因为段错误的问题仍未解决
 */
void GetQueue(WCV Car,N *node,std::vector<Request> servicequeue,float t,float tm)
{
    for(int j=0;j<sizeof(node);j++){
        updateNode(node[j],tm);
        if(needCharge(node[j])){
            Request r;
            r.x = node[j].x;
            r.y = node[j].y;
            r.e = node[j].e;
            r.q = node[j].q;
            r.t = t;
            r.ID = node[j].ID;
            servicequeue.push_back(r);

            float dtemp = sqrt((Car.x - node[j].x) * (Car.x - node[j].x) +
                               (Car.y - node[j].y) * (Car.y - node[j].y));
            Car.dn = (Car.dn > dtemp) ? dtemp : Car.dn;
            Car.df = (Car.df < dtemp) ? dtemp : Car.df;
            Car.te = (Car.te > r.t) ? t : Car.te;
            Car.tl = (Car.tl < r.t) ? t : Car.tl;
        }
    }
}

#endif //WSN_SERVICEQUEUE_H
