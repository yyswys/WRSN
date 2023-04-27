#include <iostream>
#include "WRSN.h"
#include "WCV.h"
#include "ServiceQueue.h"
int main() {
    WRSN W;
    WCV Car;
    //Request servicequeue[20];
    float X, Y;
    int n;
    float qc, v,qm;
    float r[5];
    float td = 0;
    float length;
    Grid G;

    X = 300;
    Y = 150;
    n = 40;
    qc = 500;
    qm = 10;
    v = 5;
    length = 1;
    for(int i=0;i<5;i++){
        r[i] = i+1;
    }

    N node[n];

    initWCV(Car,W,qc,qm,v,r);
    initWRSN(W,X,Y,n);
    initN(n, node, "C://Users//22306//CLionProjects//WSN//node40//node2.txt");
    initGrid(W,length,G);
    float t = 0;
    while(t<3000){
        t+=0.5;
        for(int i=0;i<40;i++) {
            updateNode(node[i], 0.5);
        }
        updateRequest(node);//更新请求队列
        /*
         * 更新请求队列
         * 利用遍历档位，利用getPoints函数获得可以给请求节点充电的网格位置，输入为请求队列、网格、此时的半径
         * 如果能够满足充电的条件，利用fakecharge函数，计算从当前位置到节点位置再到给节点充满电的效益和模拟充电过程即可
         * TODO：fakecharge需调整为输入为小车、网格坐标、节点 输出为效益和能否完成充电
         * 需要存储最佳效益对应的档位（半径）以及充电位置坐标
         * 遍历完成后获得最佳档位和最优充电位置，真实充电
         */
        for(){
            getPoints();
            Location bestP;
            if( ){
                fakeCharge();
                bestU? updatebestP

            }
        }
        realCharge()
        updateNode
        updateRequest

    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
