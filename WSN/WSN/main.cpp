#include <iostream>
#include "WCV.h"
#include "WRSN.h"
#include "math.h"
#include "ServiceQueue.h"
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    WRSN W;
    WCV Car;
    //TODO:改链表
    //Request servicequeue[15];
    //Request servicequeue[50];
    vector<Request> servicequeue;
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
    initN(n, node, "C://Users//22306//CLionProjects//WSN//node40//node2.txt");
    cout << Car.E << endl;
    /*for (int i = 0; i < n; i++) {
        cout << node[i].x << " " << node[i].y << " " << node[i].q << " " << node[i].e << "\n";
        //cout << node[i].q << " ";
    }
    cout << "\n";*/

    /*
     * 从零开始计时
     */
    for (int i = 0; i < 200; i++) {
        //GetQueue(Car,node,servicequeue,i,1);
        //这个for循环更新更新节点状态及请求队列
        for (int j = 0; j < n; j++) {//更新节点状态
            updateNode(node[j], 1);//向后拨
            /*
             * debug过程中发现push_back会重复添加请求，添加对同ID的去重
             */
            if (needCharge(node[j]) && find_if(servicequeue.begin(),servicequeue.end(),[] (auto v){
                if(v.ID == )
            return true;
            else return false;})!=servicequeue.end() ) {//需要充电 加到队列中
                Request r;
                r.x = node[j].x;
                r.y = node[j].y;
                r.e = node[j].e;
                r.q = node[j].q;
                r.t = i;
                r.ID = node[j].ID;
                //servicequeue[flag++] = r;
                servicequeue.push_back(r);
                float dtemp = sqrt((Car.x - node[j].x) * (Car.x - node[j].x) +
                                   (Car.y - node[j].y) * (Car.y - node[j].y));
                Car.dn = (Car.dn > dtemp) ? dtemp : Car.dn;
                Car.df = (Car.df < dtemp) ? dtemp : Car.df;
                Car.te = (Car.te > r.t) ? i : Car.te;
                Car.tl = (Car.tl < r.t) ? i : Car.tl;
            }
        }

        //sort(node.begin(),node.end(),op);
        // 如果请求队列元素多于两个则进行排序
        if (servicequeue.size() >= 2) {
            for (int k = 0; k < servicequeue.size(); k++) {//排序
                for (int j = 0; j < servicequeue.size() - k; j++) {
                    if (//!op(node[servicequeue[j].ID], node[servicequeue[j + 1].ID], Car, n)) {
                            !op(node[servicequeue.at(j).ID], node[servicequeue.at(j).ID], Car, n)) {
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
        /*
         * do while第一版，会有segmentation error
         * 尝试第二版 直接while
         * 如果小车需要充电优先保证小车寿命
         * 如果充电了更新状态、更新请求队列
         */
        //do {
            while(i<3000&&flag1<servicequeue.size()){

            if (NeedChargeW(Car)) {//如果小车得充电了，优先保证小车寿命
                cout << "Need Charge,Energy of Car is :" << Car.E << endl;
                ChargeCar(Car, tc);

                for (int m = 0; m < n; m++) {
                    updateNode(node[m], tc);
                    //TODO:更新节点后需要考虑是否需要更新队列
                    if (needCharge(node[m])) {//需要充电 加到队列中
                        Request r;
                        r.x = node[m].x;
                        r.y = node[m].y;
                        r.e = node[m].e;
                        r.q = node[m].q;
                        r.t = i;
                        r.ID = node[m].ID;
                        //servicequeue[flag++] = r;
                        servicequeue.push_back(r);
                        float dtemp = sqrt((Car.x - node[m].x) * (Car.x - node[m].x) +
                                           (Car.y - node[m].y) * (Car.y - node[m].y));
                        Car.dn = (Car.dn > dtemp) ? dtemp : Car.dn;
                        Car.df = (Car.df < dtemp) ? dtemp : Car.df;
                        Car.te = (Car.te > r.t) ? i : Car.te;
                        Car.tl = (Car.tl < r.t) ? i : Car.tl;
                    }
                }
                cout << "Charge Car costs " << tc << endl;
                i += tc;
            }
            int Number = servicequeue.size();
            if (Number >= 2) {
                for (int k = 0; k < servicequeue.size(); k++) {//排序
                    for (int j = 0; j < servicequeue.size() - k; j++) {
                        if (//!op(node[servicequeue[j].ID], node[servicequeue[j + 1].ID], Car, n)) {
                                !op(node[servicequeue[j].ID], node[servicequeue[j+1].ID], Car, n)) {
                            Request r;
                            r = servicequeue[j + 1];
                            servicequeue[j + 1] = servicequeue[j];
                            servicequeue[j] = r;
                        }
                    }
                }
            }

            //TODO: Here,Segmentation fault
            cout<<flag1<<endl;
            /*
             * 如果队首可以服务，则服务队首，否则flag1++，直到可以服务的那个
             */
            if (//checkCanWaitDeadline(Car, node[servicequeue[flag1].ID]) &&
                //checkCanWaitDeadLine(Car,node,servicequeue[flag1].ID)&&
                     !servicequeue.empty()&&checkCanWaitDeadline(Car, node[servicequeue.at(flag1).ID]) &&
                    fakeCharge(Car, node[servicequeue.at(flag1).ID])) {//如果可以充
                realCharge(Car, node[servicequeue.at(flag1).ID], ta);
                i+=ta;
                td = td + sqrt((Car.x - node[servicequeue.at(flag1).ID].x) *
                               (Car.x - node[servicequeue.at(flag1).ID].x) +
                               (Car.y - node[servicequeue.at(flag1).ID].y) *
                               (Car.y - node[servicequeue.at(flag1).ID].y)) / Car.v + i - servicequeue.at(flag1).t;
                /*
                 * 充完电后更新状态
                 */
                for (int m = 0; m < n; m++) {
                    updateNode(node[m], ta);

                    if (needCharge(node[m])) {//需要充电 加到队列中
                        Request r;
                        r.x = node[m].x;
                        r.y = node[m].y;
                        r.e = node[m].e;
                        r.q = node[m].q;
                        r.t = i;
                        r.ID = node[m].ID;
                        //servicequeue[flag++] = r;
                        servicequeue.push_back(r);
                        float dtemp = sqrt((Car.x - node[m].x) * (Car.x - node[m].x) +
                                           (Car.y - node[m].y) * (Car.y - node[m].y));
                        Car.dn = (Car.dn > dtemp) ? dtemp : Car.dn;
                        Car.df = (Car.df < dtemp) ? dtemp : Car.df;
                        Car.te = (Car.te > r.t) ? i : Car.te;
                        Car.tl = (Car.tl < r.t) ? i : Car.tl;
                    }
                }
                if (servicequeue.size() >= 2) {
                    for (int k = 0; k < servicequeue.size(); k++) {//排序
                        for (int j = 0; j < servicequeue.size() - k; j++) {
                            if (//!op(node[servicequeue[j].ID], node[servicequeue[j + 1].ID], Car, n)) {
                                    !op(node[servicequeue.at(j).ID], node[servicequeue.at(j).ID], Car, n)) {
                                Request r;
                                r = servicequeue[j + 1];
                                servicequeue[j + 1] = servicequeue[j];
                                servicequeue[j] = r;
                            }
                        }
                    }
                }

                cout << "Charge Node costs " << ta << endl;
                //TODO:更新队列
/*                for (int m = 0; m < servicequeue.size() - 1; m++) {
                    servicequeue[m] = servicequeue[m + 1];
                }

                servicequeue.size() -= 1;*/
                /*
                 * 排出队首元素
                 */
                servicequeue.erase(servicequeue.begin()+flag1);
                //TODO:更新队列，就是擦去服务的请求，但是我这样写好像是错误的，因为flag1，在变，如果光是这样，会有问题————比如内存泄露（擦除的其实并不是当前的flag1对应的）
                //我们可以，加个flag1=0
                flag1=0;
            } else
                flag1++;
        }
            //while ( i <= 3000 && flag1 < servicequeue.size());

    }


    int cnt = 0;
    float tall = 0;
    for (int i = 0; i < n; i++) {
        tall += node[i].t;

        if (node[i].alive) {
            cnt++;
        }
    }

    cout << "average alive time Ta/N = " << tall / n << "\n";
    cout << "energy usage Eall/Ereal = " << Car.Eall / Car.Ereal << "\n";
    cout << "alive percent Na/N = " << cnt / n << endl;
    cout << "hello world\n";
    return 0;
}