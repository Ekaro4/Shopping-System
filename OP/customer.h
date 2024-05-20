//
// Created by ヒヤシンス on 2023/11/13.
//

#include<iostream>
using namespace std;

#ifndef OP_CUSTOMER_H
#define OP_CUSTOMER_H

class customer {
public:

    //获取余额
    double get_money() const;

    //获取id
    string get_id() const;

    //获取密码
    string get_password() const;

    //重载相等运算符
    bool operator==(const customer &o);

    //构造函数
    customer(const string &id, const string &password, const double &money);

    //更改密码
    void change_password(const string &new_password);

    //花钱了
    void cost(double cost_money);

private:
    //用户昵称
    string id;
    //用户密码
    string password;
    //用户余额
    double money;

};

#endif
