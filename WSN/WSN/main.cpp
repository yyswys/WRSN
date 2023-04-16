#include <iostream>
#include "WCV.h"
#include "WRSN.h"
#include "math.h"
#include "ServiceQueue.h"
using namespace std;

int main() {
    WRSN W;
    WCV Car;
    Request servicequeue[10];
    float X, Y;
    int n;
    float qc, qm, v;
    float td = 0;

    X = 300;
    Y = 150;
    n = 40;
    qc = 500;
    qm = 10;
    v = 5;
    //vector<N> node[n];
    N node[n];
    initWRSN(W, X, Y, n);//初始化节点
    initWCV(Car, W, qc, qm, v);//初始化小车
    initN(n, node, "C://Users//22306//CLionProjects//WSN//node40//node3.txt");
    cout<<Car.E<<endl;
    /*for (int i = 0; i < n; i++) {
        cout << node[i].x << " " << node[i].y << " " << node[i].q << " " << node[i].e << "\n";
        //cout << node[i].q << " ";
    }
    cout << "\n";*/

    for (int i = 0; i < 3000; i++) {

        int flag = 0;
        for (int j = 0; j < n; j++) {//更新节点状态
            updateNode(node[j], 1);//往后拨
            if (needCharge(node[j])) {//需要充电 加到队列中
                Request r;
                r.x = node[j].x;
                r.y = node[j].y;
                r.e = node[j].e;
                r.q = node[j].q;
                r.t = i;
                r.ID = node[j].ID;
                servicequeue[flag++] = r;
                float dtemp = sqrt((Car.x - node[j].x) * (Car.x - node[j].x) +
                                   (Car.y - node[j].y) * (Car.y - node[j].y));
                Car.dn = (Car.dn > dtemp) ? dtemp : Car.dn;
                Car.df = (Car.df < dtemp) ? dtemp : Car.df;
                Car.te = (Car.te > r.t) ? i : Car.te;
                Car.tl = (Car.tl < r.t) ? i : Car.tl;
            }
        }

        //sort(node.begin(),node.end(),op);
        // 如果使用vector，直接用sort排序可用
        if (flag >= 2) {
            for (int k = 0; k < flag; k++) {//排序
                for (int j = 0; j < flag - k; j++) {
                    if (!op(node[servicequeue[j].ID], node[servicequeue[j + 1].ID], Car, n)) {
                        Request r;
                        r = servicequeue[j + 1];
                        servicequeue[j + 1] = servicequeue[j];
                        servicequeue[j] = r;
                    }
                }
            }
        }

        int flag1 = 0;
        float ta = 0;
        float tc = 0;


        do {

            if (NeedCharge(Car)) {//如果小车得充电了，优先保证小车寿命
                cout<<"Need Charge,Energy of Car is :"<<Car.E<<endl;
                ChargeCar(Car, tc);
                for (int m = 0; m < n; m++) {
                    updateNode(node[m], tc-1);
                }
                cout<<"Charge Car costs "<<tc<<endl;
                i += (tc-1);
            }
            if (checkCanWaitDeadLine(Car, node[servicequeue[flag1].ID]) &&
                fakeCharge(Car, node[servicequeue[flag1].ID])) {//如果可以充
                realCharge(Car, node[servicequeue[flag1].ID], ta);
                td = td + sqrt((Car.x - node[servicequeue[flag1].ID].x) *
                               (Car.x - node[servicequeue[flag1].ID].x) +
                               (Car.y - node[servicequeue[flag1].ID].y) *
                               (Car.y - node[servicequeue[flag1].ID].y)) / Car.v + i - servicequeue[flag1].t;


                for (int m = 0; m < n; m++) {
                    updateNode(node[m], ta-1);
                }
                i +=  (ta-1);
                cout << "Charge Node costs " << ta << endl;
                for (int m = 0; m < flag - 1; m++) {
                    servicequeue[m] = servicequeue[m + 1];
                }
                flag -= 1;

            } else
                flag1++;
        } while (flag1 < flag);

    }


    int cnt = 0;
    float tall = 0;
    for (int i = 0; i < n; i++) {
        tall += node[i].t;

        if (node[i].alive) {
            cnt++;
        }
    }

    cout << "Ta/N = " << tall / n << "\n";
    cout << "Eall/Ereal = " << Car.Eall / Car.Ereal << "\n";
    cout << "Na/N = " << cnt / n << endl;
    cout << "hello world\n";
    return 0;
}