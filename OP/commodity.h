//
// Created by ヒヤシンス on 2023/11/13.
//

#include<iostream>

using namespace std;

#ifndef OP_COMMODITY_H
#define OP_COMMODITY_H

class commodity {
public:
    //构造函数
    commodity(const string &id, const double &price, const int &number);

    //获取ID
    string get_id() const;

    //获取单价
    double get_price() const;

    //获取库存
    int get_number() const;

    //重载相等运算符
    bool operator==(const commodity &o) const;

    //修改单价
    void change_price(double new_price);

    //修改存货
    void change_number(int new_number);

    //售出
    void sold(int out);
private:
    //商品名
    string id;
    //价格
    double price;
    //剩余数量
    int number;


};

#endif //OP_COMMODITY_H
