//
// Created by 22306 on 2023/4/23.
//
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

    float r[5];
    float R;

    float maxE;
    float Eall;
    float Ereal;
};
void initWCV(WCV& W,WRSN W1,float qc,float qm,float v,float*r) {
    W.x = W1.X / 2;
    W.y = W1.Y / 2;
    W.E = 50000;
    W.maxE = 50000;
    W.qc = qc;
    W.qm = qm;
    W.v = v;

    for(int i=0;i<5;i++){
        W.r[i] = r[i];
    }

    W.Eall=0;
    W.Ereal=0;

}


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
            Car.R = Car.r[0];
        case 2:
            //Car.qc = ;
            Car.R = Car.r[1];
        case 3:
            //Car.qc = ;
            Car.R = Car.r[2];
    }
}
float calculatePk(WCV&Car,N node){

    float d = sqrt((Car.x-node.x)*(Car.x-node.x)+
            (Car.y-node.y)*(Car.y-node.y));
    return Car.qc*(alpha/(betta+d));
}
//调一百次方法
int fakeCharge(WCV&Car,Location l,N node[],Grid G){
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

        //TODO:遍历所有点可以改成遍历可以被充到电的点
        getPoints(servicequeue,G,Car.R);
        /*for(int j=0;j<30;j++){//遍历所有点，如果欧式距离小于r，可以被充电
            if(sqrt((Car.x-node[j].x)*(Car.x-node[j].x)+
                    (Car.y-node[j].y)*(Car.y-node[j].y)) <= Car.R){
                Qk+=calculatePk(Car,node[j])*((node[j].qmax-node[j].q)/node[j].qr);
            }
        }*/
        for(int j=0;j<canChargeP.size();j++){
            N temp;
            temp.x = canChargeP[j].x;
            temp.y = canChargeP[j].y;
            Qk+= calculatePk(Car,temp);
        }
        U = Qk/(Qk+rk*Car.qm);
        if(U<=bestU){
            bestU=U;
            bestP=i;
        }
    }
    return bestP;
}

void realCharge()
{

}

#endif //WRSN_ULTRA_WCV_H
