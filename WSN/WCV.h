//
// Created by 22306 on 2023/4/15.
//
#include "math.h"
#include "WRSN.h"
#ifndef WSN_WCV_H
#define WSN_WCV_H
struct WCV{
    float x;
    float y;

    float E;    //residual energy of W
    float qc;   //energy consumption rate of charging
    float qm;   //energy consumption rate of moving
    float v;    //traveling speed of WCV

    float dn,df;
    float tl,te;
    float Eall;
    float Ereal;
};
void initWCV(WCV& W,WRSN W1,float qc,float qm,float v) {
    W.x = W1.X / 2;
    W.y = W1.Y / 2;
    W.E = 50000;
    W.qc = qc;
    W.qm = qm;
    W.v = v;
    W.tl = 9999;
    W.te = 0;
    W.dn = 9999;
    W.df = 0;
    W.Eall=0;
    W.Ereal=0;

}
bool NeedCharge(WCV Car){
    if(Car.E<=15000){
        return true;
    }
    else
        return true;
}
void ChargeCar(WCV &Car,float &t1){
    float d1 = sqrt((150 - Car.x) * (150 - Car.x) +
                    (75 - Car.y) * (75 - Car.y));
    float t=d1/Car.v;
    Car.Ereal+=t*Car.qm;
    Car.Eall+=t*Car.qm;
    t1 = t;

    return ;
}
#endif //WSN_WCV_H
