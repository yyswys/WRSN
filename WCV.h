//
// Created by 22306 on 2023/4/23.
//
#include "math.h"
#include "WRSN.h"
#include "ServiceQueue.h"
#ifndef WRSN_ULTRA_WCV_H
#define WRSN_ULTRA_WCV_H
struct WCV{
    float x;
    float y;
    float E;
    float qc;
    float qm;
    float v;
    float r;


    float maxE;
    float Eall;
    float Ereal;
};

bool NeedCharge(WCV& Car)
{
    if(Car.E<Car.maxE*0.3){
        return true;
    }
    else
        return false;
}
void ChargeCar(WCV& Car,float &t)
{
    float d1 = sqrt((150 - Car.x) * (150 - Car.x) +
                    (75 - Car.y) * (75 - Car.y));
    float t1 = d1 / Car.v;
    Car.E = 50000;
    Car.x = 150;
    Car.y = 75;
    Car.Ereal += t1 * Car.qm;
    Car.Eall += t1 * Car.qm;
    t = t1;
    return ;
}
void cCharge(WCV&Car,int n){//n个档位
    switch (n) {
        case 1:
            //Car.qc = ;
            Car.r = ;
        case 2:
            //Car.qc = ;
            Car.r = ;
        case 3:
            //Car.qc = ;
            Car.r = ;
    }
}
float calculatePk(WCV&Car,N node){
    float d = sqrt((Car.x-node.x)*(Car.x-node.x)+
            (Car.y-node.y)*(Car.y-node.y));
    return Car.qc*(alpha/(beta+d));
}

int fakeCharge(WCV&Car,Location l,N node[]){
    //根据不同档位模拟充电效率，选择最好的一档去真实地充电
    float U = 0;
    float bestU=0;
    int bestP = 0;

    float d = sqrt((Car.x-l.x)*(Car.x-l.x)+
                             (Car.y-l.y)*(Car.y-l.y));
    float rk = d/Car.v;
    for(int i=0;i<3;++i){
        cCharge(Car,i);
        float Qk=0;
        for(int j=0;j<30;j++){//遍历所有点，如果欧式距离小于r，可以被充电
            if(sqrt((Car.x-node[j].x)*(Car.x-node[j].x)+
                    (Car.y-node[j].y)*(Car.y-node[j].y))<Car.r){
                Qk+=calculatePk(Car,node[j])*((node[j].qmax-node[j].q)/node[j].qr)
            }
        }
        U = Qk/(Qk+rk*Car.qm);
        if(U<=bestU){
            bestU=U;
            bestP=i;
        }
    }
    return bestP;
}
#endif //WRSN_ULTRA_WCV_H
