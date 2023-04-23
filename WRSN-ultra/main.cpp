#include <iostream>
#include "WRSN.h"
#include "WCV.h"
#include "ServiceQueue.h"
int main() {
    WRSN W;
    WCV Car;
    Request servicequeue[20];
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

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
