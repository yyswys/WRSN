//
// Created by 22306 on 2023/4/15.
//
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



float time(WCV Car,N Node,int n)
{
    return ((Node.e / Node.q - Car.te) * n) /
           (Car.tl - Car.te);
}

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

bool op(N N1,N N2,WCV Car,int n) {
    float n1_car_distance = distance(Car, N1, n);
    float n1_car_time = time(Car, N2, n);
    float n2_car_distance = distance(Car, N1, n);
    float n2_car_time = time(Car, N2, n);
    float final_score_n1 = score(n1_car_distance, n1_car_time);
    float final_score_n2 = score(n2_car_distance, n2_car_time);

    if (final_score_n1 < final_score_n2) {
        return true;
    } else {
        return false;
    }
}

bool checkCanWaitDeadLine(WCV Car,N node){
    float d = sqrt((Car.x - node.x) * (Car.x - node.x) +
                   (Car.y - node.y) * (Car.y - node.y));
    if (node.e - (d / Car.v) * node.q > 0) {//充电设备到达前不会死亡
        return true;
    } else
        return false;
}

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
        Car.qc * (900 - Node.e) / Node.qr - //error in charge
        (d1 / Car.v) * Car.qm < 0) {    //error after charge
        return false;
    } else
        return true;
}

//真实充电，返回花费时间，将其他节点的状态也向后拨动这样多的时间
void realCharge(WCV &Car,N &Node,float &t) {
    float distance = sqrt((Car.x - Node.x) * (Car.x - Node.x) +
                          (Car.y - Node.y) * (Car.y - Node.y));
    float E = Car.E;
    Car.x = Node.x;
    Car.y = Node.y;
    float tm = distance / Car.v;

    float qc = Car.qc;
    float tc = (900 - Node.e) / Node.qr;

    t = tc+tm;

    Car.Eall +=tc*qc+tm*Car.qm;
    Car.Ereal +=tc*qc*0.9+tm*Car.qm;
    Car.E = E - tc * qc + tm * Car.qm;
}

bool needCharge(WCV& W) {
    if (W.E < 50000 * 0.3) {
        return true;
    } else {
        return false;
    }
}


#endif //WSN_SERVICEQUEUE_H
