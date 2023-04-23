//
// Created by 22306 on 2023/4/23.
//
#include "string"
#include "fstream"
#include "math.h"
#include "vector"
#ifndef WRSN_ULTRA_WRSN_H
#define WRSN_ULTRA_WRSN_H

float alpha;
float betta;

struct Location{
    float x;
    float y;
};

struct WRSN{
    int X;  //width
    int Y;  //length
    int N;  //number of sensor nodes
    float E;//能耗比（充电车消耗电量比上网络接受充电电量）
    float Na;//存活比率
};
void initWRSN(WRSN&W,float x,float y,int n){
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
    float q;    //consumption rate of node N
    float qmax;

    float qr;   //energy receiving rate of node
    bool alive;
};
void initN(int n,N node[],std::string filename){
    std::ifstream infile;
    infile.open(filename);
    for(int i=0;i<n;i++){
        infile>>node[i].x>>node[i].y>>node[i].e>>node[i].q;

        node[i].ID=i;
        node[i].qr=0.9;
        node[i].alive = 1;
        node[i].t=0;
    }
    infile.close();
    return ;
}

struct Grid{
    std::vector<Location> l;
    int n;
    float length;
    int nofGrid;
};
//floor向下取整
//ceil向上取整
void initGrid(WRSN&W,float length,Grid&G){
    //划分网格，根据边长划分，得到网格数量及充电位置数量
    float x = W.X;
    float y = W.Y;
    G.nofGrid = floor(x/length)*floor(y/length);
    G.n = (floor(x/length)+1)*(floor(y/length)+1);
    for(int i=0;i<ceil(x/length);i++){
        for(int j=0;ceil(j<y/length);j++){
            l
        }
    }
}


bool needCharge(N node) {
    if (node.e <= 270) {
        return true;
    } else return false;
}
void updateNode(N &node,float t) {
    node.e -= t * node.q;
    if (node.e <= 0) {
        node.alive = 0;
    } else {
        node.t += t;
    }
    return;
}


#endif //WRSN_ULTRA_WRSN_H
