//
// Created by 22306 on 2023/4/15.
//
#include "string"
#include "fstream"
#ifndef WSN_WRSN_H
#define WSN_WRSN_H
struct WRSN{
    int X;  //width
    int Y;  //length
    int N;  //number of sensor nodes
    float E;//能耗比（充电车消耗电量比上网络接受充电电量）
    float Na;//存活比率
};
/*
 * 更新无线传感器网络，包括长、宽、节点数
 */
void initWRSN(WRSN &W,float x,float y,int n){
    W.X = x;
    W.Y = y;
    W.N = n;
    W.E=0;
    W.Na=0;
}
struct N{
    float t;
    int ID;
    float x;
    float y;

    float e;    //residual energy of N
    float emax;
    float q;    //consumption rate of node N

    float qr;   //energy receiving rate of node
    bool alive;
};
/*
 * 从文件读取节点信息包括节点坐标、节点最大电量、节点耗电速率
*/
void initN(int n,N node[],std::string filename){
    std::ifstream infile;
    infile.open(filename);
    for(int i=0;i<n;i++){
        infile>>node[i].x>>node[i].y>>node[i].e>>node[i].emax>>node[i].q;

        node[i].ID=i;
        node[i].qr=0.9;
        node[i].alive = 1;
        node[i].t=0;
    }
    infile.close();
    return ;
}

/*
 * 如果小于三成电量则需要充电
 */
bool needCharge(N node) {
    if (node.e <= 0.3*node.emax) {
        return true;
    } else
        return false;
}
/*
 * 更新节点状态，传入时间t、节点node
 * 变动参数有节点是否存活、节点电量
 */
void updateNode(N &node,float t) {
    node.e -= t * node.q;
    if (node.e <= 0) {
        node.alive = 0;
    } else {
        node.t += t;
    }
    return;
}

#endif //WSN_WRSN_H
