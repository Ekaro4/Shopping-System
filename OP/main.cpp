#include <iostream>
#include"information.h"

//#include"information.cpp"

using namespace std;

int main() {
    //初始化
    Information I;
    if (!I.Init()) {
        cout << "初始化失败!!" << endl;
        exit(-1);
    } else {
        cout << "欢迎来到购物系统" << endl;
    }
    //主菜单
    I.menu();
    return 0;
}